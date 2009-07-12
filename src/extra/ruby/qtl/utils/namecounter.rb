
class NameCounter < Hash

  def add value
    self[value] = 0 if !self[value]
    self[value] += 1
    self[value]
  end

end
