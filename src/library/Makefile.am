# socketproxy/src/library/Makefile.am
# (c) 2013 Mike Doyle

# TODO: Figure out what the hell I'm doing here.

lib_LTLIBRARIES = libsoxprox.la
libsoxprox_la_SOURCES = fifo_client.c fifo_client.h is_open.c is_open.h \
	serialize.c serialize.h socket.c socket.h udp.h uds_client.c \
	uds_client.h xunistdx.c xunistdx.h

socket.o: socket.c socket.h serialize.h
	gcc -c socket.c

fifo_client.o: fifo_client.c fifo_client.h serialize.h

clean:
	rm *.o
