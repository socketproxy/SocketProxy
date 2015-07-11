#!/usr/bin/bash

###
# socketproxy/src/scripts/test_agent.sh
# (c) 2010 Mike Doyle
#
#    This file is part of SocketProxy.
#
#    SocketProxy is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 2 of the License, or
#    (at your option) any later version.
#
#    SocketProxy is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with SocketProxy.  If not, see <http://www.gnu.org/licenses/>.

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
