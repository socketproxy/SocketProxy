##
# socketproxy/src/server/Makefile
# (c) 2010 Mike Doyle
#

BUILDDIR ?= .
BINDIR ?= .
LIBDIR ?= .

syntax:
	perl -c *.pl

all: soxprox

soxprox:
	cp soxprox.pl $(BINDIR)/soxprox

clean:
	rm -f $(BINDIR)/soxprox
