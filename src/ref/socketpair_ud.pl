#!/usr/bin/perl -w

###
# socketproxy/src/ref/socketpair_ud.pl
# (c) 2010 Mike Doyle
#

use strict;
use Socket; 
# Design note: using Socket instead of IO::Socket because
# according to the man page it is a h2xs tranlation of the
# C-based socket.h. "This means that it has a far more likely 
# chance of getting the numbers right. This includes all of the 
# commonly used pound-defines like AF_INET, SOCK_STREAM, etc.



my $ud_file;
my $rv = fork();
if (!defined($rv)) {
	die "Could not spawn a new process: $!\n";
}

my $ppid = getppid();

if ($rv == 0){ # Child
    $ud_file = "/tmp/soxprox-$$-$ppid";
	print "I'm the child process,\t$ud_file\n";
    child();
} else { # Parent
    $ud_file = "/tmp/soxprox-$rv-$$";
	print "I'm the parent process,\t$ud_file\n";
    parent();
}

exit 0;


###
# Subroutines
#

sub
parent {
    my $sock;
    my $addr = $ud_file; # Unix domain sockets use files as addresses.
    socket ( $sock, AF_UNIX, SOCK_STREAM, 0 )
        || die "socket: $!";
    my $sun = pack_sockaddr_un($addr);
    unlink ( $addr );
    bind ( $sock, $sun );
    listen ( $sock, SOMAXCONN );
}

sub 
child {
    sleep 1;
}

