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

Fetch the loaded data and check the type (unknown at this point)

  >> d = qtl.data
  >> d.type
  => 'F2 intercross'

Return the number of individuals

  >> d.individuals.size
  => 120

The short notation - get number of individuals

  >> d.nind
  => 120

Number of phenotypes

  >> d.nphe
  => 3

Number of markers

  d.totmar
  => 133

Number of chromosomes

  d.nchr
  => 20

  {'1'=>13,'2'=>6},d.nmar)
  'D10M44',d.marker(0).name)
  '2',d.marker(14).chromosome)
  133,d.markers.size)
  20,d.chromosomes.size)
  19,d.chromosomes.autosomes.size)
  'X',d.chromosomes.x.name)
  13,d.chromosomes[1].markers.size)
  'T264',d.phenotypecolumn(0).name)
  2,d.phenotypecolumns.size)
  [96.7, 100],d.perc_phenotyped)

  88.5,d.perc_genotyped)
=end

