
class QtlIndividual
  attr_reader :phenotypes, :sex, :pgm, :genotypes

  def initialize
    @phenotypes = QtlPhenotypes.new
    @genotypes  = QtlGenotypes.new
  end

  def set_phenotype pid, value
    @phenotypes.set(pid,value)
  end

  def set_genotype mid, value, genotypeinfo
    @genotypes.set(mid, value, genotypeinfo)
  end

end

class QtlIndividuals < Array

  def individual ind
    self[ind] = QtlIndividual.new if self[ind]==nil
    self[ind]
  end

  def set_phenotype ind, pid, value
    individual(ind).set_phenotype(pid, value)
  end

  def set_genotype ind, mid, value, validategenotypes=nil
    individual(ind).set_genotype(mid, value, validategenotypes)
  end

  # Return of index
  def index
    Array.new(size) {|i| i} 
  end

end
