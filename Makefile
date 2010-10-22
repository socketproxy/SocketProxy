###
# socketproxy/Makefile
# (c) 2010 Mike Doyle
#

commit:
	git commit 
	#git remote add origin git@github.com:socketproxy/SocketProxy.git

push: commit
	git push origin master

loc:
	wc -l `find . | egrep "(Makefile|\.c|\.sh|\.pl|\.h)$$"`
tarball:
	cd ..
	tar czvf ../socketproxy-`date +'%Y%m%d'`.tgz .

clean:
	rm -r build/*

