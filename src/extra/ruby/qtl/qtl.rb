require 'qtl/qtldataset'
require 'qtl/input/qtlcsv'
require 'qtl/rqtl/rqtl'

# QTL factory - based on the input type a QTL dataset is created

class QTL

  attr_reader :data

  def initialize fn, validategenotypes=nil
    if fn =~ /(CSV|csv)$/
      @data = QtlCsv.new(fn,validategenotypes)
    end
    raise "Cannot determine format of #{fn}" if !@data
    @data.normalize
  end

end
