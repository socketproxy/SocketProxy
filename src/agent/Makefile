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

BUILDDIR ?= .
BINDIR ?= .
LIBDIR ?= .

syntax:
	perl -c *.pl

all: soxprox-agent

soxprox-agent: soxprox-agent.pl.m4
	m4 soxprox-agent.pl.m4 > $(BINDIR)/soxprox-agent
	chmod +x $(BINDIR)/soxprox-agent

clean:
	rm -f 	$(BINDIR)/soxprox-agent 	\
		$(BINDIR)/soxprox_debug.err	\
		$(BINDIR)/soxprox_debug.log
