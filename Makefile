###
# socketproxy/Makefile
# (c) 2010 Mike Doyle
#

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

