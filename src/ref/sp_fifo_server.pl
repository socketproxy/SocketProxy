#!/usr/bin/perl -w

###
# socketproxy/src/ref/sp_fifo_server.pl
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

