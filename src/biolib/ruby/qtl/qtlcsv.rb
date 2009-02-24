# Reads a QTL CSV file into a QtlDataset, similar to R's read.cross 
# function as described in the R/QTL book

class QtlCsv

  attr_reader :dataset

  def initialize fn, alleles=['A','B'], genotypes=['A','H','B','D','C'], na=['-','NA']
    File.new(fn) do | f |
      @dataset = QtlDataset.new
    end
  end

end
