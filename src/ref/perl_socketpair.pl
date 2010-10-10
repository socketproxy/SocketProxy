#!/usr/bin/perl -w

###
# socketproxy/src/ref/perl_socketpair.pl
# (c) 2010 Mike Doyle
#


# From http://perldoc.perl.org/perlipc.html

#!/usr/bin/perl -w
# pipe2 - bidirectional communication using socketpair
# "the best ones always go both ways"

use Socket;
use IO::Handle; # thousands of lines just for autoflush :-(
# We say AF_UNIX because although *_LOCAL is the
# POSIX 1003.1g form of the constant, many machines
# still don't have it.
socketpair(CHILD, PARENT, AF_UNIX, SOCK_STREAM, PF_UNSPEC)
or die "socketpair: $!";

CHILD->autoflush(1);
PARENT->autoflush(1);

if ($pid = fork) {
    close PARENT;
    print CHILD "Parent Pid $$ is sending this\n";
    chomp($line = <CHILD>);
    print "Parent Pid $$ just read this: `$line'\n";
    close CHILD;
    waitpid($pid,0);
} else {
    die "cannot fork: $!" unless defined $pid;
    close CHILD;
    chomp($line = <PARENT>);
    print "Child Pid $$ just read this: `$line'\n";
    print PARENT "Child Pid $$ is sending this\n";
    close PARENT;
    exit;
}

