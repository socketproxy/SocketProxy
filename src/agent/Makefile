##
# socketproxy/src/agent/Makefile
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

.PHONY: syntax all clean

# When other Makefiles call this one recursively, the below values are
# overwritten.
BUILDDIR ?= .
BINDIR ?= .
LIBDIR ?= .
SRCDIR ?= ..
export BINDIR BUILDDIR LIBDIR SRCDIR

syntax: soxprox-agent.pl
	perl -c *.pl

all: soxprox-agent

soxprox-agent.pl: soxprox-agent.pl.m4
	m4 soxprox-agent.pl.m4 > soxprox-agent.pl
	chmod +x soxprox-agent.pl

soxprox-agent: soxprox-agent.pl soxprox-agent.pl
	cp soxprox-agent.pl $(BINDIR)/soxprox-agent

clean:
	rm -f   soxprox-agent.pl
	rm -f 	$(BINDIR)/soxprox-agent 	\
		$(BINDIR)/soxprox_debug.err	\
		$(BINDIR)/soxprox_debug.log
