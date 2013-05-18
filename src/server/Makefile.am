bin_SCRIPTS = soxprox
CLEANFILES = $(bin_SCRIPTS)
EXTRA_DIST = soxprox.pl

# XXX Add rules to do textual substitution of variables here. That way you
# can have a #!PERL that becomes #!/usr/bin/perl or #!/bin/perl or whatevs.
# Also, you can embed the version number in the usage message. See
# http://www.gnu.org/software/automake/manual/html_node/Scripts.html for
# an example. 

soxprox: soxprox.pl Makefile
	cp soxprox.pl soxprox
	chmod +x soxprox
