require 'qtl/qtlmarker'
require 'qtl/qtlphenotype'

class QtlDataset
  # attr_reader :individuals, :phenotypes, :markers
  NA = '-'

  def initialize alleles, genotypes, na
    @used_alleles      = alleles
    @used_genotypes    = genotypes
    @used_na           = na
    @individuals       = []
    @markers           = []
    @genotypes         = []
    @phenotypecolumns  = []
    @phenotypes        = []
  end

  def set_phenotypecolumn column, name
    @phenotypecolumns[column] = QtlPhenotype.new(name)
  end

  def phenotypecolumn column
    @phenotypecolumns[column]
  end

  def set_phenotype ind, pid, value
    @phenotypes[pid] = [] if @phenotypes[pid] == nil
    value = NA if @used_na.include?(value)
    @phenotypes[pid][ind] = value
  end

  def set_marker mid, name, chromosome, pos
    @markers[mid] = QtlMarker.new(name, chromosome, pos)
  end

  def set_genotype ind, mid, value
    # test if it has legal value
    raise "Genotype error for individual #{ind}, marker #{mid}, value #{value}" if !@used_na.include?(value) and !@used_genotypes.include?(value)
    @genotypes[mid] = [] if @genotypes[mid] == nil
    value = NA if @used_na.include?(value)
    @genotypes[mid][ind] = value
  end

  # Return phenotype +num+ of individual +pid+
  def phenotype pid, num=0
    @phenotypes[pid]
  end

  # Return the information of marker +mid+
  def marker mid 
    @markers[mid]
  end
end
