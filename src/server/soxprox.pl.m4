#!/usr/bin/perl -w

###
# socketproxy/src/server/soxprox.pl
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
use File::Basename;

my $client_fifo_mask = 0777;
my %alive;

###
# soxprox.pl -- The server component of Socket Proxy.
#
#
# roadmap:
#   parse the command line
#   make the agent
#   make the client
#   pass notes back and forth between the client and the agent.
#

$SIG{CHLD} = \&sig_chld;
$SIG{INT}  = \&sig_int;
my ( $agent_cmd, $client_cmd,    $debug )       = parse_cmdline();
my ( $agent_pid, $from_agent_fh, $to_agent_fh ) = make_agent($agent_cmd);
my ( $client_pid, $client_cmd_fifo ) = make_client($client_cmd);

###
# Main loop: pass notes back and forth from the client to the agent.
#
# In particular:
#   read from the client,
#   write to the agent,
#   read from the agent,
#   write to the client
while (1) {
    my $req  = "";
    my $resp = "";

    debug_print("Server: In main loop\n");

    # Read from the client
    open( CMD_FIFO, "<", $client_cmd_fifo ) or die $!;

    while ( sysread( CMD_FIFO, my $buf, 1024 ) != 0 ) {
        debug_print("Reading from fifo\n");
        $req .= $buf;
    }
    close(CMD_FIFO);

    debug_print("here's the request: $req\n");

    # Write to the agent
    syswrite( $to_agent_fh, $req );

    debug_print("Finished writing to agent\n");

    # Read from the agent
    my $newlines = 0;
    while ( sysread( $from_agent_fh, my $buf, 1 ) != 0 ) {

        if ( $buf eq "\n" ) {
            $newlines++;
        }
        else {
            $newlines = 0;
        }

        last if ( $newlines == 2 );

        $resp .= $buf;
    }

    debug_print("Server read response from agent: ($resp)\n");

    # Write to the client
    open( CMD_FIFO, ">", $client_cmd_fifo ) or die $!;
    syswrite( CMD_FIFO, "$resp" );
    close(CMD_FIFO);

    debug_print("Finished writing to client\n");

}

#<<<

include(SHARED_DIR/soxprox-shared.pl)

;

#>>>
###
# Parse the command line
#
#
sub parse_cmdline {
    use Getopt::Long;
    my ( $agent_cmd, $client_cmd, $help ) = ( '', '', '', '' );
    GetOptions(
        'agent=s'            => \$agent_cmd,
        'client=s'           => \$client_cmd,
        'client-fifo-mask=i' => \$client_fifo_mask,
        'debug'              => \$debug,
        'help'               => \$help
    );

    if ($help) {
        usage();
        exit 0;
    }

    debug_print(
        "agent command: $agent_cmd, client command: $client_cmd\n");

    if ( $agent_cmd eq '' or $client_cmd eq '' ) {
        usage();
        exit 1;
    }

    return ( $agent_cmd, $client_cmd, $debug )

     #TODO: input sanitization to mitigate command injection possibilities.
}    # end of sub parse_cmdline;

###
# Make the agent
#
# Portability note: "The open2() and open3() functions are unlikely to work
# anywhere except on a Unix system or some other one purporting to be POSIX
# compliant." --perlipc
sub make_agent {
    use FileHandle;
    use IPC::Open2;
    my $agent_cmd = shift;

    my ( $agent_pid, $from_agent_fh, $to_agent_fh );
    $agent_pid = open2( $from_agent_fh, $to_agent_fh, $agent_cmd );
    $alive{$agent_pid} = 1;
    return ( $agent_pid, $from_agent_fh, $to_agent_fh );
}    # end of sub make_agent

###
# sub make_client
#
# spawns the local client process and starts communication with it.
#
sub make_client {
    use POSIX;

    ###
    # XXX Work in progress: move from fifos to unix domain sockets. I was
    # using fifos previously because I wasn't using dlsym to shadow the
    # socket(2) related system calls.
    #

    my $client_cmd = shift;
    my $command_fifo;

    # This needs to be set pre-fork so that we're sure that the child
    # process's pause will catch correctly.
    $SIG{ALRM} = \&null_sig_catcher;

    my $rv = fork();
    if ( !defined($rv) ) {
        die "Could not spawn a new process: $!\n";
    }

    my $ppid = getppid();

    if ( $rv == 0 ) {    # Child

        # To give the parent time to make the fifo.
        pause();

        # Make our environment what we want here:
        if ( !-f $ENV{LIBDIR} . '/libmike.so.1' ) {
            die "Can't find my lib. libdir is " . $ENV{LIBDIR};
        }
        $ENV{LD_PRELOAD} = $ENV{LIBDIR} . '/libmike.so.1';

        exec($client_cmd)
          or die( 'Failed to exec client: $!. Libdir is ' . $ENV{LIBDIR} );

    }
    else {    # Parent

        # XXX Unix domain sockets also use file paths as addresses.
        # As such, this naming convention will continue to be used.
        #
        my $command_fifo = "/tmp/soxprox-$rv-$$/command_fifo";

        $alive{$rv} = 1;

        mkdir( dirname($command_fifo), $client_fifo_mask )
          || die "Couldn't make directory for $command_fifo";
        mkfifo( $command_fifo, $client_fifo_mask )
          || die "Couldn't make fifo $command_fifo: $!";

        sleep(3);
        kill( 'ALRM', $rv );

        return ( $rv, $command_fifo );
    }
}    # end of sub make_client;

sub sig_chld {
    my $sig = shift;

    my $dead_pid = wait;

    $alive{$dead_pid} = 0;
    debug_print("$dead_pid died!\n");

    cleanup();

}    # end of sig_chld

sub sig_int {
    cleanup();
}    # end of sig_int

sub null_sig_catcher {
    ;
}

sub cleanup {

    if (   ( defined $client_pid )
        && ( exists( $alive{$client_pid} ) )
        && ( $alive{$client_pid} == 1 ) )
    {
        kill( 'INT', $client_pid );
        if ( waitpid( $client_pid, 0 ) == $client_pid ) {
            $alive{$client_pid} = 0;
        }
    }

    if (   ( defined $agent_pid )
        && ( exists( $alive{$agent_pid} ) )
        && ( $alive{$agent_pid} == 1 ) )
    {
        kill( 'INT', $agent_pid );
        if ( waitpid( $agent_pid, 0 ) == $agent_pid ) {
            $alive{$agent_pid} = 0;
        }
    }

    close($from_agent_fh);
    close($to_agent_fh);

    exit(0);

}    # end of sub cleanup

sub usage {
    print "soxprox --help\n";
    print 'soxprox --agent="agent command" --client="client command"'
      . "\n";
    print "\n";
    print
"It's probably best to use double quotes around the commands. Here's an example:\n";
    print
'soxprox --agent="ssh user@target.example.com" --client="nmap -sP 10.1.1.0/255"'
      . "\n";
}    # end of sub usage
