###
# socketproxy/Makefile
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
#
.PHONY: agent server library test commit push loc tarball diff clean
export BUILDDIR = $(PWD)/bin
export BINDIR = $(PWD)/bin
export LIBDIR = $(PWD)/lib

all: agent server library

add: clean
	git add .
agent:
	$(MAKE) -C src agent

server:
	$(MAKE) -C src server

library:
	$(MAKE) -C src library

test:
	$(MAKE) -C src test

commit:
	git commit 

push: commit
	git push origin

loc:
	wc -l `find . | egrep "(Makefile|\.c|\.sh|\.pl|\.h)$$"`
tarball:
	cd ..
	tar czvf ../socketproxy-`date +'%Y%m%d'`.tgz .

diff:
	echo Not added
	git diff
	echo Added, not committed 
	git diff --cached

clean:
	rm -f soxprox_debug.err  soxprox_debug.log
	rm -f $(BUILDDIR)/*
	rm -f $(BINDIR)/*
	$(MAKE) -C src clean
