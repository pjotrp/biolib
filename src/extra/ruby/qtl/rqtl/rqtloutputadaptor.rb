
require 'qtl/qtlresult'

class RQtlOutputAdaptor

  def initialize input
    @input = input
  end

  def results lods
    mrs = []
    lods.each_with_index do | lod, i |
      mrs[i] = QtlResult.new(@input.marker(i),lod)
    end
    mrs
  end

end

class RQtlScanoneOutputAdaptor < RQtlOutputAdaptor
end
