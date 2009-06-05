require 'qtl/utils/namecounter'

# Keeps track of Genotypes used

class QtlGenotypeName


end

class QtlGenotypeNames < NameCounter

  NA = '-'

end

class QtlValidateGenotypes

  attr_reader :alleles, :genotypes, :na
  # Example alleles=['A','B'], genotypes=['A','H','B','D','C'], na=['-','NA']
  def initialize alleles, genotypes, na=['-','NA']
    @alleles = alleles
    @genotypes = genotypes
    @na = na
  end

  def validated value
    return value if @genotypes==nil
    raise "Genotype error for value #{nvalue}" if !@na.include?(value) and !@genotypes.include?(value)
    value = QtlGenotypeNames::NA if @na.include?(value)
    value
  end

end

class QtlGenotype

  attr_reader :value

  def set nvalue, genotypeinfo
    nvalue = genotypeinfo.validated(nvalue)
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

  def set mid, value, genotypeinfo
    self[mid] = QtlGenotype.new() if !self[mid]
    self[mid].set(value, genotypeinfo)
    @genotypenames.add(self[mid].value)
  end

  def names
    @genotypenames.keys
  end

end

# State class for dataset
class QtlGenotypeInfo

  attr_reader :namesread

  def initialize validategenotypes
    @validategenotypes = validategenotypes
    @validategenotypes = QtlValidateGenotypes.new(nil,nil) if !validategenotypes
    @namesread = NameCounter.new
    @names     
  end

  def validated value
    @namesread.add(value)
    value = @validategenotypes.validated(value)
    value
  end

  def names
    @namesread.keys - [ QtlGenotypeNames::NA ]
  end

  def na
    @validategenotypes.na
  end

  def alleles
    @validategenotypes.alleles
  end
end
