#!/bin/bash
# usage: run.sh [java_home]  - builds the agent and the loader, runs the probe in a few configurations
set -u
JH=${1:-${JAVA_HOME:-$(dirname $(dirname $(readlink -f $(which java))))}}
OS=$(uname -s); ARCH=$(uname -m)
case $OS in Linux) INC=linux; EXT=so;; Darwin) INC=darwin; EXT=dylib;; esac
cc -shared -fPIC -O1 -o libprobe.$EXT -I$JH/include -I$JH/include/$INC probe.c || exit 1
$JH/bin/javac -d out Loader.java || exit 1
echo "### $OS $ARCH, $($JH/bin/java -version 2>&1 | head -1)"
file -L $JH/bin/java 2>/dev/null | sed 's/.*: /   launcher (file): /'
run() { echo "--- $1"; shift; "$@" $JH/bin/java -agentpath:$PWD/libprobe.$EXT -cp out Loader 16 30000 2>&1 | grep -v '^linked' ; }
run "default" env
if [ $OS = Linux ]; then
  run "ulimit -s unlimited (legacy mmap layout)" bash -c 'ulimit -s unlimited; exec "$@"' _
  for lib in /usr/lib/$ARCH-linux-gnu/libjemalloc.so.2 /usr/lib/$ARCH-linux-gnu/libtcmalloc.so.4 /usr/lib/$ARCH-linux-gnu/libmimalloc.so.2 /usr/lib/$ARCH-linux-gnu/libmimalloc.so.2.1; do
    [ -f $lib ] && run "LD_PRELOAD=$(basename $lib)" env LD_PRELOAD=$lib
  done
fi
