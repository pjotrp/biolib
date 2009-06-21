require 'qtl/qtlmarker'
require 'qtl/qtlphenotype'
require 'qtl/qtlgenotype'
require 'qtl/qtlindividual'
require 'qtl/qtlchromosome'
require 'qtl/qtlmap'
require 'qtl/input/qtlnormalize'

class QtlDataset

  include QtlNormalize, Contract

  attr_reader :individuals, :markers, :phenotypenames, :chromosomes, :genotypes, :map
  attr_reader :addcov, :intcov

  def initialize validategenotypes=nil
    @individuals          = QtlIndividuals.new
    @markers              = QtlMarkers.new
    @phenotypenames       = QtlPhenotypeNames.new
    @chromosomes          = QtlChromosomes.new(@markers)
    @genotypes            = QtlGenotypeInfo.new(validategenotypes)
    @addcov = []
    @intcov = []
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

  def naddcov
    0
  end

  def nintcov
    0
  end

  # Fetch genotype info by individual/marker (QtlMarker, name or mid)
  def genotype ind, m_id
    contract("Unknown individual #{ind}") { @individuals[ind] != nil }
    if m_id.kind_of?(QtlMarker)
      mid = m_id.mid
    elsif m_id.kind_of?(String)
      mid = @markers[m_id].mid
    else
      mid = m_id
    end
    return 'NA' if mid==nil or @individuals[ind].genotypes[mid]==nil
    @individuals[ind].genotypes[mid].value
  end

  # Fetch phenotype info by individual/pid
  def phenotype ind, pid
    @individuals[ind].phenotypes[pid].value
  end

  # Return all phenotypes as an array of arrays
  def phenotypes
    pheno = []
    @individuals.each do | ind |
      pheno.push ind.phenotypes.to_a
    end
    pheno
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
    :f2
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

  def expand_markers! step
    @map = QtlMap.new(d.markers).expand(step)
  end
end


