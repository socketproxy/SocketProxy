#!/usr/bin/bash

###
# socketproxy/src/scripts/test_nmap.sh
# (c) 2010 Mike Doyle
#

set -x
set -e
cd /home/ferrous/projects/socketproxy/
rm -rf build
mkdir build
cd build

mkdir lib libsrc
cd libsrc
cp ../../src/library/*.c ../../src/library/*.h .
gcc -c *.c
gcc -shared -Wl,-soname,libmike -o ../lib/libmike.so.1 *.o

cd ..

cp ../src/agent/soxprox-agent.pl ./soxprox-agent
cp ../src/server/soxprox.pl ./soxprox

./soxprox \
    --agent="/home/ferrous/projects/socketproxy/build/soxprox-agent" \
    --client="nmap -PS -p80 --max-parallelism=1 -v localhost"
