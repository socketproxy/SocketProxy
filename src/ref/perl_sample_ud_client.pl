#!/usr/bin/perl -w

###
# socketproxy/src/ref/perl_sample_ud_client.pl
# (c) 2010 Mike Doyle
#

# From perlipc: http://perldoc.perl.org/perlipc.html


use Socket;
use strict;
my ($rendezvous, $line);

$rendezvous = shift || 'catsock';
socket(SOCK, PF_UNIX, SOCK_STREAM, 0) || die "socket: $!";
connect(SOCK, sockaddr_un($rendezvous)) || die "connect: $!";
while (defined($line = <SOCK>)) {
    print $line;
}
exit;
