#######import libsequence module#########
import sys
sys.path += ['../libsequence']
#print sys.path
#import biolib.libsequence as libsequence
from biolib.libsequence import *

########import DocTest and unittest#######
import doctest

#######create test cases#########
#class TestSeq(object):
    
class TestFasta(object):
##    def setUp(self):
####        """
####        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
####        """
##        self.fasta = Fasta('DNA', 'ATGACGTGTA')
##        return fasta
##
##    def tearDown(self):
##        del fasta

    def testFasta(self):
        """Constructor: Create a FASTA sequence

        >>> fasta = Fasta()
        >>> fasta = Fasta('dna', 'ATG')
        """
    def testcopy_Fasta(self):
        """Copy constructor

        >>> fasta = Fasta('dna', 'ATGC')
        >>> fasta1 = Fasta(fasta)
        """

    def testdes_Fasta(self):
        """Destructor

        >>> fasta = Fasta('dna', 'ATGC')
        >>> del fasta
        """

    def testGetName(self):
        """Return the sequence name

        Given a FASTA sequence, its name will be returned

        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.GetName()
        'DNA'
        """
    #        self.fasta.GetName()

    def testGetSeq(self):
        """Return the sequence itself

        Given a FASTA sequence, itself will be returned

        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.GetSeq()
        'ATGACGTGTA'
        """
    #        self.fasta.GetSeq()
    def testsubstr(self):
        """Returns a substring of the current string, starting at index, and length characters long.

        substr(beg, len)
        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.substr(2,3)
        'GAC'

        if the 'len' argument is omitted, the rest of string from the 'beg' will be displayed
        >>> fasta.substr(2)
        'GACGTGTA'
        """
    def testlength(self):
        """Return the total length of the sequence

        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.length()
        10
        """
    def testUngappedLength(self):
        """Return length of sequence, excluding the gap character '-'

        >>> fasta = Fasta('DNA','A-T-TG')
        >>> fasta.UngappedLength()
        4
        """
    def testIsGapped(self):
        """Returns True if the sequence contaings the gap character '-', False otherwise

        >>> fasta = Fasta('DNA','A-T-TG')
        >>> fasta.IsGapped()
        True
        """

    def testc_str(self):
        """Returns the C-style string representing the sequence as a cont char *

        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.c_str()
        'ATGACGTGTA'
        """
    def testto_std_str(self):
        """allows (implict) cast to std::string

        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.to_std_str()
        'ATGACGTGTA'
        """
    def testSubseq(self):
        """range-checking done by assert()

        Subseq(beg, len)
        Parameters:
        beg 	the index along the sequence at which the substring begins
        length 	the length of the subseq Acts via std::string.substr(). Note that this modifies the data in the object by changing thestd::string--if you want to keep the original sequence, you need to make a copy of the object first.

        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.Subseq(2,3)
        >>> fasta.GetSeq()
        'GAC'
        """

    def testComplement(self):
        """Complement the Sequence

        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.Complement()
        >>> fasta.GetSeq()
        'TACTGCACAT'
        """

    def testRevcom(self):
        """Reverse and complement the sequence

        >>> fasta = Fasta('DNA', 'ATGACGTGTA')
        >>> fasta.Revcom()
        >>> fasta.GetSeq()
        'TACACGTCAT'
        """
    def testoperator_equal(self):
        """Returns true if the sequences contain the same data, false otherwise.

        >>> fasta = Fasta('DNA', 'ATGC')
        >>> fasta1 = Fasta('DNA', 'AGTC')
        >>> fasta == fasta1
        False
        """

    def testoperator_notequal(self):
        """Returns false if the sequences contain the same data, true otherwise.

        >>> fasta = Fasta('DNA', 'ATGC')
        >>> fasta1 = Fasta('DNA', 'AGTC')
        >>> fasta != fasta1
        True
        """
    
class TestSimpleSNP(object):

    def testSimpleSNP(self):
        """Constructor:

        This constructor has two bools. One is diploid, the other is isofemale

        SimpleSNP(diploid = False, isofemale = False)
        >>> snp = SimpleSNP()
        """
    def testdes_SimpleSNP(self):
        """Destructor:

        >>> snp = SimpleSNP()
        >>> del snp
        """
        
    def testoutgroup(self):
        """returns true if there is outgroup information, false (defalut) otherwise
    
        >>> snp = SimpleSNP()
        >>> snp.outgroup()
        False
        """
    def testset_outgroup(self):
        """Set the boolean value of outgroup

        >>> snp = SimpleSNP()
        >>> snp.set_outgroup(1)
        >>> snp.outgroup()
        True
        """

def TestKimura80(object):

    def testKimura80(self):
        """Constructor: Kimura's 2-parameter distance

        Kimura80(seq1, seq2): seq1 and seq2 should be of the same length.
        >>> fas1 = Fasta('dna1', 'AGTGCG')
        >>> fas2 = Fasta('dn22', 'TGCACT')
        >>> kim = Kimura80(fas1, fas2)
        """

    def testK(self):
        """Returns: the distance between the two sequences.

        >>> fas1 = Fasta('dna1', 'AGTGCG')
        >>> fas2 = Fasta('dn22', 'TGCACT')
        >>> kim = Kimura80(fas1, fas2)
        >>> kim.K()
        0.0
        """

    def testsites(self):

        """Returns:the number of sites compared, excluding gaps, missing data, etc.

        >>> fas1 = Fasta('dna1', 'AGTGCG')
        >>> fas2 = Fasta('dn22', 'TGCACT')
        >>> kim = Kimura80(fas1, fas2)
        >>> kim.sites()
        6
        """
        
    



        
    
    

    
        

      

if __name__ == "__main__":
##    suite = unittest.TestSuite()
##    suite.addTest(doctest.DocTestSuite())
##    runner = unittest.TextTestRunner()
##    runner.run(suite)
##    unittest.main()


    

    doctest.testmod()
    



    
        


