# Keeps track of Genotypes used

class QtlGenotypeName


end

class QtlGenotypeNames < Hash

  NA = '-'

  def add name
    self[name] = 0 if self[name]==nil
    self[name] += 1
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
    @value
  end

  def genotyped?
    value != QtlGenotypeNames::NA
  end

end

# Every individual has a range of genotypes
class QtlGenotypes < Array

  def initialize 
    super
    @genotypenames = QtlGenotypeNames.new
  end

  def set mid, value, validategenotypes=nil
    self[mid] = QtlGenotype.new() if !self[mid]
    self[mid].set(value, validategenotypes)
    @genotypenames.add(self[mid].value)
  end

  def names
    @genotypenames.keys
  end
end

# State class for dataset
class QtlGenotypeInfo
end
