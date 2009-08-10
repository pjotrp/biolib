"""
{AbstractAlphabet.i}
[class] AbstractAlphabet:
see Alphabet--partial implementation of interface

{Alphabet.i}
[class] Alphabet:
>>> alpha = bpp.DefaultAlphabet()
>>> dna = bpp.DNA()

>>> alpha.getSupportedInts()
(-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37)
>>> alpha.getSupportedChars()
('-', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '?')
>>> alpha.isIntInAlphabet(1)
True
>>> alpha.isIntInAlphabet(666)
False
>>> alpha.isCharInAlphabet('F')
True
>>> alpha.isCharInAlphabet('f')
True
>>> alpha.getSize()
26
>>> dna.getSize()
4
>>> alpha.getNumberOfChars()
39
>>> dna.getNumberOfChars()
20
>>> alpha.getNumberOfTypes()
27
>>> dna.getNumberOfTypes()
15
>>> alpha.intToChar(7)
'H'
>>> alpha.charToInt('z')
25

>>> alpha.getGapCharacterCode()
-1
>>> alpha.isGap(-1)
True
>>> alpha.isGap(0)
False
>>> alpha.isGap('-')
True
>>> alpha.isGap('A')
False
>>> alpha.getUnknownCharacterCode()
38
>>> dna.isUnresolved('Y')
True
>>> alpha.isUnresolved(2)
False
>>> alpha.getGeneric([0,1])
38
>>> bpp.DNA().stringGetGeneric(['A','G'])
'R'

>>> alpha.getAlias(1)
(1,)
>>> alpha.getAlias('A')
('A',)
>>> dna.getAlias('R')
('A', 'G')
>>> alpha.getName(-1)
'Gap'
>>> dna.getName('A')
'Adenine'

>>> alpha.getAlphabetType()
'Default alphabet'

{AlphabetExceptions.i}
[class] AlphabetException
>>> alpha = bpp.DefaultAlphabet()
>>> x = bpp.AlphabetException("bad alphabet!", alpha)
>>> x.getAlphabet()
<bpp.Alphabet; proxy of <Swig Object of type 'Alphabet *' at 0x...> >
>>> x.what()
'AlphabetException: bad alphabet!(Default alphabet)'

[class] BadCharException
>>> x = bpp.BadCharException("ZZ", "ZZ isn't a letter!", alpha)
>>> x.getBadChar()
'ZZ'
>>> x.what()
"AlphabetException: BadCharException: ZZ. ZZ isn't a letter!(Default alphabet)"

[class] BadIntException
>>> x = bpp.BadIntException(-666, "I don't like -666", alpha)
>>> x.getBadInt()
-666
>>> x.what()
"AlphabetException: BadIntException: -666. I don't like -666(Default alphabet)"

[class] AlphabetMismatchException
>>> alpha = bpp.DefaultAlphabet()
>>> dna = bpp.DNA()
>>> rna = bpp.RNA()
>>> x = bpp.AlphabetMismatchException("bad alphabets!", dna, rna)
>>> x.what()
'AlphabetMismatchException: bad alphabets!(DNA alphabet, RNA alphabet)'

[class] CharStateNotSupportedException
>>> x = bpp.CharStateNotSupportedException("bad state", alpha)
>>> x.what()
'AlphabetException: CharStateNotSupportedException: bad state(Default alphabet)'


{AlphabetTools.i}
[class] AlphabetTools
>>> alpha = bpp.DefaultAlphabet()
>>> dna = bpp.DNA()
>>> rna = bpp.RNA()
>>> proteins = bpp.ProteicAlphabet()
>>> codons = bpp.StandardCodonAlphabet(dna)
>>> bpp.AlphabetTools.getType('A')
7
>>> bpp.AlphabetTools.getType('-')
-1
>>> bpp.AlphabetTools.checkAlphabetCodingSize(alpha)
True
>>> bpp.AlphabetTools.getAlphabetCodingSize(alpha)
1
>>> bpp.AlphabetTools.isNucleicAlphabet(dna)
True
>>> bpp.AlphabetTools.isDNAAlphabet(dna)
True
>>> bpp.AlphabetTools.isRNAAlphabet(rna)
True
>>> bpp.AlphabetTools.isProteicAlphabet(proteins)
True
>>> bpp.AlphabetTools.isCodonAlphabet(codons)
True
>>> bpp.AlphabetTools.match(dna,0,4)
True


{CodonAlphabet.i}
[class] CodonAlphabet:
note--bug in tested version in getPositions()--likely fixed in current version
>>> dna = bpp.DNA()
>>> sca = bpp.StandardCodonAlphabet(dna)
>>> sca.getSupportedChars()
('---', 'AAA', 'AAC', 'AAG', 'AAT', 'ACA', 'ACC', 'ACG', 'ACT', 'AGA', 'AGC', 'AGG', 'AGT', 'ATA', 'ATC', 'ATG', 'ATT', 'CAA', 'CAC', 'CAG', 'CAT', 'CCA', 'CCC', 'CCG', 'CCT', 'CGA', 'CGC', 'CGG', 'CGT', 'CTA', 'CTC', 'CTG', 'CTT', 'GAA', 'GAC', 'GAG', 'GAT', 'GCA', 'GCC', 'GCG', 'GCT', 'GGA', 'GGC', 'GGG', 'GGT', 'GTA', 'GTC', 'GTG', 'GTT', 'TAA', 'TAC', 'TAG', 'TAT', 'TCA', 'TCC', 'TCG', 'TCT', 'TGA', 'TGC', 'TGG', 'TGT', 'TTA', 'TTC', 'TTG', 'TTT', 'NNN')
>>> sca.STOP
'Stop'
>>> sca.getName("AAA")
''
>>> sca.charToInt("TAG")
-3
>>> sca.charToInt("TTG")
59
>>> sca.getAlphabetType()
'Standard codon alphabet'
>>> sca.getUnknownCharacterCode()
61
>>> sca.isUnresolved(61)
True
>>> sca.isUnresolved('nnn')
True
>>> sca.getCodon(0,0,0)
0
>>> sca.getCodon(1,0,1)
17
>>> sca.getCodon(0,1,2)
6
>>> sca.getCodon("C","A","G")
'CAG'
>>> sca.getFirstPosition(6)
0
>>> sca.getSecondPosition(6)
1
>>> sca.getThirdPosition(6)
2
>>> sca.getPositions(6)
(0, 1, 2)
>>> sca.getFirstPosition("CAG")
''
>>> sca.getPositions("CAG")
...
>>> sca.isStop(-2)
True
>>> sca.isStop("TAG")
True
>>> sca.getNucleicAlphabet()
<bpp.NucleicAlphabet; proxy of <Swig Object of type 'NucleicAlphabet *' at 0x...> >


{DefaultAlphabet.i}
[class] DefaultAlphabet:
>>> alpha = bpp.DefaultAlphabet()
>>> alpha.getSize()
26
>>> alpha.getNumberOfTypes()
27
>>> alpha.getAlphabetType()
'Default alphabet'
>>> alpha.getUnknownCharacterCode()
38
>>> alpha.isUnresolved(6)
False
>>> alpha.isUnresolved('A')
False

{DNA.i}
[class] DNA:


>>> dna = bpp.DNA()
>>> dna.getAlias('A')
('A',)
>>> dna.getAlias('R')
('A', 'G')
>>> dna.getAlias(10)
(0, 1, 2)
>>> dna.getGeneric([0,1,2])
10
>>> dna.stringGetGeneric(['A','G','T'])
'D'
>>> dna.getAlphabetType()
'DNA alphabet'


{EchinodermMitochondrialCodonAlphabet.i}
[class] EchinodermMitochondrialCodonAlphabet:
>>> dna = bpp.DNA()
>>> emca = bpp.EchinodermMitochondrialCodonAlphabet(dna)
>>> emca.getSupportedChars()
('---', 'AAA', 'AAC', 'AAG', 'AAT', 'ACA', 'ACC', 'ACG', 'ACT', 'AGA', 'AGC', 'AGG', 'AGT', 'ATA', 'ATC', 'ATG', 'ATT', 'CAA', 'CAC', 'CAG', 'CAT', 'CCA', 'CCC', 'CCG', 'CCT', 'CGA', 'CGC', 'CGG', 'CGT', 'CTA', 'CTC', 'CTG', 'CTT', 'GAA', 'GAC', 'GAG', 'GAT', 'GCA', 'GCC', 'GCG', 'GCT', 'GGA', 'GGC', 'GGG', 'GGT', 'GTA', 'GTC', 'GTG', 'GTT', 'TAA', 'TAC', 'TAG', 'TAT', 'TCA', 'TCC', 'TCG', 'TCT', 'TGA', 'TGC', 'TGG', 'TGT', 'TTA', 'TTC', 'TTG', 'TTT', 'NNN')
>>> emca.getSize()
62
>>> emca.getNumberOfTypes()
63
>>> emca.getAlphabetType()
'EchinodermMitochondrial codon alphabet'
>>> emca.isStop(-2)
True
>>> emca.isStop("TAG")
True


{InvertebrateMitochondrialCodonAlphabet.i}
[class] InvertebrateMitochondrialCodonAlphabet:
>>> rna = bpp.RNA()
>>> imca = bpp.InvertebrateMitochondrialCodonAlphabet(rna)
>>> imca.getSize()
62
>>> imca.getNumberOfTypes()
63
>>> imca.getAlphabetType()
'Invertebrate mitochondrial codon alphabet'
>>> imca.isStop(5)
False
>>> imca.isStop("UAG")
True


{NucleicAlphabet.i}
[class] NucleicAlphabet:
>>> dna = bpp.DNA()
>>> dna.getSize()
4
>>> dna.getNumberOfTypes()
15
>>> dna.getUnknownCharacterCode()
14
>>> dna.isUnresolved(10)
True


{ProteicAlphabet.i}
[class] ProteicAlphabet:
>>> pa = bpp.ProteicAlphabet()
>>> pa.getSupportedChars()
('-', 'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V', 'B', 'Z', 'X', 'O', '0', '?')
>>> pa.getName('A')
'Alanine'
>>> pa.getSize()
20
>>> pa.getNumberOfTypes()
23
>>> pa.getUnknownCharacterCode()
22
>>> pa.getAlias(0)
(0,)
>>> pa.getAlias(20)
(2, 3)
>>> pa.getAlias('B')
('N', 'D')
>>> pa.getGeneric([2,3])
20
>>> pa.stringGetGeneric(['N','D'])
'B'
>>> pa.isUnresolved(20)
True
>>> pa.isUnresolved('A')
False
>>> pa.getAlphabetType()
'Proteic alphabet'
>>> pa.getAbbr('A')
'ALA'
>>> pa.getAbbr(19)
'VAL'


{RNA.i}
[class] RNA:
>>> rna = bpp.RNA()
>>> rna.getAlias('Y')
('C', 'U')
>>> rna.getAlias(10)
(0, 1, 2)
>>> rna.getAlias('U')
('U',)
>>> rna.stringGetGeneric(['A','G','U'])
'D'
>>> rna.getGeneric([0,1,2])
10
>>> rna.getAlphabetType()
'RNA alphabet'


{Sequence.i}
[class] Sequence:
>>> import bpp
>>> dna = bpp.DNA()
>>> seq = bpp.Sequence("test", "AGGTCT", dna)
>>> seq.clone()
<bpp.Sequence; proxy of <Swig Object of type 'Sequence *' at 0x...> >
>>> seq.getAlphabet()
<bpp.Alphabet; proxy of <Swig Object of type 'std::vector< Alphabet *,std::allocator< Alphabet const * > >::value_type' at 0x...> >
>>> seq.size()
6
>>> seq.toString()
'AGGTCT'
>>> seq.getName()
'test'
>>> seq.setName('Test')
>>> seq.getSense()
True
>>> seq.setSense(False)
>>> seq.setComments(['this is a comment','this is another'])
>>> seq.getComments()
('this is a comment', 'this is another')

>>> seq.setToSizeR(8)
>>> seq.setToSizeL(9)
>>> seq.toString()
'-AGGTCT--'

>>> seq.intVecAppend([1])
>>> seq.strVecAppend(['A','C'])
>>> seq.append("GGG")
>>> seq.toString()
'-AGGTCT--CACGGG'

>>> seq.strVecSetContent(['A','G'])
>>> seq.intVecSetContent([0,1])
>>> seq.setContent("agt")
>>> seq.toString()
'AGT'

>>> seq = bpp.Sequence("test", "AGGTCT", ["comment1","comment2"], dna)
>>> seq = bpp.strVecSequence("test", ['a','g'], dna)
>>> seq = bpp.strVecSequence("test", ['a','g'], ["comment1","comment2"], dna)
>>> seq = bpp.intVecSequence("test", [0,1], dna)
>>> seq = bpp.intVecSequence("test", [0,1], ["comment1","comment2"], dna)


{SequenceTools.i}
[class] BowkerTest
>>> dna = bpp.DNA()
>>> seq = bpp.Sequence("test", "AGGTCT", dna)
>>> seqA = bpp.Sequence("aligned", "AG--TT", dna)
>>> bowker = bpp.SequenceTools.bowkerTest(seq,seqA)
>>> bowker.getName()
"Bowker's test for homogeneity."
>>> bowker.getStatistic()
1.0
>>> bowker.getPValue()
0.80125195693584916
>>> bowker.clone()
<bpp.BowkerTest; proxy of <Swig Object of type 'BowkerTest *' at 0x...> >
>>> bowker.setStatistic(0.5)
>>> bowker.setPValue(-1)

[class] SequenceTools
>>> dna = bpp.DNA()
>>> seq = bpp.Sequence("test", "AGGTCT", dna)
>>> seq1 = bpp.Sequence("test1", "GGG", dna)
>>> seqA = bpp.Sequence("aligned", "AG--TT", dna)

>>> bpp.SequenceTools.subseq(seq,0,4).toString()
'AGGTC'
>>> bpp.SequenceTools.concatenate(seq,seq1).toString()
'AGGTCTGGG'
>>> bpp.SequenceTools.complement(seq).toString()
'TCCAGA'
>>> bpp.SequenceTools.transcript(seq).toString()
'UCCAGA'
>>> bpp.SequenceTools.reverseTranscript(bpp.SequenceTools.transcript(seq)).toString()
'AGGTCT'
>>> bpp.SequenceTools.invert(seq,True).toString()
'TCTGGA'
>>> bpp.SequenceTools.reverse(seq).toString()
'TCTGGA'
>>> bpp.SequenceTools.getPercentIdentity(seq,seqA)
50.0
>>> bpp.SequenceTools.getNumberOfCompleteSites(bpp.Sequence("test", "AH--TT", dna))
3
>>> bpp.SequenceTools.getNumberOfSites(bpp.Sequence("test", "AH--TT", dna))4
>>> bpp.SequenceTools.removeGaps(seqA).toString()
'AGTT'

>>> bpp.SequenceTools.bowkerTest(seq,seqA)

>>> hetero = bpp.Sequence("heterozygous", "ATTCGGGKWTATRYRM", dna)
>>> haplo = bpp.Sequence("haplotype", "ATTCGGGTATATGCAA", dna)
>>> bpp.SequenceTools.subtractHaplotype(hetero, haplo, "result").toString()
'ATTCGGGNNTATNNNN'
>>> bpp.SequenceTools.bowkerTest(seq,seqA)
<bpp.BowkerTest; proxy of <Swig Object of type 'BowkerTest *' at 0x...> >



{StandardCodonAlphabet.i}
[class] StandardCodonAlphabet:
>>> dna = bpp.DNA()
>>> sca = bpp.StandardCodonAlphabet(dna)
>>> sca.isStop("TAG")
True
>>> sca.getSize()
61
>>> sca.getNumberOfTypes()
62
>>> sca.getAlphabetType()
'Standard codon alphabet'
>>> sca.isStop(-1)
False
>>> sca.isStop("TAG")
True


{VertebrateMitochondrialCodonAlphabet.i}
[class] VertebrateMitochondrialCodonAlphabet
>>> dna = bpp.DNA()
>>> vmca = bpp.VertebrateMitochondrialCodonAlphabet(dna)
>>> vmca.getSize()
60
>>> vmca.getNumberOfTypes()
61
>>> vmca.getAlphabetType()
'Vertebrate mitochondrial codon alphabet'
>>> vmca.isStop(-3)
True
>>> vmca.isStop("taa")
True


"""


import doctest
import bpp
doctest.testmod(optionflags = 8)
