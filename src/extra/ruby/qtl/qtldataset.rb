require 'qtl/qtlmarker'
require 'qtl/qtlphenotype'
require 'qtl/qtlgenotype'
require 'qtl/qtlindividual'
require 'qtl/qtlchromosome'
require 'qtl/input/qtlnormalize'

class QtlDataset

  include QtlNormalize

  attr_reader :individuals, :markers, :phenotypenames, :chromosomes, :genotypes

  def initialize validategenotypes=nil
    @individuals          = QtlIndividuals.new
    @markers              = QtlMarkers.new
    @phenotypenames       = QtlPhenotypeNames.new
    @chromosomes          = QtlChromosomes.new(@markers)
    @genotypes            = QtlGenotypeInfo.new(validategenotypes)
  end

  def individual ind
    @individuals[ind] = QtlIndividual.new if @individuals[ind] == nil
    @individuals[ind]
  end

  # The number of individuals (R/qtl type)
  def nind
    @individuals.size
  end

  # The number of chromosomes (R/qtl type)
  def nchr
    @chromosomes.size
  end

  # The number of markers on chromosomes (R/qtl type)
  def nmar
    @chromosomes.nmar
  end

  # Fetch genotype info by individual/marker(or mid)
  def genotype ind, name
    name = @markers[name].mid if name.kind_of?(String)
    @individuals[ind].genotypes[name].value
  end

  # Number of phenotypes
  def nphe
    @phenotypenames.size
  end

  # Return the information of marker +mid+
  def marker mid 
    @markers.by_id(mid)
  end

  def marker_by_name name
    @markers[name]
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
        countph[i] +=1 if ph != nil and ph.phenotyped?
      end
    end
    countph.map { | c | (c*1000.0/tot_phenotypes).round/10.0 }
  end

  def perc_genotyped
    tot_genotypes = @individuals[0].genotypes.size * @individuals.size
    c = 0
    @individuals.each_with_index do | ind, i |
      ind.genotypes.each do | g |
        c +=1 if g != nil and g.genotyped?
      end

    end
    (c*1000.0/tot_genotypes).round/10.0
  end

end


