#!/usr/bin/perl -w

##
# socketproxy/src/agent/soxprox_agent.pl
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
use Errno;

use Getopt::Std;


# Design note: using Socket instead of IO::Socket because
# according to the man page it is a h2xs tranlation of the
# C-based socket.h. This means that it has a far greater
# chance of getting the numbers right. This includes all of the
# commonly used pound-defines like AF_INET, SOCK_STREAM, etc.



###
# Initialization and global definitions.
#

# Set to create debug log files
my $debug;

our $opt_d = 0;
getopts('d');

if($opt_d == 1) {
	$debug = 1;
} else {
	$debug = 0;
}


# Vector for the various commands possible.
my %agent_commands;

# The hash of active sockets that this agent is using, along with an iterator
my %sockets;
my $sock_iter = 1;

if ($debug) {
#   open(OLD_STDERR,">&STDERR") or die "Failed to save STDERR";
    close ( STDERR );
    open (STDERR,">soxprox_debug.err") or die "Failed to redirect STDERR";
    open ( DEBUG, ">soxprox_debug.log" ) or die "Couldn't open debug log";
}

if ( $debug ) {
	print DEBUG "Debug mode on\n";
}

# Set up signal handlers.
$SIG{INT} = \&sig_int;


# Set up command dispatch hash.
$agent_commands{socket} = \&agent_command_socket;
$agent_commands{connect} = \&agent_command_connect;

###
# Main loop. Talk with the server over standard io.
#
while (1) {
    my $req = "";
    #my $buf = "";


    # Read a request from the server
    my $newlines = 0;
    for (;;) {

        my $n = sysread(STDIN, my $buf, 1);

        if ( $n == 0 ) {
            cleanup();
        }

        if( $debug ) { print DEBUG "Gotta char: $buf, n: $n\n"; }

        next if ( $req eq "" and $buf eq "\0" );

        if ( $buf eq "\n" ) {
            $newlines++;
        } else {
            $newlines = 0;
        }

        last if $newlines == 2;


        $req .= $buf;
    }

    if ( $debug ) {
        print DEBUG "Agent received request ($req)\n";
    }

    # Parse that request
    my $req_ref = parse_request($req);

    if ( !defined($req_ref) ) {
        print STDERR "Undefined req_ref\n";
        exit 1;
    }

    if ( $debug ) {
        print DEBUG "Command: " . $req_ref->{command} . "\n"; 
        my $foo = $req_ref->{params};
        foreach my $key ( keys(%$foo) ) {
            print DEBUG "\t$key:\t" . $req_ref->{params}->{$key} . "\n";
        }
    }

    my $func_ref;
    if ( !exists ($agent_commands{$req_ref->{command}}) ){
        print STDERR "No command " . $req_ref->{command} . "\n";
        exit 1;
    }

    $func_ref = $agent_commands{$req_ref->{command}};

    my $resp = &$func_ref($req_ref);

    if ( $debug ) {
        print DEBUG "Agent sending response to server: ($resp)\n";
    }

    syswrite ( STDOUT, "$resp\n" );


} # end of main loop



###
# Subroutines
#

sub
parse_request
{
    my $data = shift;

    my @messages = split (/\n\n/, $data); #TODO What if the data doesn't end with a \n\n?

    foreach my $message (@messages) {
        my @message_lines = split /\n/, $message;
        my %parsed_request = ();

        my $line = shift @message_lines;


        if ( $debug ) { print DEBUG "Line to parse: ($line)\n"; }
        
        if ( $line !~ /^([_a-zA-Z][_a-zA-Z0-9]*)$/ ) {
            print STDERR "First line does not match a command name: ($line)\n";
            return undef;
        }

        $parsed_request{'command'} = $1;

        foreach $line (@message_lines) {

            if ( $debug ) { print DEBUG "Line to parse: ($line)\n"; }
            if ( $line !~ /^([_a-zA-Z][-_a-zA-Z0-9]*):\s+([\w\.]+)$/ ) {
                print STDERR "Line does not match a parameter definition\n";
                return undef;
            }
            $parsed_request{params}->{$1} = $2;

        }
        return \%parsed_request;
    }# foreach $message
}# end of sub parse_request



##
# Agent commands
# 
# These all take in a fully populated command hash. They implement the 
# socket commands that the library shadows. 
#

sub
agent_command_socket {

    my $resp;

    # Sanity checks: 
    #   we were passed in something,
    #   what we were passed in looks like a command hash,
    #   this command hash is for a socket command,
    #   the socket command has the appropriate parameters defined,
    #   the parameters are valid integers,

    return 1 unless     ( defined ( my $cmd_hash = shift ) ); 
    return 1 unless     ( defined ( $cmd_hash->{command} ) ); 
    return 1 unless     ( $cmd_hash->{command} eq 'socket' );
    return 1 unless     ( defined ( $cmd_hash->{params}->{family} ) );
    return 1 unless     ( defined ( $cmd_hash->{params}->{type} ) );
    return 1 unless     ( defined ( $cmd_hash->{params}->{protocol} ) );
    return 1 unless     ( $cmd_hash->{params}->{family} =~ /^-?\d+$/ );
    return 1 unless     ( $cmd_hash->{params}->{type} =~ /^-?\d+$/ );
    return 1 unless     ( $cmd_hash->{params}->{protocol} =~ /^-?\d+$/ );
    if ( $debug ) { print DEBUG "in agent_command_socket\n"; }

    # Now all we lack is finishing up
    my $retval = socket (   my $tempsock,
                            $cmd_hash->{params}->{family},
                            $cmd_hash->{params}->{type},
                            $cmd_hash->{params}->{protocol} );


    # The documentation for Socket.pm doesn't say anything 
    # about error handling. This makes me sad. Here's what
    # I can do:

    if ( !defined ( $tempsock ) ) {
         $resp = "response\n"
                  . "command: " . $cmd_hash->{command} . "\n"
                  . "retval: -1\n"
                  . "errno: EACESS\n";

        return $resp;
    }

    # Stash the socket in the global socket hash for later use.
    $sockets{$sock_iter} = $tempsock;

    print DEBUG "Created socket # $tempsock " . fileno($tempsock). "\n";

    # Create a response and return it.
    $resp = "response\n"
             . "command: " . $cmd_hash->{command} . "\n"
             . "retval: $sock_iter\n";

    $sock_iter++;
    return $resp;

} # end of agent command socket


sub
agent_command_connect {

    my $resp;

    ###
    # Sanity checks: 
    #   we were passed in something,
    #   what we were passed in looks like a command hash,
    #   this command hash is for a connect command,
    #   the connect command has the appropriate parameters defined,
    #   the parameters are valid data types,

    return 1 unless     ( defined ( my $cmd_hash = shift ) ); 
    return 1 unless     ( defined ( $cmd_hash->{command} ) ); 
    return 1 unless     ( $cmd_hash->{command} eq 'connect' );

    my $params = $cmd_hash->{params};

    return 1 unless param_is_uint ( $cmd_hash->{params}, "sin_port" ) ;
    return 1 unless param_is_uint ( $cmd_hash->{params}, "addrlen" );
    return 1 unless param_is_ip ( $cmd_hash->{params}, "sin_addr" );

    return 1 unless param_is_uint ( $cmd_hash->{params}, "sockfd" );
    if ( !exists ( $sockets{$cmd_hash->{params}->{sockfd}} ) ) {
        print DEBUG "File descriptor is not a socket.\n";
        return 1;
    }

    my $sockfd = $sockets{$cmd_hash->{params}->{sockfd}};

    print DEBUG "Connect with socket # $sockfd " . fileno($sockfd). "\n";
    

    return 1 unless param_is_something (
        $cmd_hash->{params},
        "sin_family",
        qr/^AF_(INET|INET6|LOCAL|LINK)$/,
        "address family"
    );

    if ( $debug ) { print DEBUG "in agent_command_socket\n"; }


    # Now all we lack is finishing up

    ###
    # Make the connection
    #
    my $paddr = sockaddr_in(
        $cmd_hash->{params}->{sin_port},
        inet_aton($cmd_hash->{params}->{sin_addr})
    );

    my $retval = connect ( $sockfd, $paddr );

    # Get the numeric value of errno
     my $moneybang = $! + 0;

    # Create a response and return it.
    $resp = "response\n"
        . "command: " . $cmd_hash->{command} . "\n";

    if ( ! $retval ) {
        $resp .= "retval: -1\n";
        $resp .= "errno: " . get_c_errno($moneybang) . "\n";
    } else { 
        $resp .= "retval: 0\n";
    }

    return $resp;

} # end of agent_command_connect;



##
# Signal handlers
#
sub
sig_int {
    cleanup();
}

sub
cleanup {
    close ( DEBUG );
    close ( STDERR );
    exit(0);
}



##
# Validation routines
#

sub
param_is_uint {
    my $r = qr/^\d+$/;
    return param_is_something ( @_, $r, "unsigned int" );
} # end of param_is_uint

sub
param_is_int {
    my $r = qr/^-?\d+$/;
    return param_is_something ( @_, $r, "int" );
} # end of param_is_int

sub
param_is_id {
    return param_is_something ( @_, qr/^[_a-zA-Z][-a-zA-Z0-9]*$/, "identifier" );
} # end of param_is_id

sub
param_is_ip {
    return param_is_something ( 
        @_, 
        qr/^([012]?\d?\d\.){3}([012]?\d?\d)$/,
        "IP Address" );
}

sub
param_is_something {
    my $hashref = shift;
    my $name = shift;
    my $regex = shift;
    my $type = shift;

    if ( !exists($hashref->{$name}) ) {
        if ( $debug ) {
            print DEBUG "No parameter $name\n";
        }
        return 0;
    }

    if ( $hashref->{$name} !~ /$regex/) {
        if ( $debug ) {
            print DEBUG "$name is not a valid $type: " 
                . $hashref->{$name} 
                . "\n";
        }
        return 0;
    }

    return 1;
} # end of param_is_something

###
# get_c_errno
# finds the constant EFOO that was set and returns it as string "EFOO"
# takes in the $! value
#
sub
get_c_errno {

    my $moneybang = shift;

    # Note: $ERRNO is a synonym for $!. %ERRNO is a synonym for %!
    
    foreach my $key ( keys(%!) ) {
        if ( $!{$key} == $moneybang ) {
            return $key;
        }
    }
} # end of get_c_errno

