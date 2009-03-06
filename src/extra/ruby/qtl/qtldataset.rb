require 'qtl/qtlmarker'
require 'qtl/qtlphenotype'
require 'qtl/qtlindividual'

class QtlDataset
  # attr_reader :individuals, :phenotypes, :markers
  NA = '-'

  def initialize alleles, genotypes, na
    @allowed_alleles      = alleles
    @allowed_genotypes    = genotypes
    @allowed_na           = na

    @individuals          = []
    @markers              = []
    @phenotypes           = []
  end

  def set_phenotypecolumn column, name
    @phenotypes[column] = QtlPhenotype.new(name)
  end

  def phenotypecolumn column
    @phenotypecolumns[column]
  end

  def set_phenotype ind, pid, value
    value = NA if @allowed_na.include?(value)
    individual(ind).phenotypes[pid] = value
  end

  def set_marker mid, name, chromosome, pos
    @markers[mid] = QtlMarker.new(name, chromosome, pos)
  end

  def set_genotype ind, mid, value
    # test if it has legal value
    raise "Genotype error for individual #{ind}, marker #{mid}, value #{value}" if !@allowed_na.include?(value) and !@allowed_genotypes.include?(value)
    value = NA if @allowed_na.include?(value)
    individual(ind).genotypes[mid] = value
  end

  def individual ind
    @individuals[ind] = QtlIndividual.new if @individuals[ind] == nil
    @individuals[ind]
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
