#!/usr/bin/bash

###
# socketproxy/src/scripts/fake_socket.sh
# (c) 2010 Mike Doyle
#

set -x
set -e
cd /home/ferrous/projects/socketproxy/
rm -rf build
mkdir build
cd build
cp ../src/test/fake_socket.c .
gcc -c fake_socket.c
mkdir lib
gcc -shared -Wl,-soname,libmike -o lib/libmike.so.1 fake_socket.o
cp ../src/test/socket_test.c .
gcc -o socket_test socket_test.c
LD_PRELOAD="lib/libmike.so.1" ./socket_test
