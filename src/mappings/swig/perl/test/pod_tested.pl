#!/usr/bin/perl

package pod_tested ;

use strict ;
use warnings ;

use Carp ;

use POD::Tested ; 
use File::Slurp ;
use Getopt::Long ;

use English qw( -no_match_vars ) ;
use Carp ;

use vars qw ($VERSION);
$VERSION     = '0.01' ;

my ($output, $input, $verbose, $verbose_pod_generation, $help) ;

if
	(
	GetOptions 
		(
		'i|input=s' => \$input,
		'o|output=s' => \$output,
		'v|verbose'  => \$verbose,
		'verbose_pod_generation'  => \$verbose_pod_generation,
		'help'  => \$help,
		)
	)
	{
	croak GetHelp() if(defined $help || (!defined $input));
	
	$output = $input . '.tested.pod' unless defined $output ;

	croak 'Input and output are the same!' if $input eq $output ;
	
	my @options_to_pod_tested ;
	push @options_to_pod_tested, (INPUT => $input) ;
	push @options_to_pod_tested, (VERBOSE  => $verbose) if defined $verbose ;
	push @options_to_pod_tested, (VERBOSE_POD_GENERATION  => $verbose_pod_generation) if defined $verbose_pod_generation ;
	
	my $parser = POD::Tested->new(@options_to_pod_tested, FILE => $input);

	my $test = Test::More->builder ;
	
	my $number_of_failed_tests = grep {$_->{ok} != 1} $test->details() ;

	if($number_of_failed_tests)
		{
		my @failed_indexes ;
		my $index = 1 ;
		
		for my $test ($test->details())
			{
			push @failed_indexes, $index unless $test->{ok} ;
			$index++ ;
			}
		
		my $list_of_failed = join(', ', @failed_indexes) ;
		print "# No POD output will be generated.\n# Failed tests: $list_of_failed.\n" or croak $ERRNO ;
		
		if(-e $output)
			{
			use File::Copy ;
			move $output, "${output}.failed_pod_tested.txt" ;
			print "# Moving '$output' to '${output}.failed_pod_tested.txt'\n" or croak $ERRNO ;
			}
		}
	else
		{
		print "# Generating POD in '$output'.\n" or croak $ERRNO ;
		write_file($output, $parser->GetPOD()) ;
		}
	}

#------------------------------------------------------------------------------

sub GetHelp
{
return <<'EOW' ;

Name
	pod_tested.pl
	
Synopsis
	perl pod_tested.pl -i pod_file
	
Description
	Extract POD and code and test it.
	
Options
	-i|input
	-o|output
	-v|verbose
	-verbose_pod_generation
	
Input file format

=head1 Config::Hierarchical cookbook

=begin common

  my $value = 'hi' ;
  print "value = '$value'\n" ;

=end common

Result:

=begin test

  is($value, 'hi') ;
  generate_pod("  value = '$value'\n") ;

=end test

=for POD::Tested reset

other text, including code (indented text) that is not checked

  indented pod code that is not checked

=cut

EOW
}

#------------------------------------------------------------------------------

1 ;
