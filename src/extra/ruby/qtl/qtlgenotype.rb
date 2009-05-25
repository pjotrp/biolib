# Keeps track of Genotypes used

class QtlGenotypeName


end

class QtlGenotypeNames

  NA = '-'

  def initialize 
  end

end

class QtlValidateGenotypes

  def initialize alleles=['A','B'], genotypes=['A','H','B','D','C'], na=['-','NA']
    @alleles = alleles
    @allowed_genotypes = genotypes
    @allowed_na = na
  end

  def validated value
    raise "Genotype error for value #{nvalue}" if !@allowed_na.include?(value) and !@allowed_genotypes.include?(value)
    value = QtlGenotypeNames::NA if @allowed_na.include?(value)
    value
  end

end

class QtlGenotype

  attr_reader :value

  def set nvalue, validategenotypes
    nvalue = validategenotypes.validated(nvalue) if validategenotypes
    @value = nvalue
  end

  def genotyped?
    value != QtlGenotypeNames::NA
  end

end

class QtlGenotypes < Array

  def initialize 
    super
  end

  def set mid, value, validategenotypes=nil
    self[mid] = QtlGenotype.new() if !self[mid]
    self[mid].set(value, validategenotypes)
  end
end


