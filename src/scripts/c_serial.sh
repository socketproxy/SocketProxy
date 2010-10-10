#!/usr/bin/bash

###
# socketproxy/src/scripts/c_serial.sh
# (c) 2010 Mike Doyle
#

set -x
set -e
cd /home/ferrous/projects/socketproxy/
rm -rf build
mkdir build
cd build
cp ../src/test/serialize_test.c \
   ../src/library/serialize.c \
   ../src/library/serialize.h \
    .
gcc -o serialize_test *.c
