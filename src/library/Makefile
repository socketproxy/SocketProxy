# socketproxy/src/library/Makefile
# (c) 2010 Mike Doyle

.PHONY: library
LIBDIR ?= .

socket.o: socket.c socket.h serialize.h
	gcc -c socket.c

fifo_client.o: fifo_client.c fifo_client.h serialize.h

clean:
	rm *.o $(LIBDIR)/libmike.so.1

library:
	gcc -fPIC -c *.c
	gcc -shared -fPIC -Wl,-soname,libmike -o $(LIBDIR)/libmike.so.1 *.o
