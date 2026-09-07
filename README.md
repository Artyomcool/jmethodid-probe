# jmethodID probe

Where do HotSpot jmethodIDs live and which bits do they have? A JVMTI agent records the
jmethodID of every prepared class with the thread that prepared it, a loader links
thousands of JDK classes from 16 threads, and at VM death the ids are classified against
/proc/self/maps: brk heap, anonymous mmap, file; alignment (low 3 bits); bits 40/46/47.

`./run.sh [JAVA_HOME]` runs it with the default layout, with `ulimit -s unlimited`
(the legacy bottom-up mmap layout) and with every alternative allocator found for
LD_PRELOAD. The workflow runs the same on Linux aarch64, Linux x86-64 and macOS arm64
across JDK 17/21/25 and a few vendors.
