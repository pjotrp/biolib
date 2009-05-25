# Keeps track of Genotypes used

class QtlGenotypeName

  NA = '-'

end

class QtlGenotypeNames

  def initialize alleles, genotypes, na
    @alleles = alleles
    @genotypes = genotypes
    @na = na
  end

end

class QtlGenotype

  NA = QtlGenotypeName::NA

  attr_reader :value

  def set nvalue
    # test if it has legal value
    # raise "Genotype error for individual #{ind}, marker #{mid}, value #{value}" if !@allowed_na.include?(value) and !@allowed_genotypes.include?(value)
    # value = QtlGenotype::NA if @allowed_na.include?(value)
    @value = nvalue
  end

end

class QtlGenotypes < Array

  def set mid, value
    self[mid] = QtlGenotype.new if !self[mid]
    self[mid].set(value)
  end
end


