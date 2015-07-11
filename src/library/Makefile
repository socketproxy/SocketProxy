# socketproxy/src/library/Makefile
# (c) 2010 Mike Doyle

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
