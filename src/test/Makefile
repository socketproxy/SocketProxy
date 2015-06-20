.PHONY: test clean bin_targets lib_targets one socket_test libmike.so.1 
.PHONY: fake_socket

CC=cc
BUILDDIR ?= .
BINDIR ?= .
LIBDIR ?= .
CFLAGS = -I../library
SOFLAGS = -shared -Wl,-soname,libmike -fPIC

SRCDIR ?= ..

BIN_TARGETS = serialize_test socketpair_test socket_test test_client \
	test_is_closed
LIB_TARGETS = fake_socket.c fake_malloc.c

SRC = fake_malloc.c fake_socket.c serialize_test.c socketpair_test.c \
	socket_test.c test_client.c test_is_closed.c
OBJ = $(SRC:%.c=%.o)

test_client:
	$(CC) -o $(BINDIR)/test_client test_client.c

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

all: bin_targets lib_targets

bin_targets: $(BINDIR)/$(BIN_TARGETS)

$(BINDIR)/%: %.o

lib_targets: $(LIBDIR)/$(LIB_TARGETS)
one: socket_test

some: socket_test serialize_test fake_socket

socket_test: socket_test.o
	$(CC) -o $(BUILDDIR)/socket_test socket_test.o

serialize_test: serialize_test.o
	$(CC) -o $(BUILDDIR)/serialize_test 	\
		$(CFLAGS)			\
		$(SRCDIR)/library/serialize.c	\
		serialize_test.o 
	$(BUILDDIR)/serialize_test

libmike.so.1: fake_socket.c
	$(CC) -o $(LIBDIR)/libmike.so.1		\
		$(CFLAGS)			\
		$(SOFLAGS)			\
		fake_socket.c


fake_socket: socket_test libmike.so.1
	LD_PRELOAD="$(LIBDIR)/libmike.so.1" $(BUILDDIR)/socket_test


clean:
	rm -f $(OBJ)
	cd $(BUILDDIR)
	rm -f $(BIN_TARGETS)
	cd $(LIBDIR)
	rm -f libmike.so.1
