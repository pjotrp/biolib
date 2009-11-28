BEGIN{unshift(@INC, "../emboss")};
use biolib::emboss;

# my $result = example::my_mod(7,3);
# print "my_mod returns $result!\n";

$ENV{'DATA'} = "../../../../test/data/emboss/";
$trnTable = emboss::ajTrnNewI(1);
$ajpseq   = emboss::ajSeqNewNameC("AGCT","Test sequence");
$ajpseqt  = emboss::ajTrnSeqOrig($trnTable,$ajpseq,1);
$aa       = emboss::ajSeqGetSeqCopyC($ajpseqt);

exit ($result != "SX");
