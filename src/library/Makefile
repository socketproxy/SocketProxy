# socketproxy/src/library/Makefile
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

CCFLAGS = -fPIC

.PHONY: library clean debug
LIBDIR ?= .

debug: CCFLAGS += -DDEBUG -g
debug: library

socket.o: socket.c socket.h serialize.h
	gcc -c socket.c

fifo_client.o: fifo_client.c fifo_client.h serialize.h

clean:
	rm -f *.o $(LIBDIR)/libmike.so.1

library:
	gcc $(CCFLAGS) -c *.c
	gcc -shared $(CCFLAGS) -Wl,-soname,libmike -o $(LIBDIR)/libmike.so.1 *.o
