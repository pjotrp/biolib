# Programming by contract
#

module Contract
  def contract msg, &block
    res = yield block
    if res == false
      raise "Contract error: #{msg}"
    end
  end
end
