# (c) 2015 Mike Doyle
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
#
.PHONY: test clean bin_targets lib_targets one socket_test 
.PHONY: fake_socket

CC=cc
BUILDDIR ?= $(PWD)
BINDIR ?= $(PWD)
LIBDIR ?= $(PWD)
CFLAGS = -I../library
CCFLAGS =
SOFLAGS = -shared -Wl,-soname,libmike -fPIC

export BUILDDIR BINDIR LIBDIR
SRCDIR ?= ..

BIN_TARGETS = serialize_test socketpair_test socket_test test_client \
	test_is_closed
LIB_TARGETS = fake_socket.c fake_malloc.c

SRC = fake_malloc.c fake_socket.c serialize_test.c socketpair_test.c \
	socket_test.c test_client.c test_is_closed.c
OBJ = $(SRC:%.c=%.o)

debug: CCFLAGS += -DDEBUG -g

profile: CCFLAGS += -pg
profile: socket_test

test_client:
	$(CC) -o $(BINDIR)/test_client test_client.c

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

all: bin_targets lib_targets

bin_targets: $(BINDIR)/$(BIN_TARGETS)

$(BINDIR)/%: %.o

lib_targets: $(LIBDIR)/$(LIB_TARGETS)
one: socket_test

some: agent_test
#some: socket_test serialize_test fake_socket

soxprox-agent:
	$(MAKE) -C ../agent soxprox-agent

soxprox:
	$(MAKE) -C ../server soxprox

libmike.so.1:
	$(MAKE) -C ../library libmike.so.1

agent_test: libmike.so.1 soxprox soxprox-agent test_client
	$(BUILDDIR)/soxprox --debug			\
		--agent="$(BUILDDIR)/soxprox-agent -d" 	\
		--client=$(BUILDDIR)/test_client

nc_test: libmike.so.1 soxprox soxprox-agent 
	$(BUILDDIR)/soxprox --debug			\
		--agent="$(BUILDDIR)/soxprox-agent -d" 	\
		--client="nc -z 127.0.0.1 80"

socket_test: socket_test.o
	$(CC) $(CCFLAGS) -o $(BUILDDIR)/socket_test socket_test.o
	$(BUILDDIR)/socket_test

serialize_test: serialize_test.o
	$(CC) -o $(BUILDDIR)/serialize_test 	\
		$(CFLAGS)			\
		$(SRCDIR)/library/serialize.c	\
		serialize_test.o 
	$(BUILDDIR)/serialize_test

fakesock.so.1: fake_socket.c
	$(CC) -o $(LIBDIR)/fakesock.so.1	\
		$(CFLAGS)			\
		$(SOFLAGS)			\
		fake_socket.c

fake_socket: socket_test fakesock.so.1
	LD_PRELOAD="$(LIBDIR)/fakesock.so.1" $(BUILDDIR)/socket_test

test_nc: libmike.so.1 soxprox soxprox-agent 
	

clean:
	rm -f $(OBJ)
	cd $(BUILDDIR)
	rm -f $(BIN_TARGETS)
	rm -f gmon.out
	rm -f soxprox_debug.err soxprox_debug.log
	cd $(LIBDIR)
	rm -f libmike.so.1 fakesock.so.1
	cd $(BINDIR)
	rm -f soxprox soxprox-agent
