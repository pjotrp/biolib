# Ruby DocTest

=begin

Here we load the R/QTL Listeria dataset (from a CSV) and verify the
resulting information matches that of the R version.

Find the special classes for loading QTL input files (part of BioLib 'extra').

  >> $: << '..'
  >> require 'qtl/qtl'

Locate the Listeria input file
 
  >> TESTDATADIR = '../../../test/data/qtl'
  >> LISTERIA  = TESTDATADIR+'/listeria.csv'
  >> File.exist?(LISTERIA)
  => true

Load the Listeria CSV file into a QTL object

  >> qtl = QTL.new(LISTERIA)

Fetch the loaded data and check the type (defaults to F2 at this point)
R/QTL makes it an F2 intercross based on the number of genotypes

  >> d = qtl.data
  >> d.type
  => 'F2'

Return the number of individuals

  >> d.individuals.size
  => 120

The short notation - get number of individuals

  >> d.nind
  => 120

Number of phenotypes (T264. R/QTL adds sex and pgm automagically)

  >> d.nphe
  => 1

Number of markers

  >> d.totmar
  => 133

Number of chromosomes

  >> d.nchr
  => 20

Markers per chromosome

  >> d.nmar.sort
  => [["1", 13], ["10", 5], ["11", 6], ["12", 6], ["13", 12], ["14", 4], ["15", 8], ["16", 4], ["17", 4], ["18", 4], ["19", 4], ["2", 6], ["3", 6], ["4", 4], ["5", 13], ["6", 13], ["7", 6], ["8", 6], ["9", 7], ["X", 2]]

  >> d.marker(0).name
  => 'D10M44'

  >>  d.marker(14).chromosome
  => '2'

  >> d.markers.size
  => 133

Chromosome info

  >> d.chromosomes.size
  => 20
  >> d.chromosomes.autosomes.size
  => 19
  >> d.chromosomes.x.name
  => 'X'
  >> d.chromosomes[1].markers.size
  => 13

Phenotype column info

  >> d.phenotypecolumn(0).name
  => 'T264'
  >> d.phenotypecolumns.size
  => 2

Get statistics

  >> d.perc_phenotyped
  => [96.7, 100]
  >> d.perc_genotyped
  => 88.5

=end

