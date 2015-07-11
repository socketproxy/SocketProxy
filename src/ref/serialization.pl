#!/usr/bin/perl -w

###
# socketproxy/src/ref/serialization.pl
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

sub
parse_request
{
    my $data = shift;

    my @messages = split (/\n\n/, $data); #TODO What if the data doesn't end with a \n\n?

    foreach my $message (@messages) {
        my @message_lines = split /\n/, $message;
        my %parsed_request;

        my $line = shift @message_lines;
        return undef unless $line =~ /^([_a-zA-Z][_a-zA-Z0-9]*)$/;
        $parsed_request{'command'} = $1;

        foreach $line (@message_lines) {

            return undef unless $line =~ /^([_a-zA-Z][_a-zA-Z0-9]*):\s+(\w+)$/;
            $parsed_request{params}->{$1} = $2;

        }
        return \%parsed_request;
    }# foreach $message
}# parse_request


sub
make_socket
{
    my $str = "socket\ndomain: ".PF_INET."\ntype: ".SOCK_STREAM."\nprotocol: 2\n\n"
}# make_socket

###
# Main
#

my $str = make_socket();
print $str;
my $req_ref = parse_request($str);

if ( !defined($req_ref) ) {
    exit 1;
}

print "Command: " . $req_ref->{command} . "\n"; 
my $foo = $req_ref->{params};
foreach my $key ( keys(%$foo) ) {
    print "\t$key:\t" . $req_ref->{params}->{$key} . "\n";
}
