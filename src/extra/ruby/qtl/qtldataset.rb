require 'qtl/qtlmarker'
require 'qtl/qtlphenotype'
require 'qtl/qtlindividual'

class QtlDataset
  attr_reader :individuals, :markers, :phenotypes, :chromosomes
  NA = '-'

  def initialize alleles, genotypes, na
    @allowed_alleles      = alleles
    @allowed_genotypes    = genotypes
    @allowed_na           = na

    @individuals          = []
    @markers              = []
    @phenotypes           = []
    @chromosomes          = QTLChromosomes.new(@markers)
  end

  def set_phenotypecolumn column, name
    @phenotypes[column] = QtlPhenotype.new(name)
  end

  def phenotypecolumn column
    @phenotypes[column]
  end

  def phenotypecolumns
    @phenotypes
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

  # The number of individuals
  def nind
    @individuals.size
  end

  # The number of chromosomes
  def nchr
    chr = {}
    @markers.each do | marker |
      chr[marker.chromosome] = 0 if !chr[marker.chromosome]
      chr[marker.chromosome] += 1
    end
    chr.size
  end

  def nmar
    chr = {}
    @markers.each do | marker |
      chr[marker.chromosome] = 0 if !chr[marker.chromosome]
      chr[marker.chromosome] += 1
    end
    chr
  end

  # Return phenotype +num+ of individual +pid+
  def phenotype pid, num=0
    @phenotypes[pid]
  end

  # Number of phenotypes
  def nphe
    @phenotypes.size
  end

  # Return the information of marker +mid+
  def marker mid 
    @markers[mid]
  end

  # The total number of markers
  def totmar
    @markers.size
  end

  # Return the type of the experiment as a string
  def type
    'F2'
  end

  def perc_phenotyped
    tot_phenotypes = @individuals[0].phenotypes.size * @individuals.size
    countph = []
    @individuals.each do | ind |
      ind.phenotypes.each_with_index do | ph, i |
        countph[i] = 0 if countph[i] == nil
        countph[i] +=1 if ph != nil and ph != NA
      end
    end
    countph.map { | c | (c*1000.0/tot_phenotypes).round/10.0 }
  end

  def perc_genotyped
    tot_genotypes = @individuals[0].genotypes.size * @individuals.size
    c = 0
    @individuals.each_with_index do | ind, i |
      ind.genotypes.each do | g |
        c +=1 if g != nil and g != NA
      end
    end
    (c*1000.0/tot_genotypes).round/10.0
  end

end

class QTLChromosomes

  def initialize markers
    @markers = markers
  end

  def chromosomes
    chr = {}
    @markers.each do | marker |
      chr[marker.chromosome] = 0 if !chr[marker.chromosome]
      chr[marker.chromosome] += 1
    end
    chr
  end

  def hasX?
    chromosomes['X'] != nil
  end

  def size
    chromosomes.size
  end

  def autosomes
    res = chromosomes.reject {|k,v| k=='X'}
    # size - (hasX? ? 1:0)
    res
  end

  def markers
    @markers
  end
end
