// jmethodID probe: where do the ids live, how are they aligned, which bits do they have.
// Records every jmethodID of every prepared class with the thread that prepared it,
// then classifies the values against /proc/self/maps (Linux) at VM death.
#include <jvmti.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#ifdef __linux__
#include <sys/syscall.h>
#include <elf.h>
#endif

typedef struct { uint64_t id; uint64_t tid; } Rec;
static Rec* recs;
static size_t nrecs, caprecs;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static jvmtiEnv* jvmti;

static uint64_t tid(void) {
#ifdef __linux__
    return (uint64_t)syscall(SYS_gettid);
#else
    uint64_t t; pthread_threadid_np(NULL, &t); return t;
#endif
}

static void record(jclass klass) {
    jint n = 0; jmethodID* m = NULL;
    if ((*jvmti)->GetClassMethods(jvmti, klass, &n, &m) != JVMTI_ERROR_NONE) return;
    uint64_t t = tid();
    pthread_mutex_lock(&lock);
    if (nrecs + n > caprecs) {
        caprecs = (caprecs + n) * 2;
        recs = realloc(recs, caprecs * sizeof(Rec));
    }
    for (jint i = 0; i < n; i++) { recs[nrecs].id = (uint64_t)(uintptr_t)m[i]; recs[nrecs].tid = t; nrecs++; }
    pthread_mutex_unlock(&lock);
    (*jvmti)->Deallocate(jvmti, (unsigned char*)m);
}

static void JNICALL onClassPrepare(jvmtiEnv* e, JNIEnv* jni, jthread thread, jclass klass) { record(klass); }

static void JNICALL onVMInit(jvmtiEnv* e, JNIEnv* jni, jthread thread) {
    jint n = 0; jclass* cls = NULL;
    if ((*jvmti)->GetLoadedClasses(jvmti, &n, &cls) == JVMTI_ERROR_NONE) {
        for (jint i = 0; i < n; i++) record(cls[i]);
        (*jvmti)->Deallocate(jvmti, (unsigned char*)cls);
    }
}

// ---- classification ----
typedef struct { uint64_t start, end; char kind; } Map;   // kind: H brk heap, A anonymous, F file, S stack
static Map* maps; static int nmaps;

static void readMaps(void) {
#ifdef __linux__
    FILE* f = fopen("/proc/self/maps", "r");
    if (!f) return;
    char line[4096];
    while (fgets(line, sizeof(line), f)) {
        uint64_t s, e; char perms[8]; unsigned long off; char dev[16]; unsigned long ino; char name[4096] = "";
        int k = sscanf(line, "%lx-%lx %7s %lx %15s %lu %4095[^\n]", &s, &e, perms, &off, dev, &ino, name);
        if (k < 6) continue;
        char kind = name[0] == 0 ? 'A' : strcmp(name, "[heap]") == 0 ? 'H' : strncmp(name, "[stack", 6) == 0 ? 'S' : name[0] == '[' ? 'O' : 'F';
        if (nmaps % 1024 == 0) maps = realloc(maps, (nmaps + 1024) * sizeof(Map));
        maps[nmaps].start = s; maps[nmaps].end = e; maps[nmaps].kind = kind; nmaps++;
    }
    fclose(f);
#endif
}

static char kindOf(uint64_t a) {
    for (int i = 0; i < nmaps; i++) if (a >= maps[i].start && a < maps[i].end) return maps[i].kind;
    return '?';
}

static int cmpRec(const void* a, const void* b) {
    const Rec* x = a; const Rec* y = b;
    return x->tid < y->tid ? -1 : x->tid > y->tid ? 1 : x->id < y->id ? -1 : x->id > y->id;
}

static void JNICALL onVMDeath(jvmtiEnv* e, JNIEnv* jni) {
    readMaps();
    struct utsname u; uname(&u);
    struct rlimit rl; getrlimit(RLIMIT_STACK, &rl);
    char* vmver = NULL; (*jvmti)->GetSystemProperty(jvmti, "java.vm.version", &vmver);
    char* vmname = NULL; (*jvmti)->GetSystemProperty(jvmti, "java.vm.name", &vmname);
    char* vendor = NULL; (*jvmti)->GetSystemProperty(jvmti, "java.vendor", &vendor);
    printf("== probe: %s %s | %s %s (%s) | stack rlimit %s | LD_PRELOAD=%s | DYLD_INSERT_LIBRARIES=%s\n",
           u.sysname, u.machine, vmname ? vmname : "?", vmver ? vmver : "?", vendor ? vendor : "?",
           rl.rlim_cur == RLIM_INFINITY ? "unlimited" : "limited",
           getenv("LD_PRELOAD") ? getenv("LD_PRELOAD") : "-", getenv("DYLD_INSERT_LIBRARIES") ? getenv("DYLD_INSERT_LIBRARIES") : "-");
#ifdef __linux__
    {
        FILE* x = fopen("/proc/self/exe", "rb"); Elf64_Ehdr h;
        if (x && fread(&h, sizeof h, 1, x) == 1) printf("   launcher: %s\n", h.e_type == ET_DYN ? "PIE (ET_DYN)" : h.e_type == ET_EXEC ? "non-PIE (ET_EXEC)" : "?");
        if (x) fclose(x);
        printf("   brk heap at %#lx, this agent mapped at %#lx, a stack var at %#lx\n",
               (unsigned long)sbrk(0), (unsigned long)(uintptr_t)&onVMDeath, (unsigned long)(uintptr_t)&u);
    }
#endif
    pthread_mutex_lock(&lock);
    qsort(recs, nrecs, sizeof(Rec), cmpRec);
    uint64_t lo = ~0ull, hi = 0; size_t low3[8] = {0}; size_t b47 = 0, b46 = 0, b40 = 0, kinds[256] = {0};
    size_t nthreads = 0;
    for (size_t i = 0; i < nrecs; i++) {
        uint64_t id = recs[i].id;
        if (id < lo) lo = id; if (id > hi) hi = id;
        low3[id & 7]++; b47 += (id >> 47) & 1; b46 += (id >> 46) & 1; b40 += (id >> 40) & 1;
        kinds[(unsigned char)kindOf(id)]++;
        if (i == 0 || recs[i].tid != recs[i - 1].tid) nthreads++;
    }
    printf("   ids: %zu from %zu threads, min %#lx max %#lx\n", nrecs, nthreads, (unsigned long)lo, (unsigned long)hi);
    printf("   low 3 bits: 0:%zu 1:%zu 2:%zu 3:%zu 4:%zu 5:%zu 6:%zu 7:%zu\n", low3[0], low3[1], low3[2], low3[3], low3[4], low3[5], low3[6], low3[7]);
    printf("   bit47 set: %zu  bit46 set: %zu  bit40 set: %zu\n", b47, b46, b40);
    printf("   regions: brk-heap %zu, anon-mmap %zu, file %zu, stack %zu, other %zu, no-mapping %zu\n",
           kinds['H'], kinds['A'], kinds['F'], kinds['S'], kinds['O'], kinds['?']);
    // per thread: first 12 threads
    size_t shown = 0;
    for (size_t i = 0; i < nrecs && shown < 12;) {
        size_t j = i; size_t h = 0, a = 0, o = 0, s47 = 0;
        while (j < nrecs && recs[j].tid == recs[i].tid) {
            char k = kindOf(recs[j].id); if (k == 'H') h++; else if (k == 'A') a++; else o++;
            s47 += (recs[j].id >> 47) & 1; j++;
        }
        printf("   thread %lu: %zu ids, brk %zu anon %zu other %zu, bit47 set %zu, first %#lx last %#lx\n",
               (unsigned long)recs[i].tid, j - i, h, a, o, s47, (unsigned long)recs[i].id, (unsigned long)recs[j - 1].id);
        i = j; shown++;
    }
    pthread_mutex_unlock(&lock);
    fflush(stdout);
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM* vm, char* options, void* reserved) {
    if ((*vm)->GetEnv(vm, (void**)&jvmti, JVMTI_VERSION_1_0) != JNI_OK) return 1;
    jvmtiEventCallbacks cb; memset(&cb, 0, sizeof cb);
    cb.VMInit = onVMInit; cb.ClassPrepare = onClassPrepare; cb.VMDeath = onVMDeath;
    (*jvmti)->SetEventCallbacks(jvmti, &cb, sizeof cb);
    (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, NULL);
    (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_CLASS_PREPARE, NULL);
    (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABLE, JVMTI_EVENT_VM_DEATH, NULL);
    return 0;
}
