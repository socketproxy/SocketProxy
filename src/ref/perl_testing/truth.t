#!/usr/bin/perl

# From http://www.perl.com/pub/2001/12/04/testing.html

print "1..3\n";

my $testnum = 1;
sub ok {
	my $condition = shift;
	print $condition ? "ok $testnum\n" : "not okay $testnum\n";
	$testnum++;
}

ok ( 1 );
ok ( '0 but true' );
ok ( ! 0 );

