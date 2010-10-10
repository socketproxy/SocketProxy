#!/usr/bin/bash

###
# socketproxy/src/scripts/test_agent.sh
# (c) 2010 Mike Doyle
#

set -x
set -e
cd /home/ferrous/projects/socketproxy/
rm -rf build
mkdir build
cd build

cp ../src/test/test_client.c .
gcc -o test_client test_client.c

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
    --client="./test_client"
