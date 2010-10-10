###
# socketproxy/Makefile
# (c) 2010 Mike Doyle
#

loc:
	wc -l `find . | egrep "(Makefile|\.c|\.sh|\.pl|\.h)$$"`
tarball:
	cd ..
	tar czvf ../socketproxy-`date +'%Y%m%d'`.tgz .

clean:
	rm -r build/*

