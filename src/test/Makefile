.PHONY: test clean bin_targets lib_targets

CC=cc
BUILDDIR ?= .
BINDIR ?= .
LIBDIR ?= .
CFLAGS = -I../library

SRCDIR = .

BIN_TARGETS = serialize_test socketpair_test socket_test test_client test_is_closed
LIB_TARGETS = fake_socket.c fake_malloc.c

SRC = fake_malloc.c fake_socket.c serialize_test.c socketpair_test.c socket_test.c test_client.c test_is_closed.c
OBJ = $(SRC:%.c=$.o)

test_client:
	$(CC) -o $(BINDIR)/test_client test_client.c

#$(BUILDDIR)/%.o: %.c
#	$(CC) -c $(CFLAGS) $< -o $@
#

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

all: bin_targets lib_targets

$(BINDIR)/serialize_test: serialize_test.o
	$(CC) -o $(BUILDDIR)/serialize_test serialize_test.o ../library/serialize.o

bin_targets: $(BINDIR)/$(BIN_TARGETS)

$(BINDIR)/%: %.o

lib_targets: $(LIBDIR)/$(LIB_TARGETS)
one: socket_test.o
	$(CC) -o $(BUILDDIR)/socket_test socket_test.o

test:
	echo "Hello World! $(BUILDDIR)"

clean:
	rm $(BUILDDIR)/*.o
