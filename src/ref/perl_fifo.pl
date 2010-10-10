#!/usr/bin/perl -w

###
# socketproxy/src/ref/perl_fifo.pl
# (c) 2010 Mike Doyle
#

use strict;
#use Socket; 
use POSIX;

###
# Design note: using fifos for the client/server IPC here because, unix domain
# sockets use the socket API that I'm stomping on. Also, unlike pipes, fifos
# can be opened read-write in linux.
#



###
# Configurables
#
my $mask = 0777;


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
    $command_fifo = "/tmp/soxprox-$rv-$$/command_fifo";
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
    my ($req, $resp);
    $resp = "Ok";

    while(1) {

        $req = "";

        open (CMD_FIFO, "<", $command_fifo) or die $!;
        while (sysread(CMD_FIFO, my $buf, 1024) != 0){
            $req .= $buf;
        }
        close(CMD_FIFO);

        open (CMD_FIFO, ">", $command_fifo) or die $!;
        syswrite( CMD_FIFO, "$resp\n\n" );
        close (CMD_FIFO);

        print "Server message: $req response: $resp\n";
    }

}

sub
parent_cmd_fifo {
    use File::Basename;

    mkdir( dirname($command_fifo), $mask )
        || die "Couldn't make directory for $command_fifo";
    mkfifo( $command_fifo, $mask )
        || die "Couldn't make fifo $command_fifo: $!";
}

sub 
child {

    ###
    # I need to keep the protocol simple. While forever, the server reads 
    # the client's request, then the client reads the server's response.
    #

    my @messages = ( "Hey", "Teacher", "Leave", "Those", "Kids", "Alone" );
    my $resp;

    foreach my $mesg (@messages) {
        $resp = "";
        sleep 1 until -r $command_fifo;

        open (CMD_FIFO, ">", $command_fifo) or die $!;
        syswrite( CMD_FIFO, "$mesg\n\n" );
        close(CMD_FIFO);
        open (CMD_FIFO, "<", $command_fifo) or die $!;
        while (sysread(CMD_FIFO, my $buf, 1024) != 0){
            $resp .= $buf;
        }
        close (CMD_FIFO);
        print "Client message: $mesg response: $resp\n";
    }
}

