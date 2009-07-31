#######import libsequence module#########
import sys
sys.path += ['../libsequence']
#print sys.path
#import biolib.libsequence as libsequence
from biolib.libsequence import *

########import DocTest and unittest#######
import doctest

########create test cases#######

########1. General I/O#############
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
        
class TestKimura80(object):

    def testKimura80(self):
        """Constructor: Kimura's 2-parameter distance

        Kimura80(seq1, seq2): seq1 and seq2 should be of the same length.
        >>> fas1 = Fasta('dna1', 'AGTGCG')
        >>> fas2 = Fasta('dna2', 'TGCACT')
        >>> kim = Kimura80(fas1, fas2)
        """

    def testK(self):
        """Returns: the distance between the two sequences.

        >>> fas1 = Fasta('dna1', 'AGTGCG')
        >>> fas2 = Fasta('dna2', 'TGCACT')
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
        >>> gran3.Calculate("AAA", "CCC")
        >>> w = doubleArray_frompointer(gran3.weights())
        >>> w[1]
        0.15905190450646806
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

    def testdes_Sites(self):
        """Destructor:

        >>> redun = RedundancyCom95()
        >>> seq1 = Fasta("n1", "AGTGCC")
        >>> seq2 = Fasta("n2", "TTGCAG")
        >>> sites = Sites(redun, seq1, seq2)
        >>> del sites
        """
        
    def testL0(self):
        """Returns:alignment length in terms of non-degenerate sites

        >>> redun = RedundancyCom95()
        >>> seq1 = Fasta("n1", "AGTGCC")
        >>> seq2 = Fasta("n2", "TTGCAG")
        >>> sites = Sites(redun, seq1, seq2)
        >>> sites.L0()
        3.5
        """

    def testL2S(self):
        """Returns:alignment length in terms of transitional-degenerate sites

        >>> redun = RedundancyCom95()
        >>> seq1 = Fasta("n1", "AGTGCC")
        >>> seq2 = Fasta("n2", "TTGCAG")
        >>> sites = Sites(redun, seq1, seq2)
        >>> sites.L2S()
        2.0
        """

    def testL2V(self):
        """Returns:alignment length in terms of transversional-degenerate sites

        >>> redun = RedundancyCom95()
        >>> seq1 = Fasta("n1", "AGTGCC")
        >>> seq2 = Fasta("n2", "TTGCAG")
        >>> sites = Sites(redun, seq1, seq2)
        >>> sites.L2V()
        0.0
        """

    def testL4(self):
        """Returns:alignment length in terms of fourfold-degenerate sites

        >>> redun = RedundancyCom95()
        >>> seq1 = Fasta("n1", "AGTGCC")
        >>> seq2 = Fasta("n2", "TTGCAG")
        >>> sites = Sites(redun, seq1, seq2)
        >>> sites.L4()
        0.5
        """

class TestSingleSub(object):

    def testSingleSub(self):
        """Constructor:Deal with codons differing at 1 position.

        >>> singlesub = SingleSub()
        """

    def testdes_SingleSub(self):
        """Destructor:

        >>> singlesub = SingleSub()
        >>> del singlesub
        """

    def testoperaotr_funcall(self):
        """A functor to obtain divergence statistics for Comeron's method for codons that differ at one position. 

        SingleSubObj(sitesObj, cod1, cod2)
        Parameters:
        sitesObj 	an object of type Sequence::RedundancyCom95
        cod1 	a std::string of length 3 representing a codon
        cod2 	a std::string of length 3 representing a codon
        Note:
        cod1 and cod2 lengths are verified by assert() and consist of A,T,C,G

        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'CGG', 'ATC')
        >>> singlesub(redun, 'CAC', 'AAT')
        """
    def testP0(self):
        """Returns:number of transitions at non-degenerate sites in the codon

        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'CAC', 'AAT')
        >>> singlesub.P0()
        0.0
        """

    def testP2S(self):
        """Returns:number of transitions at transitional-degenerate sites in the codon
    
        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'CAC', 'AAT')
        >>> singlesub.P2S()
        1.0
        """

    def testP2V(self):
        """Returns:number of transitions at transversional-degenerate sites in the codon
    
        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'CAC', 'AAT')
        >>> singlesub.P2V()
        0.0
        """

    def testP4(self):
        """Returns:number of transitions at fourfold-degenerate sites in the codon

        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'CAC', 'AAT')
        >>> singlesub.P4()
        0.0
        """
    def testQ0(self):
        """Returns:number of transversions at non-degenerate sites in the codon
    
        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'TAG', 'AAC')
        >>> singlesub.Q0()
        0.0
        """

    def testQ2S(self):
        """Returns:number of transversions at transitional-degenerate sites in the codon

        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'TAG', 'AAC')
        >>> singlesub.Q2S()
        0.5
        """

    def testQ2V(self):
        """Returns:number of transversions at transversional-degenerate sites in the codon

        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'TAG', 'AAC')
        >>> singlesub.Q2V()
        0.0
        """

    def testQ4(self):
        """Returns:number of transversions at fourfold-degenerate sites in the codon

        >>> singlesub = SingleSub()
        >>> redun = RedundancyCom95()
        >>> singlesub(redun, 'TAG', 'AAC')
        >>> singlesub.Q4()
        0.5
        """

class TestTwoSubs(object):

    def testTwoSubs(self):
        """Constructor:Deal with codons differing at 2 positions

        >>> twosubs = TwoSubs()
        """

    def testdes_TwoSubs(self):
        """Destructor:

        >>> twosubs = TwoSubs()
        >>> del twosubs
        """
    def testoperator_funcall(self):
        """A function object to obtain divergence statistics for Comeron's method for
        codons that differ at two positions. Alternate paths are weighted by Grantham's distances. 

        TwoSubsObj(sitesObj, codon1, condon2, weights2)
        Parameters:
        sitesObj 	an initialized object of type Sequence::RedundancyCom95
        codon1 	string of length 3 representing nucleodites
        codon2 	string of length 3 representing nucleodites
        weights2 	a weighting scheme for the pathways

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'TCT', 'CAG', gran2)
        """
    def testP0(self):
        """Returns:number of transitions at non-degenerate sites in the codon

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'TCT', 'CAG', gran2)
        >>> twosubs.P0()
        0.61963011456326567
        """
    def testP2S(self):
        """Returns:number of transitions at transitional-degenerate sites in the codon

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'TCT', 'CAG', gran2)
        >>> twosubs.P2S()
        0.0
        """
    def testP2V(self):
        """Returns:number of transitions at transversional-degenerate sites in the codon

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'TCT', 'CAG', gran2)
        >>> twosubs.P2V()
        0.0
        """

    def testP4(self):
        """Returns:number of transitions at fourfold-degenerate sites in the codon

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'TCT', 'CAG', gran2)
        >>> twosubs.P4()
        0.0
        """
    def testQ0(self):
        """Returns:number of transversions at non-degenerate sites in the codon

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'CCT', 'AAG', gran2)
        >>> twosubs.Q0()
        0.97042355598595176
        """

    def testQ2S(self):
        """Returns:number of transversions at transitional-degenerate sites in the codon

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'CCT', 'AAG', gran2)
        >>> twosubs.Q2S()
        0.77218233301053618
        """

    def testQ2V(self):
        """Returns:number of transversions at transversional-degenerate sites in the codon

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'CCT', 'AAG', gran2)
        >>> twosubs.Q2V()
        0.0
        """

    def testQ4(self):
        """Returns:number of transversions at fourfold-degenerate sites in the codon

        >>> twosubs = TwoSubs()
        >>> gran2 = GranthamWeights2()
        >>> redun = RedundancyCom95()
        >>> twosubs(redun, 'CCT', 'AAG', gran2)
        >>> twosubs.Q4()
        0.25739411100351206
        """

class TestThreeSubs(object):

    def testThreeSubs(self):
        """Constructor:Deal with codons differing at all 3 positions.

        >>> threesubs = ThreeSubs()
        """

    def testdes_ThreeSubs(self):
        """Destructor:

        >>> threesubs = ThreeSubs()
        >>> del threesubs
        """

    def testoperator_funcall(self):
        """ A function object to obtain divergence statistics for Comeron's method for codons
        that differ at three positions. Alternate paths are weighted by Grantham's distances.

        ThreeSubsObj(sitesObj, codon1, codon2, weights3)
        Parameters:
        sitesObj 	an object of type Sequence::RedundancyCom95
        codon1 	a std::string of length 3
        codon2 	a std::string of length 3
        weights3 	a weighting scheme for the pathways
    
        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        """
    def testP0(self):
        """Returns:number of transitions at non-degenerate sites in the codon
    
        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        >>> threesubs.P0()
        0.15683540643876337
        """

    def testP2S(self):
        """Returns:number of transitions at transitional-degenerate sites in the codon

        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        >>> threesubs.P2S()
        0.19184735131118127
        """

    def testP2V(self):
        """Returns:number of transitions at transversional-degenerate sites in the codon

        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        >>> threesubs.P2V()
        0.15683540643876337
        """

    def testP4(self):
        """Returns:number of transitions at fourfold-degenerate sites in the codon

        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        >>> threesubs.P4()
        0.49448183581129201
        """

    def testQ0(self):
        """Returns:number of transversions at non-degenerate sites in the codon

        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        >>> threesubs.Q0()
        1.4183875193488655
        """

    def testQ2S(self):
        """Returns:number of transversions at transitional-degenerate sites in the codon

        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        >>> threesubs.Q2S()
        0.22654016803768418
        """

    def testQ2V(self):
        """Returns:number of transversions at transversional-degenerate sites in the codon

        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        >>> threesubs.Q2V()
        0.3550723126134504
        """

    def testQ4(self):
        """Returns:number of transversions at fourfold-degenerate sites in the codon

        >>> threesubs = ThreeSubs()
        >>> redun = RedundancyCom95()
        >>> gran3 = GranthamWeights3()
        >>> threesubs(redun, 'ATG', 'CGA', gran3)
        >>> threesubs.Q4()
        0.0
        """
class TestComeron95(object):
    def testComeron95(self):
        """Constructor:an object to implement Comeron's (1995) method to calculate Ka and Ks
        Initialize and calculate synonymous and nonsynonymous distances between two sequence objects

        Comeron95(seqa, seqb, max = 3, code = UNIVERSAL, _weigths2 = NULL, _weights3 = NULL)
        Parameters:
        seqa 	an object of type or derived from type Sequence::Seq
        seqb 	an object of type or derived from type Sequence::Seq
        max 	maximum number of substitutions per codon to allow in the analysis
        code 	genetic code, see Sequence::GeneticCodes
        _weights2 	a weighting scheme for codons differing at 2 positions. If NULL, Sequence::GranthamWeights2 is used
        _weights3 	a weighting scheme for codons differing at 3 positions. If NULL, Sequence::GranthamWeights3 is used

        Warning:
        Note that the pointers to weighting schemes are dumb pointers.
        This allows me to check for NULL and then assign a default.
        If you use your own classes, make sure they clean up after themselves if they throw exceptions!!!

        Exceptions:
        if sequence lengths are not equal or if sequence lengths are not multiples of 3
        exception will be rasied

        >>> seq1 = Fasta('s1', 'AGTGCC')
        >>> seq2 = Fasta('s2', 'CCGTAA')
        >>> comeron = Comeron95(seq1, seq2)
        """
    def testdes_Comeron95(self):
        """Destructor:

        >>> seq1 = Fasta('s1', 'AGTGCC')
        >>> seq2 = Fasta('s2', 'CCGTAA')
        >>> comeron = Comeron95(seq1, seq2)
        >>> del comeron
        """

    def testka(self):
        """Returns:the nonsynonymous distance

        Note:999.0 is returned if Ka cannot be calculated

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.ka()
        0.0
        """

    def testks(self):
        """Returns: the synonymous distance

        Note:999.0 is returned if Ka cannot be calculated

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.ks()
        0.39270813010733246
        """

    def testratio(self):
        """Returns:ka/ks

        Note:999.0 is returned if Ka/Ks cannot be calculated

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.ratio()
        0.0
        """

    def testP0(self):
        """Returns:number of transitions at nondegenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.P0()
        2.0
        """

    def testP2S(self):
        """Returns:number of transitions at 2-fold, transitional degenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.P2S()
        0.0
        """

    def testP2V(self):
        """Returns:number of transitions at 2-fold, transversional degenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.P2V()
        0.0
        """

    def testP4(self):
        """Returns:number of transitions at 4-fold degenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.P4()
        0.0
        """

    def testQ0(self):
        """Returns:number of transversion at nondegenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.Q0()
        3.9044719537318398
        """

    def testQ2S(self):
        """Returns:number of transversion at 2-fold, transitional degenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.Q2S()
        0.75747679019931624
        """

    def testQ2V(self):
        """Returns:number of transversion at 2-fold, transversional sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.Q2V()
        0.17659143153111975
        """

    def testQ4(self):
        """Returns:number of transversion at 4-fold degenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.Q4()
        0.16145982453772428
        """

    def testaa(self):
        """Returns:corrected nonsynonymous divergence at tranversioal- and non- degenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.aa()
        0.0
        """

    def testbs(self):
        """Returns:corrected synonymous divergence at transversional- and fourfold- degenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.bs()
        0.18701760636832385
        """

    def testba(self):
        """Returns:corrected nonsynonymous divergence at transitional- and non- degenerate sites

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.ba()
        0.0
        """

    def testL0(self):
        """Returns:the number of nondegenerate sites compared

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.L0()
        4.8333333333333339
        """

    def testL2S(self):
        """Returns:the number of twofold, transitional-degenerate sites compared

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.L2S()
        0.5
        """

    def testL2V(self):
        """Returns:the number of twofold, transversional-degenerate sites compared

        
        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.L2V()
        0.16666666666666666
        """

    def testL4(self):
        """Returns:the number of 4-fold degenerate sites compared

        >>> seq1 = Fasta('s1', 'GCTACGAGC')
        >>> seq2 = Fasta('s2', 'CTTCGGTAG')
        >>> comeron = Comeron95(seq1, seq2)
        >>> comeron.L4()
        2.0
        """

        
class TestshortestPath(object):

    def testshortestPath(self):
        """Constructor:A class which calculates the shortest path between two codons.

        shortestPath(codon1, codon2, code = UNIVERSAL)
        Parameters:
        codon1 	a std::string of length 3
        codon2 	a std::string of length 3
        code 	which genetic code to use
        
        Precondition:
        (codon1.length() == 3 && codon2.length() ==3)
        Note:
        If either codon1 or codon2 contain characters other than {A,G,C,T}, the pathway type will be assigned shortestPath::AMBIG

        >>> path = shortestPath('ATG', 'ACG')
        """

    def testdes_shortestPath(self):
        """Destructor:

        >>> path = shortestPath('ATG', 'ACG')
        >>> del path
        """
    def testtype(self):
        """Returns:a value from the enum type shortestPath.pathType representing the type of the shortest path.
    
        Note:enum   pathType { 
                              S, N, SS, SN, 
                              NN, SSS, SSN, SNN, 
                              NNN, NONE, AMBIG 
                            }

        >>> path = shortestPath('ATG', 'ACG')
        >>> path.type()
        1
        """

    def testpath_distance(self):
        """Returns:the total Grantham's distance of the shortest path

        >>> path = shortestPath('ATG', 'ACG')
        >>> path.path_distance()
        81.039692790000004
        """

class TeststateCounter(object):

    def teststateCounter(self):
        """Constructor:keep track of state counts at a site in an alignment or along a sequence
        
        >>> states = stateCounter()
        """

    def testoperator_funcall(self):
        """add the character in position i,j in an alignment

        characters are from {A, T, G, C, N, 0, 1, -}

        >>> states = stateCounter()
        >>> states('A')
        >>> states.a
        1
        >>> states('C')
        >>> states.c
        1
        >>> states('a')
        >>> states.a
        2
        """

    def testnStates(self):
        """Returns:the number of states counted, excluding gaps and missing data

        >>> states = stateCounter()
        >>> states('a')
        >>> states('g')
        >>> states('n')
        >>> states('0')
        >>> states('-')
        >>> states.nStates()
        3
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

    

def TestIntermediates2():
    """Calculate the intermediate codons between a pair of codons diverged at 2 positions.

        Parameters:
        intermediates 	a string[2] in which we will place the intermediate codons
        codon1 	a codon
        codon2 	a codon

        >>> c = stringArray(2)
        >>> Intermediates2(c,'ATG', 'CGG')
        >>> c[0]
        'CTG'
        >>> c[1]
        'AGG'
        """

def TestIntermediates3():
    """Calculate the intermediate codons between a pair of codons diverged at 3 positions.

    Parameters:
        intermediates 	a string[9] in which we will place the intermediate codons
        codon1 	a codon
        codon2 	a codon

    >>> c = stringArray(9)
    >>> Intermediates3(c, 'ACG', 'CTT')
    >>> print c[0], c[3], c[5], c[8]
    CCG ATG ATT ATT
    
    """

def TestmutsShortestPath():
    """Returns:a std::pair<unsigned,unsigned> representing the number of silent
    and replacement changes b/w 2 codons, as calculated by shortestPath.
    The first member of the pair is the number of silent changes in the shortest path,
    and the second the number of replacement changes. If the pathway type is shortestPath::AMBIG,
    both members of the return value will be equal to SEQMAXUNSIGNED,
    which is declared in <Sequence/SeqConstants.hpp>

    >>> mutsShortestPath('AAA', 'GGG')
    (1, 2)
    """
            
################ Miscellany ##########################
##def TestTranslate(object):
##    """Returns:a string representing the translation of the range
##
##    Translate(beg, end, genetic_code = UNIVERSAL, gapchar = '-')
##    Parameters:
##    beg 	a pointer to the beginning of the region to translate
##    end 	a pointer to 1 past the end of the region to translate
##    genetic_code 	must be a value from the enumeration list Sequence::GeneticCodes
##    gapchar 	a character representing an alignment gap
##    """

def TestTsTv():
    """akes two chars, assumed to be nucleotides. The integer returned by this function is a
    member of the enumeration type Mutations.
    
    >>> TsTv('A','G')
    1

    Takes two ints, assumed to be integer representations of nucleotides.The way to ensure that
    the int represents a nucleotide in a valid way is to use Nucleotides. The return value is
    determined by a call to TsTv(int i, int j), where the ints are defined in turn by Nucleotides
    >>> TsTv(1,2)
    2
    """

def TestDifferent():
    """Ask if two strings are different. While this can normally be done by asking if (seq1 != seq2) {},
    missing data poses a problem here. If skip-missing == 1, missing data (the 'N' character
    for nucleotide data, 'X' for amino acid) are not used to determine if the sequences are different.
    If nucleic_acid ==1, nucleotide data are assumed, if nucleic_acid==0, protein data are assumed.

    Different(seq1, seq2, skip_missing = 1, nucleic_data = 1)
    Note:
    case-insensitive
    Returns:
    true if the seqs are different, false otherwise. If the two sequences are of different length, true is returned.

    >>> seq1 = 'ATGNT'
    >>> seq2 = 'ATGT'
    >>> Different(seq1, seq2, 1, 1)
    True
    >>> seq1 = 'CCN'
    >>> seq2 = 'CCT'
    >>> Different(seq1, seq2, 1, 1)
    False
    """
def TestGapped():
    """Returns:true if the string contains gaps, false otherwise
       Note:
       The only gap character checked so far is '-'. Use template version for other gap characters

    >>> Gapped('A-G-T')
    True

    Gapped(beg, end, gapchar = '-')
    Parameters:
    beg 	an iterator
    end 	an iterator
    gapchar 	a character representing an aligment gap
    Returns:true if gapchar is present in the range [beg,end), false otherwise
    >>> fasta = Fasta('seq', 'A++GTC+CA')
    >>> beg = fasta.begin()
    >>> end = fasta.end()
    >>> Gapped(beg, end, '+')
    True
    """

def TestNotAGap():
    """Returns:true if a c is not a gap character, false otherwise.
        Note:
        Currently, only '-' is considered to be a gap character

    >>> NotAGap('-')
    False
    """
def TestNumDiffs():
    """Returns:the number of differences between two std::strings.
    Can skip missing data in the same fashion as Comparisons::Different.
    If one sequence is shorter than the other, the number of positions compared is the length of the shorter sequence.

    NumDiffs(seq1, seq2, skip_missing = 1, nucleic_acid = 1)
    Parameters: the same as Different()

    >>> seq1 = 'AATGC-CT'
    >>> seq2 = 'A-T-CCGT'
    >>> NumDiffs(seq1, seq2)
    4
    """
class TestambiguousNucleotide(object):
    """judge if a char is ambigousNuclectide. In other words,
    if char(can be lower letter) is not within{A,T,G,C},Return False if it is, otherwise Ture

    >>> amb = ambiguousNucleotide()
    >>> amb('A')
    False
    """

class TestinvalidPolyChar(object):
    """This functor can be used to determine if a range contains characters that
    the SNP analysis routines in this library cannot handle gracefully
    if char (can be lower letter) is not within{A,T,G,C,N,-,.},Return False if it is, otherwise Ture

    >>> inv = invalidPolyChar()
    >>> inv('N')
    False
    """
    

class Testsegment(object):

    def testsegment(self):
        """Constructor:A portion of a recombining chromosome.

        segment(beg, end, desc)
        This struct contains 3 public members:

        beg: the first site in the segment
        end: the last site in the segment
        desc: the individual in the sample to which the segment leads

        Create a Null segment:
        >>> seg = segment()

        Or a segment with a length of 3:
        >>> seg = segment(1,3,0)
        """

class Testchromosome(object):

    def testchromosome(self):
        """Contrctor: A chromosome is a container of segments.

        chromosome(initial_segs, population = 0)
        Parameters:
        initial_segs 	a vector of segments
        population 	used to set pop

        >>> segs = segVector(3)
        >>> segs[0] = segment()
        >>> segs[1] = segment(1,4,0)
        >>> segs[2] = segment(1,3,1)
        >>> chro = chromosome(segs)


        especially, you can create a null chromosome:
        >>> null_chro = chromosome()
        """

    def testcopy_chromosome(self):
        """Copy constructor:

        >>> segs = segVector(3)
        >>> segs[0] = segment()
        >>> segs[1] = segment(1,4,0)
        >>> segs[2] = segment(1,3,1)
        >>> chro = chromosome(segs)
        >>> chro1 = chromosome(chro)
        """

    
    def testdes_chromosome(self):
        """Destructor:

        >>> segs = segVector(3)
        >>> segs[0] = segment()
        >>> segs[1] = segment(1,4,0)
        >>> segs[2] = segment(1,3,1)
        >>> chro = chromosome(segs)
        >>> del chro
        """

    def testfirst(self):
        """Returns:the first position in the chromosome

        >>> segs = segVector(3)
        >>> segs[0] = segment()
        >>> segs[1] = segment(1,4,0)
        >>> segs[2] = segment(1,3,1)
        >>> chro = chromosome(segs)
        >>> chro.first()
        0
        """

    def testlast(self):
        """Returns:the last position in the chromosome

        >>> segs = segVector(3)
        >>> segs[0] = segment()
        >>> segs[1] = segment(1,4,0)
        >>> segs[2] = segment(1,3,1)
        >>> chro = chromosome(segs)
        >>> chro.last()
        3
        """

    def testassign_allocated_segs(self):
        """Replaces the current segs with those pointed to by newsegs

        assign_allocated_segs(newsegs, new_nsegs)
        Parameters:
        newsegs 	an array of segments allocated with malloc
        new_nsegs 	the number of segs stored in newsegs

        >>> segs = segVector(2)
        >>> segs[0] = segment(2,5,0)
        >>> segs[1] = segment(1,3,1)
        >>> chro = chromosome(segs)
        >>> newsegs = segArray(2)
        >>> newsegs[0] = segment(1,10,0)
        >>> newsegs[1] = segment(3,4,0)

        >>> chro.first()
        2
        >>> chro.assign_allocated_segs(newsegs, 2)
        >>> chro.first()
        1
        """

    def testlinks(self):
        """Computes and returns the number of positions at which recombination can occur in the chromosome

        Returns:
        (segs+nsegs-1)->end - segs->beg

        >>> segs = segVector(2)
        >>> segs[0] = segment(2,5,1)
        >>> segs[1] = segment(10,20,0)
        >>> chro = chromosome(segs)
        >>> chro.links()
        18
        """

    def testswap_with(self):
        """Swaps the data members of the current chromosome with chromosome ch.
        Called by the coalesce routine, and is necessary to prevent nastiness such as
        multiple calls to free when vectors of chromosomes go out of scope.
        Implemented as: std::swap(this->segs,ch.segs); std::swap(this->nsegs,ch.nsegs);
        std::swap(this->pop,ch.pop);

        >>> segs = segVector(2)
        >>> segs[0] = segment(2,5,1)
        >>> segs[1] = segment(10,20,0)
        >>> chro = chromosome(segs)
        >>> chro1 = chromosome()
        >>> chro1.swap_with(chro)
        >>> chro1.first()
        2
        """
                

class TestHKAdata(object):

    def testHKAdata(self):
        """Constructor:Data from a single locus for an HKA test.

        HKAdata(sa, sb, d, na, nb)
        Parameters:
        sa 	Num. polymorphic sites in species a
        sb 	Num. polymorphic sites in species b
        d 	Divergence between species a and b (per locus)
        na 	sample size for species a
        nb 	sample size for species b
        >>> hka = HKAdata(3,5,2,1,1)

        Particularly, you can create a null object:
        >>> hka = HKAdata()
        """

    def testcopy_HKAdata(self):
        """Copy constructor:

        >>> hka = HKAdata()
        >>> hka = HKAdata(3,5,2,1,1)
        >>> hka1 = HKAdata(hka)
        """

#class TestHKAresults(object):

    
class TestNode(object):

    def testnode(self):
        """Constructor:A point on a marginal tree at which a coalescent event occurs.
        A node is a branch-point on a coalescent tree.

        node(t = 0, a = -1)
        Parameters:
        t 	The (coalescent-scaled) time at which the node was generated
        a 	The index in the marginal tree that is the ancestor of the current node
      
        >>> N = node()
        """

class Testmarginal(object):

    def testmarginal(self):
        """Constructor:The genealogy of a portion of a chromosome on which no recombination has occurred.
        A marginal history is a coalscent tree for a region in which no recombination has occured in the history of a sample.
        
        marginal(beg, nsam, nnodes, tree)
        beg:The (mutational) site at which the current marginal tree begins
        nsam: The sample size being simulated. The 2*nsam-1 nodes in the tree are therefore indexed from 0 to 2*nsam-2
        nnodes: The current number of nodes in the tree
        tree: the coalescent history of this marginal tree

        >>> t = nodeVector(3)
        >>> t[0] = node()
        >>> t[1] = node(1,3)
        >>> t[2] = node(3,10)
        >>> marg = marginal(5, 10, 19, t)
        """

    def testoperator_reference(self):
        """Returns: node in tree with index i

        >>> t = nodeVector(2)
        >>> t[0] = node()
        >>> t[1] = node(5,0)
        >>> marg = marginal(3, 10, 19, t)
        >>> marg[0].time
        0.0
        """

    def testoperator_smaller(self):
        """Returns marginalObj1.beg < marginalObj.beg

        >>> t = nodeVector(2)
        >>> t[0] = node()
        >>> t[1] = node(5,0)
        >>> marg = marginal(3, 10, 19, t)
        >>> t1 = nodeVector(1)
        >>> t1[0] = node()
        >>> marg1 = marginal(1, 5, 10, t1)
        >>> marg < marg1
        False
        >>>
        """

##class Testnewick_stream_marginal_tree(object):
##
##    def 

class TestSimParams(object):

    def testSimParams(self):

        """Constructor:Parameters for Hudson's simulation program.

        >>> simpara = SimParams()
        """

    def testparams(self):

        """Returns:the command-line input to ms

        >>> simpara = SimParams()
        >>> simpara.params()
        ''
        """

    def testtotsam(self):

        """Returns:the total sample size (# gametes)

        >>> simpara = SimParams()
        >>> simpara.totsam()
        0
        """

    def testruns(self):
        """Returns:number of genealogies to generate

        >>> simpara = SimParams()
        >>> simpara.runs()
        0
        """

def Testisseg():

    """ask if a chromosome beginning at seg and containing nsegs contains a segment containing the position pos

    isseg(beg, nsegs, offset, pos)
    Parameters:
    seg 	a pointer to a segment of a chromosome (this should be the 1st segment, such as the return value
    of chromosome::begin())

    nsegs 	the number of segs in the chromosome pointed to by seg

    offset 	a pointer to an integer. This integer is used for repeated pointer arithmetic, and should be
    initalized to 0 before the first call.

    pos 	a position a long a chromosome. This function asks if pos is contained in the ancestral material of the chromosome whose segments begin at seg

    Returns:
    true if a segment exists that contains the point pos

    >>> segs = segVector(3)
    >>> segs[0] = segment(1,4,0)
    >>> segs[1] = segment()
    >>> segs[2] = segment(2,8,1)
    >>> chro = chromosome(segs)
    >>> seg = chro.begin()
    >>> offset = intPointer()
    >>> offset.assign(0)
    >>> isseg(seg, 3, 1, offset)
    True
    """

def Testcalculate_scales():

    """This is a helper function that rescales physical distance in base pairs
    to continuous distance on the interval 0,1.

    calculate_scales(fragments, sample_scale, mutation_scale)
    Parameters:
    fragments 	A vector of pairs, representing physical distance in bp.
    For each pair, the first element is the distance to the next fragment,
    and the second element is the length of the fragment. For example,
    two 1kb fragments separated by 10kb would be represented by the pairs (0,1000) (10000,1000).

    sample_scale 	This vector will be filled with values representing
    the positions of the fragments on the continuous interval, without any space
    betwen them. This is because we will actually do the simulation using a non-uniform
    genetic map to represent the high recombination rates between fragments

    mutation_scale 	This is a direct mapping of the data contained in fragments
    to the continuous scale, and can be used to rescale the positions of mutations

    >>> fragments = fragVector(3)
    >>> fragments.push_back(intPair(0,500))
    >>> fragments.push_back(intPair(1000,500))
    >>> fragments.push_back(intPair(1000,500))
    >>> sample = scaleVector(3)
    >>> mutation = scaleVector(3)
    >>> calculate_scales(fragments, sample, mutation)
    """

def Testsample_length():

    """When simulating partially linked regions, return the total length of sample material
    that we are simulating
    Returns: The sum of fragments[i].second for i=0 to i=fragments.size()-1

    sample_length(fragments)
    >>> fragments = fragVector(3)
    >>> fragments.push_back(intPair(0,500))
    >>> fragments.push_back(intPair(1000,500))
    >>> fragments.push_back(intPair(1000,500))
    >>> sample_length(fragments)
    1500
    """

def Testtotal_length():

    """When simulating partially linked regions, return the total length of the region.

    Returns:The sum of fragments[i].first + fragments[i].second for i=0 to i=fragments.size()-1

    total_length(fragments)
    >>> fragments = fragVector(3)
    >>> fragments.push_back(intPair(0,500))
    >>> fragments.push_back(intPair(1000,500))
    >>> fragments.push_back(intPair(1000,500))
    >>> total_length(fragments)
    3500
    """

def Testinit_sample():

    """A simple function to initialize a sample of chromosomes.
    Returns: a vector of chromosome

    init_sample(pop_config, nsites)
    Parameters:
    pop_config 	For a k-population model, this vector contains the sample size for each pop.
    Individuals are labeled as beloning to population 0 to k-1, in the order specified in this vector

    nsites 	The number of sites at which mutations occur. For a k-site model,
    recombination occurs at any of the k-1 "links" between sites. Eaach chromosome is assigned
    a single segment starting at position 0 and ending at nsites-1.

    >>> chroVectorObj = init_sample(intVector(1,10), 1500)
    """
def Testinit_marginal():

    """Simple function to initialize and return a marginal tree.

    Parameters:
    nsam 	the total sample size (i.e. summed over all populations) that you want to simulate

    >>> marginalObj = init_marginal(10)
    """

def Testcoalesce():

    """Common ancestor routine for coalescent simulation. Merges chromosome segments and updates
       marginal trees.

    Common ancestor routine for coalescent simulation. This routine performs the merging of two
    lineages by a coalescent event. Such merges usually require two sorts of operations. The first
    is an update to the segments contained in a chromosome, and the second is an update of the nodes
    on a marginal tree.

    coalesce(time, ttl_nsam, current_nsam, c1, c2, nsites, nlinks, sample, sample_history)
    Parameters:
    time 	the time at which the coalecent event is occuring
    ttl_nsam 	the total sample size being simulated
    current_nsam 	the current sample size in the simulation
    c1 	the array index of the first chromosome involved in the coalescent event
    c2 	the array index of the second chromosome involved in the coalescent event
    nsites 	the total mutational length of the region begin simulated. In the language of Hudson (1983), this is the number of infinitely-many-alleles loci in the simulation.
    nlinks 	a pointer to the number of "links" currently in the simulation. A link is the region between two sites, such that a chromosome currently with k sites has k-1 links
    sample 	a pointer to the vector of chromosomes which makes up the sample
    sample_history 	a pointer to the ancestral recombination graph

    >>> sample = init_sample(intVector(1,10), 1500)
    >>> slength = 1500
    >>> nsam = 19
    >>> t = 0
    >>> marginal = init_marginal(10)
    >>> sample_history = margList(1, marginal)
    >>> nlinks = intPointer()
    >>> nlinks.assign(499)
    >>> coalesce(t,nsam,nsam,1,2,slength,nlinks,sample,sample_history)
    1

    """
    

def Testtotal_time_on_arg():

    """Returns the total time on an ancestral recombination graph.

    total_time_on_arg(sample_history, total_number_of_sites)
    Parameters:
    sample_history 	an ancestral recombination graph
    total_number_of_sites 	the number of "sites" simulated on the ARG

    >>> marginal = init_marginal(10)
    >>> sample_history = margList(1, marginal)
    >>> total_time_on_arg(sample_history, 500)
    0.0
    """

def Testcrossover():

    """Recombination function.Returns:the number of links lost due to the crossover event
    
    crossover(current_nsam, chromo, pos, sample, sample_history)
    Parameters:
    current_nsam 	the current sample size in the simulation
    chromo 	the chromosome on which the crossover event is to occur
    pos 	the crossover event happens between sites pos and pos+1 (0<= pos < nsites)
    sample 	the sample of chromosomes being simulated
    sample_history 	the genealogy of the sample

    >>> sample = init_sample(intVector(1,10), 1500)
    >>> marg = init_marginal(10)
    >>> sample_history = margList(1, marg)
    >>> crossover(10, 5, 100, sample, sample_history)
    1
    """


class TestSimData(object):

    def testSimData():

        """The constructor needs to know the sample size simulated. This is easily obtainted
        using Sequence::SimParams.

        SimData(nsame = 0, nsnps = 0)
        Parameters:
        nsams    sample size
        
        >>> sdata = SimData()
       
        SimData(pos, dat)
        Parameters:
        pos     vector of doubles representing segregating positions
        dat     vector of strings representing sequence data.
        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'N0G1'
        >>> d = SimData(pos,dat)


        SimData(sbegin,send)
        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'N0G1'
        >>> d = SimData(pos,dat)
        >>> beg = d.sbegin()
        >>> end = d.send()
        >>> d1 = SimData(beg,end)
        """

        

    def testdes_SimData():
        """Destructor:

        >>> d = SimData()
        >>> del d
        """

    def testempty():
        """Returns:true if object contains no data, false otherwise

        >>> d = SimData()
        >>> d.empty()
        True
        """
        
    def testGetData():
        """Returns PolyTable::data, a vector of std::strings containing polymorphic sites.
        Assuming the vector is returned to a vector<string> called data, accessing data[i][j] accesses
        the j-th site of the i-th sequence

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'N0G1'
        >>> d = SimData(pos,dat)
        >>> d.GetData()
        ('A-TC', 'N0G1')
        """

    def testGetPositions():
        """Returns PolyTable::positions

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'N0G1'
        >>> d = SimData(pos,dat)
        >>> d.GetPositions()
        (0.25, 0.32000000000000001, 0.34000000000000002, 0.44)
        """

    def testassign():
        """Returns:true if the assignment was successful, false otherwise.
        The only case where false is returned is if the number of individuals at
        each site is not the constan from beg to end.

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'N0G1'
        >>> d = SimData(pos,dat)
        >>> beg = d.sbegin()
        >>> end = d.send()
        >>> d1 = SimData()
        >>> d1.assign(beg,end)
        True
        >>> d1.GetData()
        ('A-TC', 'N0G1')
        """
        
    def testRemoveMissing():
        """go through the data and remove all the sites with missing data (the character N).

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'N0G1'
        >>> d = SimData(pos,dat)
        >>> d.RemoveMissing()
        >>> d.GetData()
        ('-TC', '0G1')
        """

    def testRemoveAmbiguous():
        """go through the data and remove all the sites with states other than {A,G,C,T,N,0,1,-}

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'NEG1'
        >>> d = SimData(pos,dat)
        >>> d.RemoveAmbiguous()
        >>> d.GetData()
        ('ATC', 'NG1')
        """


    def testRemoveMultiHits():
        """go through the data and remove all the sites with more than 2 states segregating.
            By default, this routine also removes sites where there are 2 states segregating in the ingroup.
            and the outgroup (if present) has a 3rd state.
        
        RemoveMultiHits(skipOutgroup = False, outgroup = 0)
        Parameters:
        skipOutgroup 	default is false. If true, the character state of the outgroup is ignored.
        outgroup 	the index of the outgroup in the data vector

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(3)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'N0G1'
        >>> dat[2] = 'T-CC'
        >>> d = SimData(pos,dat)
        >>> d.RemoveMultiHits()
        >>> d.GetData()
        ('A-C', 'N01', 'T-C')
        """




            
    def testApplyFreqFilter():
        """go through the data and remove all positions where there is a variant at count
        (# of occurences in the sample) < minfreq

        ApplyFreqFilter(mincount, haveOutgroup = False, outgroup = 0)
        Parameters:
        mincount 	minimum count of a variant in the data. Variants that occur < mincount times are thrown out.
        haveOutgroup 	true if an outgroup is present in the data, false otherwise
        outgroup 	the index in the data array containing the outgroup (if present)

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(3)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'N0G1'
        >>> dat[2] = 'T-CC'
        >>> d = SimData(pos,dat)
        >>> d.ApplyFreqFilter(2)
        >>> d.GetData()
        ('', '', '')
        """
        
    def testBinary():

        """Recode the polymorphism table in 0,1 (binary notation)

        Binary(haveOutgroup = false, outgroup = 0, strictInfSites = true)
        Parameters:
        haveOutgroup 	use true if an outgroup is present, false otherwise
        outgroup 	the index of the outgroup in the data vector used to construct the object
        strictInfSites 	if true, throw out all sites with > 2 character states (including outgroup!)

        Note:
        if haveOutgroup== true, then 0 means an ancestral state and 1 a derived state in the resulting. 
        note If haveOutgroup == true, and there are sites with missing data in the outrgroup sequence,
        those sites are removed from the data, since its assumed you actually want to know ancestral/derived
        for every site

        >>> d = SimData()
        >>> d.Binary()
        """

    def testsegsites():

        """Returns the number of segregating sites in the data block

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'NEG1'
        >>> d = SimData(pos,dat)
        >>> d.segsites()
        4
        """
    def testsize():
        """Return how many std::strings are stored in PolyTable::data.

        >>> pos = doubleVector(2)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> dat = strVector(3)
        >>> dat[1] = 'A-'
        >>> dat[0] = 'N1'
        >>> dat[2] = 'CG'
        >>> d = SimData(pos,dat)
        >>> d.size()
        3
        """

    def testnumsites():
        """Returns number of sites

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'NEG1'
        >>> d = SimData(pos,dat)
        >>> d.numsites()
        4
        """

    def testposition():
        """Return the i-th position from the PolyTable::positions.

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'NGG1'
        >>> d = SimData(pos,dat)
        >>> d.position(2)
        0.34000000000000002
        """

    def testoperator_equal():
        """Returns true if two SimData object are the same, otherwise false

        >>> pos = doubleVector(4)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> pos[2] = .34
        >>> pos[3] = .44
        >>> dat = strVector(2)
        >>> dat[0] = 'A-TC'
        >>> dat[1] = 'NEG1'
        >>> d = SimData(pos,dat)
        >>> d1 = SimData(pos,dat)
        >>> d == d1
        True
        """


    

    def testoperator_notequal():
        """Returns False if two SimData object are the same, otherwise True

        >>> d = SimData()
        >>> d1 = SimData()
        >>> d != d1
        False
        """

    def testoperator_reference():
        """Return the i-th element of PolyTable::data.

        >>> pos = doubleVector(2)
        >>> pos[0] = .25
        >>> pos[1] = .32
        >>> dat = strVector(2)
        >>> dat[0] = 'AG'
        >>> dat[1] = 'TC'
        >>> d = SimData(pos,dat)
        >>> d[0]
        'AG'
        >>> d[1]
        'TC'
        """
    


class TestPolySites():

    def testPolySites():
        """This is the constructor if you are using "string-like" data, such as std::string,
        or Sequence::Fasta. Note that the vector name is aligment, and that means that every sequence
        had better be the same length!
        By default, there is no limit to how many characters can "segregate" at a variable position,
        although if there are more than 4, most biologists will start to worry. There are, however,
        times when you may wish to onlu consider sites that have a total of 2 character states.
        (NOTE: by two states, I mean including BOTH the ingroup and the outgroup sequence.) Setting
        strictInfSites to 1 will result in making a polymorphic sites object containing only sites with 2 states.

        PolySites(alignment, strictInfsites = 0, ignoregaps = 1, skipMissing = False, skipAdjSNP = False,
                   freqfilter = 0)
        Parameters:
        alignment 	vector of data
        strictInfSites 	if true, throw out all sites with > 2 states
        ignoregaps 	if true, do not count gapped sites as polymorphisms
        skipMissing 	if true, ignore ALL sites with missing data ('N')
        skipAdjSNP 	if does nothing. a placeholder for a future feature
        freqfilter 	Defaults to 0. For a polymorphic site to be included in the final table,
        the minor allele count in the data (i.e. the number of times the minor allele occurs at that site)
        must be strictly greater than freqfilter

        Note:
        segsite positions are stored as positions (starting from 1)

        Warning:
        when ignoregaps=false, this class does not do the right thing

        >>> v = fastaVector(2)
        >>> v[0] = Fasta('s1','ATGCG')
        >>> v[1] = Fasta('s2','CG-TT')
        >>> p = PolySites(v)


        

        Use following constructor if you already have a list of positions and characters

        Parameters:
        List 	a list of doubles representing positions of polymorphic positions
        stringList 	a vector of strings representing the polymorphic characters

        >>> l = doubleVector(2)
        >>> l[0] = 0
        >>> l[1] = 4
        >>> strl = strVector(2)
        >>> strl[0] = 'ATG-'
        >>> strl[1] = 'CCCT'
        >>> p = PolySites(l, strl)
        """

    def testGetData():
        """Returns PolyTable::data, a vector of std::strings containing polymorphic sites.
        Assuming the vector is returned to a vector<string> called data, accessing data[i][j] accesses
        the j-th site of the i-th sequence

        >>> v = fastaVector(2)
        >>> v[0] = Fasta('s1', 'ANTGC-C')
        >>> v[1] = Fasta('s2', '-GGTCCA')
        >>> p = PolySites(v)
        >>> p.GetData()
        ('TGC', 'GTA')
        """

    def testGetPositions():
        """Returns PolyTable::positions.

        >>> v = fastaVector(2)
        >>> v[0] = Fasta('s1', 'ANTGC-C')
        >>> v[1] = Fasta('s2', '-GGTCCA')
        >>> p = PolySites(v)
        >>> p.GetPositions()
        (3.0, 4.0, 7.0)
        """

    def testApplyFreqFilter():
        """go through the data and remove all positions where there is a variant at count
        (# of occurences in the sample) < minfreq

        ApplyFreqFilter(mincount, haveOutgroup = False, outgrp = 0)
        Parameters:
        mincount 	minimum count of a variant in the data. Variants that occur < mincount times are thrown out.
        haveOutgroup 	true if an outgroup is present in the data, false otherwise
        outgroup 	the index in the data array containing the outgroup (if present)
            
        >>> v = fastaVector(2)
        >>> v[0] = Fasta('s1', 'ANTGC-C')
        >>> v[1] = Fasta('s2', '-GGTCCA')
        >>> p = PolySites(v)
        >>> p.GetData()
        ('TGC', 'GTA')
        >>> p.ApplyFreqFilter(2)
        >>> p.GetData()
        ('', '')
        """

    def testempty():
        """Returns:true if object contains no data, false otherwise

        >>> poly = PolySites()
        >>> poly.empty()
        True
        """

    def testBinary():
        """Recode the polymorphism table in 0,1 (binary notation)

        Binary(haveOutgroup = false, outgroup = 0, strictInfSites = true)
        Parameters:
        haveOutgroup 	use true if an outgroup is present, false otherwise
        outgroup 	the index of the outgroup in the data vector used to construct the object
        strictInfSites 	if true, throw out all sites with > 2 character states (including outgroup!)

        Note:
        if haveOutgroup== true, then 0 means an ancestral state and 1 a derived state in the resulting.
        /note If haveOutgroup == true, and there are sites with missing data in the outrgroup sequence,
        those sites are removed from the data, since its assumed you actually want to know ancestral/derived
        for every site

        >>> v = fastaVector(2)
        >>> v[0] = Fasta('s1', 'ANTGC-C')
        >>> v[1] = Fasta('s2', '-GGTCCA')
        >>> p = PolySites(v)
        >>> p.Binary()
        >>> p.GetData()
        ('000', '111')
        """

##    def testsize():
##        """Return how many std::strings are stored in PolyTable::data.
##
##        >>> pol = PolySites()
##        >>> pol.size()
##        0
##        """

    def testnumsites():
        """Return how many positions are stored in PolyTable::positions

        >>> v = fastaVector(2)
        >>> v[0] = Fasta('s1','ANTGC-C')
        >>> v[1] = Fasta('s2','-GGTCCA')
        >>> data = PolySites(v)
        >>> data.numsites()
        3
        """

##class TestFST(object):
##
##    def testFST():
##        

class TestPolySNP(object):

    def testPolySNP():
        """Molecular population genetic analysis

        PolySNP()
        Parameters:
        data 	a valid object of type Sequence::PolyTable
        haveOutgroup 	true if an outgroup is present, false otherwise
        outgroup 	if haveOutgroup is true, outgroup is the index of that sequence in data
        totMuts 	if true (the default) use the total number of inferred mutations,
        otherwise use the total number of polymorphic sites in calculations

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GG1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        """

    def testThetaPi():
        """Calculated here as the sum of 1.0 - sum of site homozygosity accross sites.

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.ThetaPi()
        4.666666666666667
        """

    def testThetaW():
        """The classic "Watterson's Theta" statistic, generalized to missing data and
        multiple mutations per site:

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.ThetaW()
        6.0
        """

    def testThetaH():
        """Calculate Theta ( = 4Nu) from site homozygosity, a la Fay and Wu (2000).
        This statistic is problematic in general to calculate when there are multiple hits.
        The test requires that the ancestral state (inferred from the outgroup) still be
        segregating in the ingroup. If that is not true, the site is skipped.

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.ThetaH()
        0.0
        """

    def testThetaL():
        """Calculate Theta ( = 4Nu) from site homozygosity, corresponding to equation 1 in
        Thornton and Andolfatto (Genetics) "Approximate Bayesian Inference reveals evidence
        for a recent, severe, bottleneck in a Netherlands population of Drosophila melanogaster,
        " (although we labelled in  in that paper) The test requires that the ancestral state
        (inferred from the outgroup) still be segregating in the ingroup. If that is not true,
        the site is skipped.

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.ThetaL()
        0.0
        """        

    def testVarPi():
        """Total variance of mean pairwise differences. Tajima in Takahata/Clark book, (13).

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.VarPi()
        9.7777777777777803
        """

    def testStochasticVarPi():
        """Stochastic variance of mean pairwise differences. Tajima in Takahata/Clark book, (14).

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.StochasticVarPi()
        4.2222222222222232
        """

    def testSamplingVarPi():
        """Component of variance of mean pairwise differences from sampling. Tajima in Takahata/Clark book, (15)

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.SamplingVarPi()
        5.5555555555555562
        """
        
    def testVarThetaW():
        """Returns:Variance of Watterson's Theta (ThetaW()).

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.VarThetaW()
        15.428571428571429
        """

    def testNumPoly():
        """Returns: the number of polymorphic (segregating) sites in data

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.NumPoly()
        5
        """

    def testNumMutations():
        """Returns:the total number of mutations in the data. The number of mutations
        per site = number of states per site - 1

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.NumMutations()
        9
        """

    def testNumSingletons():
        """Returns:number of polymorphisms that appear once in the data, without respect to ancestral/derived

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.NumSingletons()
        13
        """

    def testNumExternalMutations():
        """Returns:the number of derived singletons.

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p)
        >>> snp.NumExternalMutations()
        4294967295L
        """

    def testTajimasD():
        """A common summary of the site frequency spectrum. Proportional to . This routine does calculate the denominator of the test statistic.

        Warning:
        statistic undefined if there are untyped SNPs
        Returns:
        Tajima's D, or nan if there are no polymorphic sites

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.TajimasD()
        nan
        """

    def testHprime():
        """Returns:ThetaPi-ThetaH/(~Var(ThetaPi-ThetaH)). This corresponds to Equation 5 in Thornton and
        Andolfatto (Genetics) "Approximate Bayesian Inference reveals evidence for a recent, severe,
        bottleneck in a Netherlands population of Drosophila melanogaster"

        Parameters:
        likeThorntonAndolfatto 	The calculation of H' requires calculation of . In Thornton and Andolfatto, we simply used , which is slightly biased. By default, this function calculates , unless this bool is set to false, in which case is used.
        Note:
        returns nan if there are 0 polymorphic sites

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.Hprime()
        inf
        """

    def testDnominator():
        """Returns:Denominator of Tajima's D, or nan if there are no polymorphic sites

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.Dnominator()
        0.0
        """
    def testDandVH():
        
        """To check if two sequences are unique, Sequence::Comparisons::Different is used,
        which does not allow missing data to result in 2 sequences being considered different
        (as they would be if you simply used thestd::string comparison operators == or !=)

        Returns:the haplotype diversity of the data.
        
        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.DandVH()
        1.0
        """

    def testDandVK():
        """To check if two sequences are unique, Sequence::Comparisons::Different is used,
        which does not allow missing data to result in 2 sequences being considered different
        (as they would be if you simply used the std::string comparison operators == or !=)

        Returns:
        number of haplotypes in the sample

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.DandVK()
        2
        """
        

    def testWallsB():
        """Returns:Wall's B Statistic.

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.WallsB()
        1.0
        """
    def testWallsBprime():
        """Returns:Wall's B Statistic.

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.WallsBprime()
        3
        """

    def testWallsQ():
        """Returns:Wall's Q Statistic.

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.WallsQ()
        1.0
        """
    def testHudsonsC():
        """Returns:Hudson's (1987) estimator of , an estimator of the population recombination rate that
        depends on the variance of the site frequencies. The calculation is made by a call to
        Recombination::HudsonsC

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.HudsonsC()
        10000.0
        """

    def testMinrec():
        """Returns:The minimum number of recombination events observed in the sample (Hudson and Kaplan 1985).
        Will return SEQMAXUNSIGNED if there are < 2 segregating sites.

        >>> v = fastaVector(3)
        >>> v[0] = Fasta('s1', 'ATGCNC')
        >>> v[1] = Fasta('s2', 'GCCA-T')
        >>> v[2] = Fasta('s3', '0GA1TC')
        >>> p = PolySites(v)
        >>> snp = PolySNP(p,True,1,True)
        >>> snp.Minrec()
        0
        """
        
        
class TestClustalW_str(object):

    def testClustalW_str():
        """This class defines an input routine for alignments in ClustalW format.
        This class template is instantiated with the following types:
        std::pair<std::string, std::string>

        ClustalW_str( strPairObj ): strPairObj is an object instantiated from
        std::vector< std::pair<std::string, std::string> >
        >>> p = pVector(2)
        >>> p[0] = strPair('s1','AT')
        >>> p[1] = strPair('s2','GG')
        >>> clus = ClustalW_str(p)

        Default constructor:
        >>> clus = ClustalW_str()
        """

    def testsize():
        """Returns data.size(),i.e. the length of vector

        >>> p = pVector(2)
        >>> p[0] = strPair('s1','AT')
        >>> p[1] = strPair('s2','GG')
        >>> clus = ClustalW_str(p)
        >>> clus.size()
        2
        """
        

    def testcopy_ClustalW_str():
        """Copy constructor

        >>> p = pVector(2)
        >>> p[0] = strPair('s1','AT')
        >>> p[1] = strPair('s2','GG')
        >>> clus = ClustalW_str(p)
        >>> clus1 = ClustalW_str(clus)
        """

    def testdes_ClustalW_str():
        """Destructor

        >>> clus = ClustalW_str()
        >>> del clus
        """

    def testIsAlignment():
        """A vector of sequences/strings is only an alignment if all strings are the same length.

        >>> p = pVector(2)
        >>> p[0] = strPair('s1','ATGGC')
        >>> p[1] = strPair('s2','CCCAG')
        >>> clus = ClustalW_str(p)
        >>> clus.IsAlignment()
        True
        """

    def testGapped():
        """true if the vector contains a gap character ('-') , false otherwise.

        >>> p = pVector(2)
        >>> p[0] = strPair('s1','ATGGC')
        >>> p[1] = strPair('s2', 'CC-TT')
        >>> clus = ClustalW_str(p)
        >>> clus.Gapped()
        True
        """

    def testRemoveGaps():
        """Modifies the data vector to remove all positions that contain the gap character'-'.

        
        >>> p = pVector(2)
        >>> p[0] = strPair('s1', 'AAT')
        >>> p[1] = strPair('s2', 'C-G')
        >>> clus = ClustalW_str(p)
        >>> clus.Gapped()
        True
        >>> clus.RemoveGaps()
        >>> clus.Gapped()
        False
        """

    def testopertor_reference():
        """Returns the i-th object in the vector data

        >>> p = pVector(2)
        >>> p[0] = strPair('s1', 'AAT')
        >>> p[1] = strPair('s2', 'C-G')
        >>> clus = ClustalW_str(p)
        >>> clus[0]
        ('s1', 'AAT')
        """

    def testRemoveTerminalGaps():
        """Remove all gapped sites from the ends of the alignment, up until the
        first site on either side that is ungapped.

        >>> p = pVector(2)
        >>> p[0] = strPair('s1','-GTCA-T')
        >>> p[1] = strPair('s2','TTAC-C-')
        >>> clus = ClustalW_str(p)
        >>> clus.RemoveTerminalGaps()
        >>> clus[0]
        ('s1', 'GTC')
        >>> clus[1]
        ('s2', 'TAC')
        """

    def testData():
        """Returns the std::vector < std::pair<std::string, std::string > data

        >>> p = pVector(2)
        >>> p[0] = strPair('s1','GTC')
        >>> p[1] = strPair('s2','TAC')
        >>> clus = ClustalW_str(p)
        >>> clus.Data()
        (('s1', 'GTC'), ('s2', 'TAC'))
        """

    def testTrim():
        """Returns a copy of the data vector, modified in the following way.
        The sites vector contains an even number of sites (whose values are sorted).
        If sites does not contain an even number of values Sequence::SeqException is thrown.
        If sites is empty, Sequence::SeqException is thrown. The values in sites represent a
        series of intervals that you wish to keep, and the return vector is consists only of
        those--i.e. all positions not present in the intervals defined in sites are lost.
        For example, if you pass a vector<int> containing the values 0,10,21, and 30, then
        the data vector is modified so that positions 0 through 10 and 21 through 30 are all
        that remains. One intended use of this function is to pull, for example, the coding r
        egion out of an aligned block.

        Trim(sites)
        sites 	vector<int> containing an even number of integers specifying the intervals of data to keep

        >>> p = pVector(2)
        >>> p[0] = strPair('s1', 'ATGG-CT')
        >>> p[1] = strPair('s2', 'CC-T-GC')
        >>> clus = ClustalW_str(p)
        >>> sites = intVector(2)
        >>> sites[0] = 0
        >>> sites[1] = 3
        >>> clus.Trim(sites)
        (('s1', 'ATGG'), ('s2', 'CC-T'))
        """

    def testTrimComplement():
        """Returns a copy the data vector, modified in the following way. The sites vector contains an
        even number of sites (whose values are sorted). If sites does not contain an even number of values
        Sequence::SeqException is thrown. If sites is empty, Sequence::SeqException is thrown. The values
        in sites represent a series of intervals that you wish to keep, and the return vector consists only
        of sites not present in sites--i.e. all positions not present in the intervals defined in sites are
        kept. For example, if you pass a vector<int> containing the values 0,10,21, and 30, then the data
        vector is modified so that positions 11 through 20 and 31 through the end of the sequences are all
        that remains.
        
        TrimComplement(sites)
        sites vector<int> containing an even number of integers specifying the intervals of data to throw away

        >>> p = pVector(2)
        >>> p[0] = strPair('s1', 'GT-CT')
        >>> p[1] = strPair('s2', 'ACTTC')
        >>> c = ClustalW_str(p)
        >>> s = intVector(2)
        >>> s[0] = 1
        >>> s[1] = 2
        >>> c.Trim(s)
        (('s1', 'T-'), ('s2', 'CT'))
        >>> c.TrimComplement(s)
        (('s1', 'GCT'), ('s2', 'ATC'))
        
        """

def TestAlign_IsAlignment():
    """A vector of sequences/strings is only an alignment if all strings are the same length.

     Align_IsAlignment(data)
     data 	vector<std::pair<std::string, std::string> > to check

     >>> v = pVector(2)
     >>> v[0] = strPair('s1', 'AT-G-')
     >>> v[1] = strPair('s2', '-NCT-')
     >>> Align_IsAlignment(v)
     True
     """

def TestAlign_Gapped():
    """Returns:true if the vector contains a gap character ('-') , false otherwise.

    Align_Gapped(data)
    data 	vector<std::pair<std::string, std::string> > containing sequence data

    >>> v = pVector(2)
    >>> v[0] = strPair('s1', 'GT-CAG')
    >>> v[1] = strPair('s2', '-C-NT-')
    >>> Align_Gapped(v)
    True
    """

def TestAlign_RemoveGaps():
    """Modifies the data vector to remove all positions that contain the gap character'-'.

    Align_RemoveGaps(data)
    data 	vector<std::pair<std::string, std::string> > to modify

    >>> v = pVector(2)
    >>> v[0] = strPair('s1', 'GT-CAG')
    >>> v[1] = strPair('s2', '-C-NT-')
    >>> Align_Gapped(v)
    True
    >>> Align_RemoveGaps(v)
    >>> Align_Gapped(v)
    False
    """

def TestAlign_RemoveTerminalGaps():
    """Remove all gapped sites from the ends of the alignment, up until the first site on either side that is ungapped.

    Align_RemoveTerminalGaps(data)
    data 	vector<std::pair<std::string, std::string> > to modify

    >>> v = pVector(2)
    >>> v[0] = strPair('s1', 'GT-CAG')
    >>> v[1] = strPair('s2', '-C-NT-')
    >>> Align_RemoveTerminalGaps(v)
    >>> v[0]
    ('s1', 'T-CA')
    >>> v[1]
    ('s2', 'C-NT')
    """


def TestAlign_Trim():
    """Returns a copy of the data vector, modified in the following way.
    The sites vector contains an even number of sites (whose values are sorted).
    If sites does not contain an even number of values Sequence::SeqException is
    thrown. If sites is empty, Sequence::SeqException is thrown. The values in
    sites represent a series of intervals that you wish to keep, and the return
    vector is consists only of those--i.e. all positions not present in the intervals
    defined in sites are lost. For example, if you pass a vector<int> containing the
    values 0,10,21, and 30, then the data vector is modified so that positions 0 through
    10 and 21 through 30 are all that remains. One intended use of this function is to
    pull, for example, the coding region out of an aligned block.

    Align_Trim(data, sites)
    Parameters:
    data 	the original data
    sites 	vector<int> containing an even number of integers specifying the intervals of data to keep

    >>> v = pVector(2)
    >>> v[0] = strPair('s1', 'GT-CAG')
    >>> v[1] = strPair('s2', '-C-NT-')
    >>> sites = intVector(2)
    >>> sites[0] = 1
    >>> sites[1] = 3
    >>> Align_Trim(v, sites)
    (('s1', 'T-C'), ('s2', 'C-N'))
    """

def TestAlign_Trim_Complement():
    """Returns a copy the data vector, modified in the following way. The sites vector
    contains an even number of sites (whose values are sorted). If sites does not contain
    an even number of values Sequence::SeqException is thrown. If sites is empty,
    Sequence::SeqException is thrown. The values in sites represent a series of intervals that
    you wish to keep, and the return vector consists only of sites not present in sites--i.e.
    all positions not present in the intervals defined in sites are kept. For example, if you pass
    a vector<int> containing the values 0,10,21, and 30, then the data vector is modified so that
    positions 11 through 20 and 31 through the end of the sequences are all that remains.

    Align_Trim_Complement(data, sites)
    Parameters:
    data 	the original data
    sites 	vector<int> containing an even number of integers specifying the intervals of data to throw away

    >>> v = pVector(2)
    >>> v[0] = strPair('s1', 'GT-CAG')
    >>> v[1] = strPair('s2', '-C-NT-')
    >>> sites = intVector(2)
    >>> sites[0] = 1
    >>> sites[1] = 3
    >>> Align_TrimComplement(v, sites)
    (('s1', 'GAG'), ('s2', '-T-'))
    """

def TestAlign_RemoveFixedOutgroupInsertions():
    """Removes all positions from data that for which the outgroup contains an insertion relative to ingroup

    Align_RemoveFixedOutgroupInsertions(data, sites, ref)
    Parameters:
    data 	a vector of Seq objects
    site 	index of the site at which to begin (set to 0 usually)
    ref 	the index of the outgroup in data

    >>> v = pVector(2)
    >>> v[0] = strPair('s1', 'GT-CAG')
    >>> v[1] = strPair('s2', '-C-NT-')
    >>> Align_RemoveFixedOutgroupInsertions(v, 0, 3)
    >>> v[0]
    ('s1', 'T-CA')
    >>> v[1]
    ('s2', 'C-NT')
    """

    
def TestAlign_validForPolyAnalysis():
    """Returns:true if each element in the range [beg,end) only contains characters in the set
    {A,G,C,T,N,-}, false otherwise

    Align_validForPolyAnalysis(beg,end)

    
    >>> p = pVector(2)
    >>> p[0] = strPair('s1', 'GT-CAG')
    >>> p[1] = strPair('s2', '-C-NT-')
    >>> beg = p.begin()
    >>> end = p.end()
    >>> Align_validForPolyAnalysis(beg,end)
    True
    """
def TestHudsonsC():
    """Returns Hudson's (1987) Genetical Research 50:245-250 moment estimator of
    the population recombination rate. 

    >>> v = fastaVector(2)
    >>> v[0] = Fasta('s1','ATCC')
    >>> v[1] = Fasta('s2','TGGG')
    >>> p = PolySites(v)
    >>> HudsonsC(p,False,0)
    10000.0
    """


       
########excute the test############
if __name__ == "__main__":
##    suite = unittest.TestSuite()
##    suite.addTest(doctest.DocTestSuite())
##    runner = unittest.TextTestRunner()
##    runner.run(suite)
##    unittest.main()
    doctest.testmod()
