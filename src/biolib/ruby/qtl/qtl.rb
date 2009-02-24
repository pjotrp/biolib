require 'qtl/qtldataset'
require 'qtl/qtlcsv'

class QTL

  def initialize fn
    if fn =~ /(CSV|csv)$/
      @data = QtlCsv.new(fn)
    end
    raise "Cannot determine format of #{fn}" if !@data
  end
end
