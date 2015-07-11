#!/usr/bin/bash

###
# socketproxy/src/scripts/does_socketpair_call_socket.sh
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
cp ../src/test/fake_socket.c .
gcc -c fake_socket.c
mkdir lib
gcc -shared -Wl,-soname,libmike -o lib/libmike.so.1 fake_socket.o
cp ../src/test/socketpair_test.c .
gcc -o socket_test socketpair_test.c
LD_PRELOAD="lib/libmike.so.1" ./socket_test
