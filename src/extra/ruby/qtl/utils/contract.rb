# Programming by contract
#

module Contract
  def contract msg, &block
    res = yield block
    if res == false
      raise "Contract error: #{msg}"
    end
  end

  def contract_warn msg, &block
    res = yield block
    if res == false
      print "Contract failed (warning): #{msg}"
    end
  end
end
