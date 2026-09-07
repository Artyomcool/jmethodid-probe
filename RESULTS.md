# Results, run 34139384124 (2026-09-07)

All ids 8-aligned everywhere (misaligned = 0 in every row). Linux aarch64 runners: CONFIG_ARM64_VA_BITS=48, Temurin/Zulu/Corretto launchers PIE; macOS Temurin launcher non-PIE.

```
## macos-15_17_temurin  launcher=non-PIE
   default                                    ids=200414 bit47=     0 bit46=143075 brk=     0 anon=     0 min=0x12b604240 max=0x600003bfe1b8
## macos-15_21_temurin  launcher=non-PIE
   default                                    ids=211531 bit47=     0 bit46=151803 brk=     0 anon=     0 min=0x1261053b0 max=0x600003f7ddf0
## macos-15_25_temurin  launcher=non-PIE
   default                                    ids=210194 bit47=     0 bit46=150645 brk=     0 anon=     0 min=0x10161bdd0 max=0x600003f7f238
## ubuntu-24.04-arm_17_temurin  launcher=PIE
   default                                    ids=202016 bit47=202016 bit46=190139 brk= 11877 anon=190139 min=0xaad6d4bce6a0 max=0xff130820c888
   ulimit -s unlimited (legacy mmap layout)   ids=202016 bit47= 10474 bit46=191542 brk= 10474 anon=191542 min=0x401fc0000c20 max=0xab69a309d3a8
   LD_PRELOAD=libjemalloc.so.2                ids=202016 bit47=202016 bit46=202016 brk=     0 anon=202016 min=0xff7590d30140 max=0xff75d2fe9f78
   LD_PRELOAD=libtcmalloc.so.4                ids=202016 bit47=202016 bit46=     0 brk=202016 anon=     0 min=0xab4938ce5f90 max=0xab493f78cc40
   LD_PRELOAD=libmimalloc.so.2                ids=202016 bit47=     0 bit46=     0 brk=     0 anon=202016 min=0x4d772011730 max=0x4d7be3c07b8
   LD_PRELOAD=libmimalloc.so.2.1              ids=202016 bit47=     0 bit46=     0 brk=     0 anon=202016 min=0x20f06011730 max=0x20f525698f8
## ubuntu-24.04-arm_21_corretto  launcher=PIE
   default                                    ids=213068 bit47=213068 bit46=201177 brk= 11891 anon=201177 min=0xab2201b04210 max=0xff61e01f2298
   ulimit -s unlimited (legacy mmap layout)   ids=213068 bit47= 12562 bit46=200506 brk= 12562 anon=200506 min=0x40d48402b570 max=0xab1ce2f3f478
   LD_PRELOAD=libjemalloc.so.2                ids=213068 bit47=213068 bit46=213068 brk=     0 anon=213068 min=0xff1e91315240 max=0xff1ecf320920
   LD_PRELOAD=libtcmalloc.so.4                ids=213068 bit47=213068 bit46=     0 brk=213068 anon=     0 min=0xaae31a0340c0 max=0xaae31f6c5ff8
   LD_PRELOAD=libmimalloc.so.2                ids=213068 bit47=     0 bit46=     0 brk=     0 anon=213068 min=0x5cee0013e40 max=0x5cf2849d328
   LD_PRELOAD=libmimalloc.so.2.1              ids=213068 bit47=     0 bit46=     0 brk=     0 anon=213068 min=0x5b54a013e40 max=0x5b5924070f8
## ubuntu-24.04-arm_21_temurin  launcher=PIE
   default                                    ids=213068 bit47=213068 bit46=200421 brk= 12647 anon=200421 min=0xaafa8cbd6bb0 max=0xff6f6c1f74b8
   ulimit -s unlimited (legacy mmap layout)   ids=213068 bit47= 11206 bit46=201862 brk= 11206 anon=201862 min=0x40690402b510 max=0xab26a0d93be8
   LD_PRELOAD=libjemalloc.so.2                ids=213068 bit47=213068 bit46=213068 brk=     0 anon=213068 min=0xffc0e64153c0 max=0xffc1265ee078
   LD_PRELOAD=libtcmalloc.so.4                ids=213068 bit47=213068 bit46=     0 brk=213068 anon=     0 min=0xab2b768660c0 max=0xab2b7ddfbfb8
   LD_PRELOAD=libmimalloc.so.2                ids=213068 bit47=     0 bit46=     0 brk=     0 anon=213068 min=0x25d84014080 max=0x25dcc6e0ef8
   LD_PRELOAD=libmimalloc.so.2.1              ids=213068 bit47=     0 bit46=     0 brk=     0 anon=213068 min=0x36806014080 max=0x3684e4349f8
## ubuntu-24.04-arm_21_zulu  launcher=PIE
   default                                    ids=213612 bit47=213612 bit46=200468 brk= 13144 anon=200468 min=0xab5c0027d850 max=0xffdb801e3bd8
   ulimit -s unlimited (legacy mmap layout)   ids=213612 bit47= 11768 bit46=201844 brk= 11768 anon=201844 min=0x40f0cc000c30 max=0xab5c0b86b308
   LD_PRELOAD=libjemalloc.so.2                ids=213612 bit47=213612 bit46=213612 brk=     0 anon=213612 min=0xff0652c803c0 max=0xff0690975d18
   LD_PRELOAD=libtcmalloc.so.4                ids=213612 bit47=213612 bit46=     0 brk=213612 anon=     0 min=0xaaabbc9c9ef0 max=0xaaabc20bab78
   LD_PRELOAD=libmimalloc.so.2                ids=213612 bit47=     0 bit46=     0 brk=     0 anon=213612 min=0x221b2013ea0 max=0x221fa3b7688
   LD_PRELOAD=libmimalloc.so.2.1              ids=213612 bit47=     0 bit46=     0 brk=     0 anon=213612 min=0x47580013ea0 max=0x475c8470778
## ubuntu-24.04-arm_25_temurin  launcher=PIE
   default                                    ids=211396 bit47=211396 bit46=199831 brk= 11565 anon=199831 min=0xaaf29d8096c0 max=0xff050c1cf878
   ulimit -s unlimited (legacy mmap layout)   ids=211396 bit47= 12650 bit46=198746 brk= 12650 anon=198746 min=0x401c1002ac10 max=0xab34473d21b8
   LD_PRELOAD=libjemalloc.so.2                ids=211396 bit47=211396 bit46=211396 brk=     0 anon=211396 min=0xff5e93080040 max=0xff5ecf3ee670
   LD_PRELOAD=libtcmalloc.so.4                ids=211396 bit47=211396 bit46=     0 brk=211396 anon=     0 min=0xaaba191bc0c0 max=0xaaba1e24bd78
   LD_PRELOAD=libmimalloc.so.2                ids=211396 bit47=     0 bit46=     0 brk=     0 anon=211396 min=0x3e2c2011080 max=0x3e30a5affb8
   LD_PRELOAD=libmimalloc.so.2.1              ids=211396 bit47=     0 bit46=     0 brk=     0 anon=211396 min=0x30a6a011080 max=0x30ab22cceb8
## ubuntu-24.04_17_temurin  launcher=PIE
   default                                    ids=202016 bit47=     0 bit46=202016 brk= 11225 anon=190791 min=0x55eb7e7ab7a0 max=0x7fa0842266c8
   ulimit -s unlimited (legacy mmap layout)   ids=202016 bit47=     0 bit46= 12927 brk= 12927 anon=189089 min=0x14fd080118b0 max=0x55bc547001a8
   LD_PRELOAD=libjemalloc.so.2                ids=202016 bit47=     0 bit46=202016 brk=     0 anon=202016 min=0x7f63d4900500 max=0x7f644f7fef48
   LD_PRELOAD=libtcmalloc.so.4                ids=202016 bit47=     0 bit46=202016 brk=202016 anon=     0 min=0x564500ede1e0 max=0x564505749f38
   LD_PRELOAD=libmimalloc.so.2                ids=202016 bit47=     0 bit46=     0 brk=     0 anon=202016 min=0x288120115e0 max=0x2885e404278
   LD_PRELOAD=libmimalloc.so.2.1              ids=202016 bit47=     0 bit46=     0 brk=     0 anon=202016 min=0x285880115e0 max=0x285d6780d50
## ubuntu-24.04_21_temurin  launcher=PIE
   default                                    ids=213068 bit47=     0 bit46=213068 brk= 13573 anon=199495 min=0x5647d32ab420 max=0x7f5b60223118
   ulimit -s unlimited (legacy mmap layout)   ids=213068 bit47=     0 bit46= 11772 brk= 11772 anon=201296 min=0x14c678002930 max=0x562c86302d20
   LD_PRELOAD=libjemalloc.so.2                ids=213068 bit47=     0 bit46=213068 brk=     0 anon=213068 min=0x7f240da89100 max=0x7f24857efc40
   LD_PRELOAD=libtcmalloc.so.4                ids=213068 bit47=     0 bit46=213068 brk=213068 anon=     0 min=0x55876de82100 max=0x5587759a3ff8
   LD_PRELOAD=libmimalloc.so.2                ids=213068 bit47=     0 bit46=     0 brk=     0 anon=213068 min=0x56062013c00 max=0x560aa4679b8
   LD_PRELOAD=libmimalloc.so.2.1              ids=213068 bit47=     0 bit46=     0 brk=     0 anon=213068 min=0x2e94e013c00 max=0x2e99665f5f8
## ubuntu-24.04_25_temurin  launcher=PIE
   default                                    ids=211396 bit47=     0 bit46=211396 brk= 12478 anon=198918 min=0x562495f88690 max=0x7f1dec1d82e8
   ulimit -s unlimited (legacy mmap layout)   ids=211396 bit47=     0 bit46= 12970 brk= 12970 anon=198426 min=0x154780000ba0 max=0x55a0e6b2ff48
   LD_PRELOAD=libjemalloc.so.2                ids=211396 bit47=     0 bit46=211396 brk=     0 anon=211396 min=0x7fbc011110c0 max=0x7fbc3cbfefe8
   LD_PRELOAD=libtcmalloc.so.4                ids=211396 bit47=     0 bit46=211396 brk=211396 anon=     0 min=0x55d72f142100 max=0x55d733d80bf8
   LD_PRELOAD=libmimalloc.so.2                ids=211396 bit47=     0 bit46=     0 brk=     0 anon=211396 min=0x251d2010120 max=0x2521a3f4cd0
   LD_PRELOAD=libmimalloc.so.2.1              ids=211396 bit47=     0 bit46=     0 brk=     0 anon=211396 min=0x352d8010120 max=0x35320331710
```
