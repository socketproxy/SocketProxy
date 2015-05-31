###
# socketproxy/Makefile
# (c) 2010 Mike Doyle
#

.PHONY: agent server library test commit push loc tarball diff clean
export BUILDDIR = $(PWD)/bin
export BINDIR = $(PWD)/bin
export LIBDIR = $(PWD)/lib

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
	rm -r build/*

