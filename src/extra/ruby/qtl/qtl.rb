require 'qtl/qtldataset'
require 'qtl/qtlcsv'

# QTL factory - based on the input type a QTL dataset is created

class QTL

  attr_reader :data

  def initialize fn
    if fn =~ /(CSV|csv)$/
      @data = QtlCsv.new(fn)
    end
    raise "Cannot determine format of #{fn}" if !@data
    @data.normalize
  end

end
