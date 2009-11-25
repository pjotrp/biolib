
require 'biolib/emboss'

ENV['DATA'] = "../../../../test/data/emboss/"
trnTable = Biolib::Emboss.ajTrnNewI(1);
ajpseq   = Biolib::Emboss.ajSeqNewNameC("AGCT","Test sequence")
ajpseqt  = Biolib::Emboss.ajTrnSeqOrig(trnTable,ajpseq,1)
aa       = Biolib::Emboss.ajSeqGetSeqCopyC(ajpseqt)
raise 'Test failed '+aa if aa != 'SX'

exit 0
