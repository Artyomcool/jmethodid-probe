import java.io.IOException;
import java.lang.module.ModuleReader;
import java.lang.module.ModuleReference;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

// Loads and links thousands of JDK classes from many threads, so that the jmethodID
// cells get allocated from many malloc arenas (glibc gives a fresh thread a fresh arena).
public class Loader {
    public static void main(String[] args) throws Exception {
        int threads = args.length > 0 ? Integer.parseInt(args[0]) : 16;
        int limit = args.length > 1 ? Integer.parseInt(args[1]) : 30000;
        List<String> names = new ArrayList<>();
        for (ModuleReference ref : ModuleLayer.boot().configuration().modules().stream().map(m -> m.reference()).toList()) {
            try (ModuleReader r = ref.open()) {
                r.list().filter(n -> n.endsWith(".class") && !n.contains("-")).forEach(n -> {
                    if (names.size() < limit) names.add(n.substring(0, n.length() - 6).replace('/', '.'));
                });
            } catch (IOException ignored) {
            }
        }
        AtomicInteger next = new AtomicInteger();
        AtomicInteger linked = new AtomicInteger();
        Thread[] ts = new Thread[threads];
        for (int t = 0; t < threads; t++) {
            ts[t] = new Thread(() -> {
                // a fresh thread: its first malloc picks an arena
                for (int i; (i = next.getAndIncrement()) < names.size();) {
                    try {
                        Class<?> c = Class.forName(names.get(i), false, Loader.class.getClassLoader());
                        c.getDeclaredMethods();   // links (prepares) the class
                        linked.incrementAndGet();
                    } catch (Throwable ignored) {
                    }
                }
            }, "loader-" + t);
            ts[t].start();
        }
        for (Thread t : ts) t.join();
        System.out.println("linked " + linked.get() + " of " + names.size() + " classes on " + threads + " threads");
    }
}
