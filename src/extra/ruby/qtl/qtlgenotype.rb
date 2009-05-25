require 'qtl/utils/namecounter'

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

  attr_reader :alleles, :genotypes, :na
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

  def initialize validategenotypes
    @validategenotypes = validategenotypes
    @namesused = NameCounter.new
  end

  def validated value
    @namesused.add(value)
    value = @validategenotypes.validated(value) if @validategenotypes
    value
  end

  def names
    @namesused.keys - [ QtlGenotypeNames::NA ]
  end

  def na
    @validategenotyeps.alleles
  end

  def alleles
    @validategenotyeps.alleles
  end
end
