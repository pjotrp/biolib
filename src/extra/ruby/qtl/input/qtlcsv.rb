# Reads a QTL CSV file into a QtlDataset, similar to R's read.cross 
# function as described in the R/QTL book

class QtlCsv < QtlDataset

  def initialize fn, validategenotypes=nil
    super(validategenotypes)
    File.open(fn) do | f |  
      # parse the file header
      l1 = f.gets.chomp.split(/,/) # markers
      l2 = f.gets.chomp.split(/,/) # chromosome number
      # count phenotypes
      phenotypenum = 0
      l2.each do | obj |
        break if obj != ''
        phenotypenum += 1
      end
      raise 'No phenotype columns defined ' if phenotypenum == 0
      # Set phenotype names
      (0..phenotypenum-1).each do | pid |
        set_phenotypename(pid,l1[pid])
      end
      # Check for map distance row
      line = f.gets
      l3 = line.chomp.split(/,/) # (optional) cM
      hasposrow = l3[0] == ''
      # Now set marker names and attributes
      (0..l1.size-phenotypenum-1).each do | mid |
        col = mid+phenotypenum
        set_marker(l1[col],l2[col],(hasposrow ? l3[col]:nil), mid)
      end
      line = f.gets if hasposrow 
      # Read rest of the rows
      i = 0
      loop {
        a = line.chomp.split(/,/)
        raise 'Size problem with line '+line if (a.size != l1.size)
        (0..phenotypenum-1).each do | pid |
          set_phenotype(i, pid, a[pid])
        end
        (0..a.size-phenotypenum-1).each do | mid |
          set_genotype(i, mid, a[mid+phenotypenum])
        end
        line = f.gets
        break if line == nil
        i += 1
      }
    end
    # p self
  end

end
