#######import libsequence module#########
import sys
sys.path += ['../libsequence']
#print sys.path
#import biolib.libsequence as libsequence
from biolib.libsequence import *

########import DocTest and unittest#######
import doctest

########create test classes#######
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
    def testoperator_reference(self):
        """Return the i-th element of the sequence.

        >>> fasta = Fasta('dna','atg')
        >>> fasta[1]
        't'
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

class TestKimura80(object):

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
class TestGranthamWeights2(object):

    def testGranthamWeights2(self):
        """Constructor: eights paths by Grantham's distances for codons differing at 2 sites.

        >>> gran2 = GranthamWeights2()
        """

    def testdes_GranthamWeights2(self):
        """Destructor:

        >>> gran2 = GranthamWeights2()
        >>> del gran2
        """
    def testweights(self):
        """Returns:a double * of size 2 (1 value for each branch)

        >>> gran2 = GranthamWeights2()
        >>> weights = gran2.weights()
        >>> w = doubleArray_frompointer(weights)
        >>> # the above statement transform a C array 'weights' to an object 'w'
        >>> # that can be handled just like a C array in python, for example,
        >>> # w[0],w[1]
        """

    def testCalculate(self):
        """Calculate actually calculates the weights for each branch

        Calculate(codon1, codon2)
        codon1 and codon2 are 3-letters condons from different branch

        >>> gran2 = GranthamWeights2()
        >>> gran2.Calculate("CGU", "AGG")
        >>> w = doubleArray_frompointer(gran2.weights())
        >>> w[0]
        0.0
        >>> w[1]
        1.0
        """
class TestGranthamWeights3(object):

    def testGranthamWeights3(self):
        """Constructor: Weights paths by Grantham's distances for codons differing at 3 sites.

        >>> gran3 = GranthamWeights3()
        """
    def testdes_GranthamWeights3(self):
        """Destructor:

        >>> gran3 = GranthamWeights3()
        >>> del gran3
        """
    def testweights(self):
        """Returns:a double * of size 6 (1 value for each branch)

        >>> gran3 = GranthamWeights3()
        >>> w = doubleArray_frompointer(gran3.weights())
        >>> # w can be accesed like w[0], w[1],...,w[5]
        """

    def testCalculate(self):
        """Calculate actually calculates the weights for each branch

        Calculate(codon1, codon2)
        codon1 and codon2 are 3-letters condons from different branch

        >>> gran3 = GranthamWeights3()
        >>> gran3.Calculate("UGG", "CGA")
        >>> w = doubleArray_frompointer(gran3.weights())
        >>> w[1]
        0.5
        """
class TestUnweighted2(object):

    def testUnweighted2(self):
        """Constructor:weights all pathways equally

        >>> unwei2 = Unweighted2()
        """

    def testdes_Unweighted2(self):
        """Destructor:

        >>> unwei2 = Unweighted2()
        >>> del unwei2
        """
    def testweights(self):
        """Returns:a double * of size 2 (1 value for each branch)

        >>> unwei2 = Unweighted2()
        >>> w = doubleArray_frompointer(unwei2.weights())
        """

    def testCalculate(self):
        """Calculate actually calculates the weights for each branch

        Calculate(codon1, codon2)
        codon1 and codon2 are 3-letters condons from different branch

        >>> unwei2 = Unweighted2()
        >>> unwei2.Calculate("CGU", "AGG")
        >>> w = doubleArray_frompointer(unwei2.weights())
        >>> w[0]
        0.5
        >>> w[1]
        0.5
        """

class TestUnweighted3(object):
    
    def testUnweighted3(self):
        """Constructor:weights all pathways equally

        >>> unwei3 = Unweighted3()
        """

    def testdes_Unweighted3(self):
        """Destructor:

        >>> unwei3 = Unweighted3()
        >>> del unwei3
        """
        
    def testweights(self):
        """Returns:a double * of size 6 (1 value for each branch)

        >>> unwei3 = Unweighted3()
        >>> w = doubleArray_frompointer(unwei3.weights())
        """

    def testCalculate(self):
        """Calculate actually calculates the weights for each branch

        Calculate(codon1, codon2)
        codon1 and codon2 are 3-letters condons from different branch

        >>> unwei3 = Unweighted3()
        >>> unwei3.Calculate("UGG", "CGA")
        >>> w = doubleArray_frompointer(unwei3.weights())
        >>> w[1]
        0.16666666666666666
        >>> w[3]
        0.16666666666666666
        >>> w[5]
        0.16666666666666666
        """
class TestRedundancyCom95(object):

    def testRedundancyCom95(self):
        """Constructor:Calculate redundancy of a genetic code using Comeron's counting scheme

        >>> redundancy = RedundancyCom95()
        """
    def testdel_RedundancyCom95(self):
        """Destructor:

        >>> redundancy = RedundancyCom95()
        >>> del redundancy
        """
    def testFirstNon(self):
        """Returns:number of times the first codon position is non-degenerate

        Precondition:codon is of length 3, is all uppercase, and only contains
        the characters {A,G,C,T}
        Exceptions:Sequence::SeqException if precondition is not met
        (The following member functions have the same exception handling)
        
        >>> redundancy = RedundancyCom95()
        >>> redundancy.FirstNon("CGA")
        0.5
        """

    def testFirst2S(self):
        """Returns:number of times the first codon position is synonymous via a transition

        >>> redundancy = RedundancyCom95()
        >>> redundancy.First2S("TTT")
        0.0
        """

    def testFirst2V(self):
        """Returns:number of times the first codon position is synonymous via a transversion
        
        >>> redundancy = RedundancyCom95()
        >>> redundancy.First2V("AGG")
        0.33333333333333331
        """

    def testThirdNon(self):
        """Returns:number of times the third position is non-degenerate

        >>> redundancy = RedundancyCom95()
        >>> redundancy.ThirdNon("AGA")
        0.0
        """

    def testThirdFour(self):
        """Returns:number of times the third position is fourfold-degenerate

        >>> redundancy = RedundancyCom95()
        >>> redundancy.ThirdFour("CGG")
        1.0
        """

    def testThird2S(self):
        """Returns:number of times the third position is synonymous via a transition

        >>> redundancy = RedundancyCom95()
        >>> redundancy.Third2S("AGG")
        1.0
        """
    def testThird2V(self):
        """Returns:number of times the third position is synonymous via a transversion
        >>> redundancy = RedundancyCom95()
        >>> redundancy.Third2V("AGG")
        0.0
        """

    def testL0_vals(self):
        """Returns:the number of non-degenerate positions in codon

        >>> redundancy = RedundancyCom95()
        >>> redundancy.L0_vals("CGG")
        1.6666666666666667
        """

    def testL2S_vals(self):
        """Returns:the number of transitional silent sites in codon

        >>> redundancy = RedundancyCom95()
        >>> redundancy.L2S_vals("AGG")
        1.0
        """

    def testL2V_vals(self):
        """Returns:the number of transversional silent sites in codon

        >>> redundancy = RedundancyCom95()
        >>> redundancy.L2V_vals("AGG")
        0.33333333333333331
        """

    def testL4_vals(self):
        """Returns:the number of fourfold silent sites in codon

        >>> redundancy = RedundancyCom95()
        >>> redundancy.L4_vals("CGG")
        1.0
        """

class TestSites(object):

    def testSites(self):
        """Constructor:Calculate length statistics for divergence calculations.

        Sites(sitesObj, seq1, seq2, max = 3, code = 0)
        Parameters:
        sitesObj 	an initialized object of type RedundancyCom95
        seq1 	a Seq object
        seq2 	a Seq object
        max 	max number of substitutions per codon to analyze
        code 	see Sequence::GeneticCodes for valid values

        Note:
        sequences must be of same length, this is checked by assert()
        sequence lengths must be multiples of 3, this is checked by assert()

        >>> redun = RedundancyCom95()
        >>> seq1 = Fasta("n1", "AGTGCC")
        >>> seq2 = Fasta("n2", "TTGCAG")
        >>> sites = Sites(redun, seq1, seq2)
        """

        
    
    






















########excute the test############
if __name__ == "__main__":
##    suite = unittest.TestSuite()
##    suite.addTest(doctest.DocTestSuite())
##    runner = unittest.TextTestRunner()
##    runner.run(suite)
##    unittest.main()
    doctest.testmod()
