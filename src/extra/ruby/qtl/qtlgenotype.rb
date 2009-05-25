# Keeps track of Genotypes used

class QtlGenotypeName


end

class QtlGenotypeNames

  NA = '-'

  def initialize validategenotypes
  end

  def validated value
    # test if it has legal value
    # raise "Genotype error for individual #{ind}, marker #{mid}, value #{nvalue}" if !@allowed_na.include?(value) and !@allowed_genotypes.include?(value)
    # value = QtlGenotype::NA if @allowed_na.include?(value)
    value
  end
end

class QtlValidateGenotypes

  def initialize alleles=['A','B'], genotypes=['A','H','B','D','C'], na=['-','NA']
    @alleles = alleles
    @genotypes = genotypes
    @na = na
  end

end

class QtlGenotype

  attr_reader :value

  def set nvalue
    @value = nvalue
    # @value = @genotypenames.validated(nvalue)
  end

end

class QtlGenotypes < Array

  def initialize 
    super
  end

  def set mid, value
    self[mid] = QtlGenotype.new() if !self[mid]
    self[mid].set(value)
  end
end


