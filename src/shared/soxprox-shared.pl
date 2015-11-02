sub
debug_print
{
	use File::Basename;
	if ( $debug ) {
		my ($fullfile, $line) = (caller)[1,2];
		my $file = basename($fullfile);
		print STDERR "$file:$line: ", @_;
	}
}
