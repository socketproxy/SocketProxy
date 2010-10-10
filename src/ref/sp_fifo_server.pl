#!/usr/bin/perl -w

###
# socketproxy/src/ref/sp_fifo_server.pl
# (c) 2010 Mike Doyle
#

use strict;
use Socket; 
use POSIX;

###
# Design note: using fifos for the client/server IPC here because, unix domain
# sockets use the socket API that I'm stomping on. Also, unlike pipes, fifos
# can be opened read-write in linux.
#



###
# Configurables
#
$mask = "0777";


my $command_fifo;
my $rv = fork();
if (!defined($rv)) {
	die "Could not spawn a new process: $!\n";
}

my $ppid = getppid();

if ($rv == 0){ # Child
    $command_fifo = "/tmp/soxprox-$$-$ppid/command_fifo";
	print "I'm the child process,\t$command_fifo\n";
    child();
} else { # Parent
    $command_fifo = "/tmp/soxprox-$rv-$$"/command_fifo;
	print "I'm the parent process,\t$command_fifo\n";
    parent();
}

exit 0;


###
# Subroutines
#

sub
parent {
    parent_cmd_fifo();

}

sub
parent_cmd_fifo {
    use File::Basename;

    mkdir( dirname($command_fifo), $mask )
        || die "Couldn't make directory for $command_fifo";
    mkfifo( $command_fifo, $mask )
        || die "Couldn't make fifo $command_fifo";
}

sub 
child {
    sleep 1;
}

