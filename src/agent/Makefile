##
# socketproxy/src/agent/Makefile
# (c) 2010 Mike Doyle
#

BUILDDIR ?= .
BINDIR ?= .
LIBDIR ?= .

syntax:
	perl -c *.pl

all: soxprox-agent

soxprox-agent: soxprox-agent.pl
	cp soxprox-agent.pl $(BINDIR)/soxprox-agent

clean:
	rm -f $(BINDIR)/soxprox-agent
