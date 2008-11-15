# Unit tests for Affyio from Ruby
#
# Author: Pjotr Prins

$: << '../../../../biolib/ruby'

require 'affyio'
require 'test/biolibtest'
require 'test/unit/testcase'

class Test_Biolib_Affyio < Test::Unit::TestCase

  # All tests in one method - otherwise setup will reload all CEL files every time
  #
  def test_all
    datadir = $test_cwd+'/../../../../test/data/microarray/affy'
    @microarrays = []
    # ---- Locate the microarrays (CEL files) and load them. Equivalent to R's
    #  
    #  library(affy)
    #  m <- ReadAffy()
    #
    Dir.new(datadir).sort.each do | fn |
      if fn =~ /CEL/
        p fn
        @microarrays.push Biolib::Affyio.open_celfile(datadir+'/'+fn)
      end
    end
    # ---- Load the CDF file. This is automatically done by R, but you
    #      may want to recreate (using test.cdf) something like:
    #
    #  library(makecdfenv)
    #  make.cdf.package('test.cdf',species='test')
    #  exit and R CMD INSTALL testcdf/
    #  m <- ReadAffy(cdfname='test')

    @cdf = Biolib::Affyio.open_cdffile(BiolibTest.fetch("test_cdf.dat.gz",true))
    ltest_cdfinfo
    ltest_exprs
    ltest_genenames
    ltest_probeindex
    ltest_pm
    # ---- Release memory
    Biolib::Affyio.close_cdffile(@cdf)
    @microarrays.each { | m | Biolib::Affyio.close_celfile(m) }
  end

  def ltest_cdfinfo
    assert_equal(712,@cdf.cols)
    assert_equal(712,@cdf.rows)
    assert_equal(22293,Biolib::Affyio.cdf_num_probesets(@cdf))
  end

  def ltest_exprs
    # Test straight expression values of the array; as in R exprs(m)[1,1]
    row0 = [ 142.3, 90.5, 217.5, 123.8, 114.0, 299.3, 72.5, 95.3 ]
    row1 = [ 71.8,114.3,95,92.5,76,166.5,105.8,80.5 ]
    row5 = [ 350,669.8,555.5,291.5,474.8,777.8,309,507 ]
    row0.each_with_index do | e, i |
      assert_equal(e,Biolib::Affyio.cel_intensity(@microarrays[i],1-1))
    end
    row1.each_with_index do | e, i |
      assert_equal(e,Biolib::Affyio.cel_intensity(@microarrays[i],151111-1))
    end
    row5.each_with_index do | e, i |
      assert_equal(e,Biolib::Affyio.cel_intensity(@microarrays[i],500000-1))
    end
  end

  def ltest_genenames
    # Get the probeset names; as in R:
    #   geneNames(m)[1]     "1007_s_at"
    #   geneNames(m)[15111] "215738_at"
    #   geneNames(m)[21232] "221872_at"
    @probesets = []
    probeset = Biolib::Affyio.cdf_probeset_info(@cdf,1-1)
    assert_equal("AFFX-BioB-5_at",probeset.name)
    @probesets.push probeset
    # p probeset.pm_num
    # (0..probeset.pm_num).each do | i |
    #   p i
    #   probe = Biolib::Affyio.cdf_pmprobe_info(@cdf,0,i)
    #   p [ 'pm:xy', probe.x, probe.y ]
    # end
    assert_equal("215197_at",Biolib::Affyio.cdf_probeset_info(@cdf,15111-1).name)
    assert_equal("221329_at",Biolib::Affyio.cdf_probeset_info(@cdf,21232-1).name)
    @probesets.push(Biolib::Affyio.cdf_probeset_info(@cdf,15111-1))
    @probesets.push(Biolib::Affyio.cdf_probeset_info(@cdf,21232-1))
  end

  def ltest_probeindex
     cols = @cdf.cols
     # indexProbes(m, which="pm", genenames="AFFX-BioB-5_at")[[1]]
     #  [1] 268586   2471 309786 368170 216003 231967 230380 230277 176105 429597
     #  [11] 233003 130469 216301  55247  43800 100819 417952 368587 122411 382699
     pm0 = [ 268586,2471,309786,368170,216003,231967,230380,230277,176105,429597,233003,130469,216301,55247,43800,100819,417952,368587,122411,382699 ]
     mm0 = [ 269298,3183,310498,368882,216715,232679,231092,230989,176817,430309,233715,131181,217013,55959,44512,101531,418664,369299,123123,383411 ]
     pm0.each_with_index do | index, i |
       probe = Biolib::Affyio.cdf_pmprobe_info(@cdf,0,i)
       # p [ index, probe.x, probe.y, probe.x + probe.y*@cdf.cols + 1]
       assert_equal(index, probe.x + probe.y*cols + 1 )
     end
     pm0.each_with_index do | index, i |
       probe = Biolib::Affyio.cdf_pmprobe_info(@cdf,0,i)
       assert_equal(index, probe.x + probe.y*cols + 1 )
     end
     mm0.each_with_index do | index, i |
       probe = Biolib::Affyio.cdf_mmprobe_info(@cdf,0,i)
       assert_equal(index, probe.x + probe.y*cols + 1 )
     end
     # > cat(indexProbes(m, which="pm", genenames="215197_at")[[1]],sep=",") 
     pm1 = [ 320312,458144,134651,376656,2236,317393,213450,425650,77653,419474,35092 ]
     mm1 = [ 321024,458856,135363,377368,2948,318105,214162,426362,78365,420186,35804 ]
     pm1.each_with_index do | index, i |
       probe = Biolib::Affyio.cdf_pmprobe_info(@cdf,15111-1,i)
       assert_equal(index, probe.x + probe.y*cols + 1 )
     end
     mm1.each_with_index do | index, i |
       probe = Biolib::Affyio.cdf_mmprobe_info(@cdf,15111-1,i)
       assert_equal(index, probe.x + probe.y*cols + 1 )
     end
  end

  def ltest_pm
    # Test PM values; as in R's pm(m)[1,1:8]
    #  mypmindex <- pmindex(m,"AFFX-BioB-5_at")
    #  intensity(m)[mypmindex$`AFFX-BioB-5_at`,2]
    # Bioconductor 1.9 - even with test.cdf ought to be
    row = [ 665,655.8,591.3,117.5,697.8,1220.8,2763.8,2765.3,2989.3,875.8,625,229,261.3,109.8,801.3,258.3,433.3,186.8,227.5,662 ]
    row.each_with_index do | e, i |
      # p Biolib::Affyio.cel_pm(@microarrays[1],@cdf,1-1,i)
      assert_equal(e,Biolib::Affyio.cel_pm(@microarrays[1],@cdf,1-1,i))
    end
    # Test PM values; as in R's pm(m)[1,1:8]
    #  mypmindex <- pmindex(m,"215197_at")
    #  intensity(m)[mypmindex$`215197_at`,1]
    # These are Bioconductor 1.9 mappings; they differ in a few places:
    row = [ 62.3,108,346.3,47.3,70,57.5,70,119,121.5,60,254.3 ]

    row.each_with_index do | e, i |
      # p Biolib::Affyio.cel_pm(@microarrays[0],@cdf,15111-1,i)
      assert_equal(e,Biolib::Affyio.cel_pm(@microarrays[0],@cdf,15111-1,i))
    end
  end

end

class Dummy

  def test_mm
    row0 = [ 162,257.8,189.8,107.3,190,278.3,190,214.3 ]
    row1 = [ 64,73,66,71.8,60.3,81.3,88,78.3 ]
  end

end


if $0 == __FILE__
  # The following is run when invoked from the command line (not part 
  # of the actual unit test)

  cdf = nil

  datadir = '../../../../test/data/microarray/affy'
  cdffilename = '/tmp/test_cdf.dat'
  celfilename = datadir + '/test46.CEL.gz'
  celfilename = datadir + '/test_binary.cel.gz'
  if File.exist?(cdffilename)
    print "Loading #{cdffilename}..."
    cdf = Biolib::Affyio.open_cdffile(cdffilename)
    if cdf.isText
      print "Textual " 
    else
      print "XDAtype "
    end
    if cdf
      print "CDFinfo probesets=",Biolib::Affyio.cdf_num_probesets(cdf)
      (0..3).each do | i |
        probeset = Biolib::Affyio.cdf_probeset_info(cdf,i);
        print "\n",probeset.pm_num
        print ", x=",Biolib::Affyio.cdf_pmprobe_info(cdf,i,0).x
      end
    end
    print "\n"
  end

  fn = BiolibTest.fetch(celfilename)
  celobject = Biolib::Affyio.open_celfile(fn)
  p celobject.id
  raise 'FAULT' if celobject.id != '[CEL]'
  print 'rows=',Biolib::Affyio.cel_num_rows(celobject),"\n"
  print 'cols=',Biolib::Affyio.cel_num_cols(celobject),"\n"

  p celobject.cel.header.rows
  p celobject.cel.header.Algorithm
  p celobject.cel.header
  p celobject.cel.nmasks
  p celobject.cel.noutliers

  # ---- Read the first 10 intensities
  (0..10).each do | i |
    print Biolib::Affyio.cel_intensity(celobject,i),', '
  end

  # ---- Get the outliers
  print "\nOutliers: "
  (0..Biolib::Affyio.cel_num_outliers(celobject)-1).each do | i |
    print Biolib::Affyio.cel_outlier(celobject,i),', '
  end

  if cdf and celobject
    # ---- Get the first three probesets PM values
    print "\nPMs: "
    (0..3).each do | probeset |
      pset = Biolib::Affyio.cdf_probeset_info(cdf,probeset)
      print "\nName=",pset.name,' ; pm_num=',pset.pm_num
      (0..pset.pm_num-1).each do | probe |
        print ", ",Biolib::Affyio.cel_pm(celobject,cdf,probeset,probe)
      end
    end
  end

  print "\nCleaning up..."
  Biolib::Affyio.close_celfile(celobject)

  exit 0
end
