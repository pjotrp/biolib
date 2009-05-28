    # value = QtlGenotype::NA if @allowed_na.include?(value)
    # individual(ind).phenotypes[pid] = value

class QtlPhenotypeName

  attr_reader :name

  def initialize name
    @name = name
  end
end

class QtlPhenotypeNames < Array

  NA = '-'

  def set idx, value
    self[idx] = QtlPhenotypeName.new(value)
  end

end

module QtlValidatePhenotypes
  def QtlValidatePhenotypes::na? name
    [QtlPhenotypeNames::NA,'NA',nil].include?(name)
  end
end

class QtlPhenotype
  attr_reader :value

  # Set the phenotype, converting strings to numbers, when applicable.
  def set(nvalue)
    if (nvalue == nvalue.to_i.to_s)
      nvalue = nvalue.to_i
    end
    if (nvalue == nvalue.to_f.to_s)
      nvalue = nvalue.to_f
    end
    @value = nvalue
  end

  def phenotyped?
    !QtlValidatePhenotypes::na?(@value)
  end
end

class QtlPhenotypes < Array

  def set pid, value
    self[pid] = QtlPhenotype.new if !self[pid]
    self[pid].set(value)
  end

  def to_a
    collect { | ph | ph.value }
  end

end

