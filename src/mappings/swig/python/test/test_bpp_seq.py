"""
{AAChargeIndex.i}
[class] AAChargeIndex:
>>> charges = bpp.AAChargeIndex()
>>> charges.clone()
<bpp.AAChargeIndex; proxy of <Swig Object of type 'AAChargeIndex *' at 0x...> >
>>> charges.getIndex(0)
0.0
>>> charges.getIndex(1)
1.0
>>> charges.getIndex('d')
-1.0
>>> charges.getIndexVector()
<bpp.doubleVector; proxy of <Swig Object of type 'std::vector< double > *' at 0x...> >
>>> charges.getAlphabet().getAlphabetType()
'Proteic alphabet'


{AAIndex1Entry.i}
# aa1.txt is as follows:
I
0 1 2 3 4 5 6 7 8 9
10 11 12 13 14 15 16 17 18 19
[class] AAIndex1Entry:
>>> stream = bpp.ifstream("aa1.txt")
>>> aa1 = bpp.AAIndex1Entry(stream)
>>> aa1.clone()
<bpp.AAIndex1Entry; proxy of <Swig Object of type 'AAIndex1Entry *' at 0x...> >
>>> bpp.AAIndex1Entry(aa1)
<bpp.AAIndex1Entry; proxy of <Swig Object of type 'AAIndex1Entry *' at 0x...> >

>>> aa1.getIndex(1)
1.0
>>> aa1.getIndex('r')
1.0
>>> aa1.getAlphabet().getAlphabetType()
'Proteic alphabet'
>>> aa1.getIndexVector()[0]
0.0
>>> aa1.getIndexVector()[19]
19.0


{AAIndex2Entry.i}
# aa2.txt is as follows:
M
<space-separated 20x20 matrix>
[class] AAIndex2Entry:
>>> stream = bpp.ifstream("aa2.txt")
>>> aa2 = bpp.AAIndex2Entry(stream)
>>> aa2.clone()
<bpp.AAIndex2Entry; proxy of <Swig Object of type 'AAIndex2Entry *' at 0x...> >
>>> bpp.AAIndex2Entry(aa2)
<bpp.AAIndex2Entry; proxy of <Swig Object of type 'AAIndex2Entry *' at 0x...> >

>>> aa2.getIndex(0,1)
2.0
>>> aa2.getIndex('a','r')
2.0
>>> aa2.getIndexMatrix()
<bpp.doubleMatrix; proxy of <Swig Object of type 'Matrix< double > *' at 0x...> >
>>> aa2.getAlphabet().getAlphabetType()
'Proteic alphabet'


{AbstractAlphabet.i}
[class] AbstractAlphabet:
see Alphabet--partial implementation of interface


{AbstractISequence.i}
[class] (partial) AbstractISequence:
>>> fasta = bpp.Fasta()
>>> dna = bpp.DNA()

>>> container0 = bpp.VectorSequenceContainer(dna)
>>> container0.getNumberOfSequences()
0
>>> input = bpp.ifstream("data1.fas")
>>> fasta.read(input, container0)
>>> container0.getNumberOfSequences()
3

>>> container1 = bpp.VectorSequenceContainer(dna)
>>> container1.getNumberOfSequences()
0
>>> fasta.read("data1.fas", container1)
>>> container1.getNumberOfSequences()
3

>>> input = bpp.ifstream("data1.fas")
>>> container2 = fasta.read(input, dna)
>>> container2.getNumberOfSequences()
3

>>> container3 = fasta.read("data1.fas", dna)
>>> container3.getNumberOfSequences()
3


{AbstractISequence2.i}
[class] (partial) AbstractISequence2:
>>> dcse = bpp.DCSE()
>>> rna = bpp.RNA()

>>> aseqs0 = bpp.AlignedSequenceContainer(rna)
>>> aseqs0.getNumberOfSequences()
0
>>> input = bpp.ifstream("data.bpp-ali")
>>> dcse.read(input, aseqs0)
>>> aseqs0.getNumberOfSequences()
4

>>> aseqs1 = bpp.AlignedSequenceContainer(rna)
>>> aseqs1.getNumberOfSequences()
0
>>> dcse.read("data.bpp-ali", aseqs1)
>>> aseqs1.getNumberOfSequences()
4

>>> input = bpp.ifstream("data.bpp-ali")
>>> aseqs2 = dcse.read(input, rna)
>>> aseqs2.getNumberOfSequences()
4

>>> aseqs3 = dcse.read("data.bpp-ali", rna)
>>> aseqs3.getNumberOfSequences()
4


{AbstractOSequence.i}
[class] (partial) AbstractOSequence:
>>> fasta = bpp.Fasta()
>>> input = bpp.ifstream("data1.fas")
>>> dna = bpp.DNA()
>>> container = bpp.VectorSequenceContainer(dna)
>>> fasta.appendFromStream(input, container)

#>>> fasta.write(bpp.ApplicationTools.getMessage(), container)
#>seq1
#ATGCCGTGGTCCCGT
#>seq2
#TTTGGCGACCGTAACCCGT
#>seq3
#GAGACTAGCTGA
>>> fasta.write("output-file.fas", container)


{AbstractSequenceContainer.i}
[class] (partial) AbstractSequenceContainer:
>>> dna = bpp.DNA()
>>> seq0 =  bpp.Sequence("Sequence_0", "AGGTCT", dna)
>>> seq1 =  bpp.Sequence("Sequence_1", "TGTCAT", dna)
>>> vsc = bpp.VectorSequenceContainer([seq0,seq1],dna)

>>> vsc.getAlphabet().getAlphabetType()
'DNA alphabet'
>>> vsc.getName(0)
'Sequence_0'
>>> vsc.getContent(0)
(0, 2, 2, 3, 1, 3)
>>> vsc.getContent("Sequence_0")
(0, 2, 2, 3, 1, 3)
>>> vsc.toString(0)
'AGGTCT'
>>> vsc.toString("Sequence_0")
'AGGTCT'

>>> vsc.setComments(0, ["this is a comment", "so is this"])
>>> vsc.getComments(0)
('this is a comment', 'so is this')
>>> vsc.setComments("Sequence_1", ["these are comments too", "yup"])
>>> vsc.getComments("Sequence_1")
('these are comments too', 'yup')
>>> vsc.setGeneralComments(["well hello there"])
>>> vsc.getGeneralComments()
('well hello there',)
>>> vsc.deleteGeneralComments()
>>> vsc.getGeneralComments()
()


{AlignedSequenceContainer.i}
[class] AlignedSequenceContainer:
>>> dna = bpp.DNA()
>>> seq1 = bpp.Sequence("seq1", "AAAAA", dna)
>>> seq2 = bpp.Sequence("seq2", "CCCCC", dna)
>>> seq3 = bpp.Sequence("seq3", "G-G-G", dna)
>>> seqX = bpp.Sequence("seqX", "AAAAAA", dna)
>>> site1 = bpp.Site(['G','G'], dna, 11)
>>> site2 = bpp.Site(['T','T'], dna, 12)
>>> seqs = bpp.AlignedSequenceContainer(dna)

>>> seqs.addSequence(seq1)
>>> seqs.addSequence(seqX)
Traceback (most recent call last):
...
Exception: <bpp.Exception; proxy of <Swig Object of type 'Exception *' at 0x...> >
>>> seqs.addSequence(seq3, 0)
>>> 
>>> seqs.setSequence("seq1", seq2)
>>> seqs.setSequence(0, seq1)
>>> 
>>> seqs.getNumberOfSites()
5
>>> seqs.getSitePositions()
(1, 2, 3, 4, 5)
>>> seqs.getSite(0).toString()
'AC'
>>> 
>>> seqs.addSite(site1)
>>> seqs.addSite(site2,0)
>>> seqs.getSitePositions()
(12, 1, 2, 3, 4, 5, 11)
>>> seqs.reindexSites()
>>> seqs.getSitePositions()
(1, 2, 3, 4, 5, 6, 7)
>>> seqs.getSequence(0).toString()
'TAAAAAG'
>>> seqs.toString(0)
'TAAAAAG'
>>> seqs.removeSite(0)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> seqs.deleteSite(5)
>>> seqs.createEmptyContainer().getNumberOfSequences()
0
>>> seqs.clear()
>>> seqs.clone()
<bpp.AlignedSequenceContainer; proxy of <Swig Object of type 'AlignedSequenceContainer *' at 0x...> >
>>> bpp.AlignedSequenceContainer(seqs)
<bpp.AlignedSequenceContainer; proxy of <Swig Object of type 'AlignedSequenceContainer *' at 0x...> >


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
>>> x.getAlphabet().getAlphabetType()
'Default alphabet'
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


{AlphabetIndex1.i}
[class] interface AlphabetIndex1
>>> klein = bpp.KleinAANetChargeIndex()
>>> klein.getIndex(0)
0.0
>>> klein.getIndex('s')
0.0
>>> klein.getIndexVector()
<bpp.doubleVector; proxy of <Swig Object of type 'std::vector< double > *' at 0x...> >
>>> klein.getAlphabet().getAlphabetType()
'Proteic alphabet'


{AlphabetIndex2.i}
[class] interface AlphabetIndex2
>>> dna = bpp.DNA()
>>> scores = bpp.DefaultNucleotideScore(dna)
>>> scores.getIndex(0,1)
-3.0
>>> scores.getIndex('a','c')
-3.0

#>>> bpp.MatrixTools._print(scores.getIndexMatrix())
#4x4
#[
#[10, -3, -1, -4]
#[-3, 9, -5, 0]
#[-1, -5, 7, -3]
#[-4, 0, -3, 8]
#]



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


{BLOSUM50.i}
[class] BLOSUM50
>>> blosum = bpp.BLOSUM50()
>>> blosum.clone()
<bpp.BLOSUM50; proxy of <Swig Object of type 'BLOSUM50 *' at 0x...> >
>>> blosum.getIndex(5,14)
-1.0
>>> blosum.getIndex('S','S')
5.0
>>> blosum.getAlphabet().getAlphabetType()
'Proteic alphabet'
>>> blosum.getIndexMatrix()
<bpp.doubleMatrix; proxy of <Swig Object of type 'Matrix< double > *' at 0x...> >


{Clustal.i}
[class] Clustal:
>>> clustal = bpp.Clustal()
>>> clustal.getFormatName()
'Clustal'
>>> clustal.getFormatDescription()
'The Clustal alignment tool output format.'
>>> prot = bpp.ProteicAlphabet()
>>> aseqs = bpp.AlignedSequenceContainer(prot)
>>> stream = bpp.ifstream("data.bpp-aln")
>>> 
>>> clustal.appendFromStream(stream, aseqs)
>>> aseqs.getNumberOfSequences()
2
>>> aseqs.toString(0)
'FQA...
>>> clustal.checkNames()
True
>>> clustal.checkNames(False)
>>> clustal.checkNames()
False


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
(...)
>>> sca.isStop(-2)
True
>>> sca.isStop("TAG")
True
>>> sca.getNucleicAlphabet()
<bpp.NucleicAlphabet; proxy of <Swig Object of type 'NucleicAlphabet *' at 0x...> >


{CodonSiteTools.i}
[class] CodonSiteTools:
>>> import bpp
>>> dna = bpp.DNA()
>>> code = bpp.StandardGeneticCode(dna)
>>> alpha = bpp.StandardCodonAlphabet(dna)
>>> site = bpp.Site(['TAG','AAA','CCC'],alpha,300)
>>> site1 = bpp.Site(['TAT','AAA','CCC'],alpha,600)

>>> bpp.CodonSiteTools.hasGapOrStop(site)
True
>>> bpp.CodonSiteTools.hasStop(site)
True
>>> bpp.CodonSiteTools.isMonoSitePolymorphic(site1)
False
>>> bpp.CodonSiteTools.isSynonymousPolymorphic(site1,code)
False
>>> site2 = bpp.CodonSiteTools.generateCodonSiteWithoutRareVariant(site1, 0.25)
>>> site2.getContent()
(49, 0, 21)
>>> bpp.CodonSiteTools.numberOfDifferences(3,4,alpha)
2
>>> bpp.CodonSiteTools.numberOfSynonymousDifferences(2,4,code)
1.0
>>> bpp.CodonSiteTools.piSynonymous(site1,code,False)
0.5
>>> bpp.CodonSiteTools.piNonSynonymous(site1,code,False)
2.166...
>>> bpp.CodonSiteTools.numberOfSynonymousPositions(1,code,1.0)
0.333...
>>> bpp.CodonSiteTools.meanNumberOfSynonymousPositions(site1,code,1.0)
0.555...
>>> bpp.CodonSiteTools.numberOfSubsitutions(site,0.0)
5
>>> bpp.CodonSiteTools.numberOfNonSynonymousSubstitutions(site1,code,0.0)
4
>>> bpp.CodonSiteTools.fixedDifferences(site,site1,0,1,code)
(0, 0)


{DCSE.i}
[class] DCSE:
>>> dcse = bpp.DCSE()
>>> dcse.getFormatName()
'DCSE'
>>> dcse.getFormatDescription()
'RNA structure format'
>>> rna = bpp.RNA()
>>> aseqs = bpp.AlignedSequenceContainer(rna)
>>> stream = bpp.ifstream("data.bpp-ali")
>>> dcse.appendFromStream(stream, aseqs)
>>> aseqs.getNumberOfSequences()
4
>>> aseqs.toString(0)
'ACGACGGUNU'


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



{DefaultNucleotideScore.i}
[class] DefaultNucleotideScore:
>>> dna = bpp.DNA()
>>> scores = bpp.DefaultNucleotideScore(dna)
>>> scores.getIndex(0,1)
-3.0
>>> scores.getIndex('a','c')
-3.0
>>> scores.clone()
<bpp.DefaultNucleotideScore; proxy of <Swig Object of type 'DefaultNucleotideScore *' at 0x...> >
>>> bpp.MatrixTools._print(scores.getIndexMatrix())


{DistanceMatrix.i}
[class] DistanceMatrix:
>>> dm = bpp.DistanceMatrix(["a","b","c"])
>>> dm.size()
3
>>> dm.getNames()
('a', 'b', 'c')
>>> dm.getName(0)
'a'
>>> dm.getNameIndex('a')
0
>>> dm[0]
(0.0, 0.0, 0.0)
>>> dm[0][0]
0.0
>>> dm.setName(1, 'B')
>>> dm.getNames()
('a', 'B', 'c')
>>> dm.setNames(['A','B','C'])
>>> dm.getNames()
('A', 'B', 'C')

>>> dm.nRows()
3
>>> bpp.DistanceMatrix(dm)
<bpp.DistanceMatrix; proxy of <Swig Object of type 'DistanceMatrix *' at 0x...> >
>>> bpp.DistanceMatrix(5)
<bpp.DistanceMatrix; proxy of <Swig Object of type 'DistanceMatrix *' at 0x...> >
>>> bpp.DistanceMatrix(5).nRows()
5
>>> dm.reset()


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


{DNAToRNA.i}
[class] DNAToRNA:
>>> d2r = bpp.DNAToRNA()
>>> dna = bpp.DNA()
>>> rna = bpp.RNA()
>>> dSeq = bpp.Sequence("dna-seq", "ACGT",dna)

>>> d2r.getSourceAlphabet().getAlphabetType()
'DNA alphabet'
>>> d2r.getTargetAlphabet().getAlphabetType()
'RNA alphabet'

>>> d2r.translate("T")
'U'
>>> d2r.translate(2)
2
>>> rSeq = d2r.translate(dSeq)
>>> rSeq.toString()
'ACGU'
>>> d2r.reverse("U")
'T'
>>> d2r.reverse(2)
2
>>> d2r.reverse(rSeq).toString()
'ACGT'


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


{EchinodermMitochondrialGeneticCode.i}
[class] EchinodermMitochondrialGeneticCode:
>>> dna = bpp.DNA()
>>> emca = bpp.EchinodermMitochondrialCodonAlphabet(dna)
>>> seq = bpp.Sequence("seq", "AAAGCT", emca)

>>> emgc = bpp.EchinodermMitochondrialGeneticCode(dna)
>>> emgc.translate("AAA")
'N'
>>> emgc.translate(41)
7
>>> emgc.translate(seq).toString()
'NA'


{Fasta.i}
[class] Fasta:
>>> fasta = bpp.Fasta()
>>> fasta.getFormatName()
'FASTA file'
>>> fasta.getFormatDescription()
'Sequence name (preceded by >) in one line, sequence content, no comments'
>>> fasta.checkNames()
True
>>> fasta.checkNames(True)
>>> fasta.checkNames()
True
>>> fasta.checkNames(False)
>>> fasta.checkNames()
False
>>> fasta.checkNames(True)

>>> input = bpp.ifstream("data1.fas")
>>> dna = bpp.DNA()
>>> container = bpp.VectorSequenceContainer(dna)
>>> fasta.appendFromStream(input, container)

>>> fasta.write(bpp.ApplicationTools.getMessage(), container)
>>> fasta.write("output-file.fas", container)


{Genbank.i}
[class] GenBank:
>>> genbank = bpp.GenBank()
>>> genbank.getFormatName()
'GenBank file'
>>> genbank.getFormatDescription()
'Sequences following the GenBank data base format.'

>>> input = bpp.ifstream("data.gb")
>>> container = bpp.VectorSequenceContainer(dna)
>>> container.getNumberOfSequences()
0
>>> genbank.appendFromStream(input, container)
>>> container.getNumberOfSequences()
1


{GeneticCode.i}
[class] StopCodonException
>>> x = bpp.StopCodonException("stop!!!!!", "TAG")
>>> x.getCodon()
'TAG'
>>> x.what()
'StopCodonException: stop!!!!!(TAG)'

[class] GeneticCode;
>>> dna = bpp.DNA()
>>> codons = bpp.StandardCodonAlphabet(dna)
>>> code = bpp.StandardGeneticCode(dna)
>>> code.getSourceAlphabet().getAlphabetType()
'Standard codon alphabet'
>>> code.getTargetAlphabet().getAlphabetType()
'Proteic alphabet'
>>> code.translate("agt")
'S'
>>> code.translate(9)
15
>>> seq = bpp.Sequence("seq", "ACCTCG",codons)
>>> code.translate(seq).toString()
'TS'

>>> code.areSynonymous('agt','agc')
True
>>> code.areSynonymous(11,9)
True
>>> code.getSynonymous('s')
('AGC', 'AGT', 'TCA', 'TCC', 'TCG', 'TCT')
>>> code.getSynonymous(15)
(9, 11, 50, 51, 52, 53)
>>> s = bpp.Sequence("name","ACCCATGAGGAGGTAG",dna)
>>> code.getCodingSequence(s,True,True).toString()
'ATGAGGAGG'


{GranthamAAChemicalDistance.i}
[class] GranthamAAChemicalDistance:
>>> gDist = bpp.GranthamAAChemicalDistance()
>>> gDist.setSymmetric(True)
>>> gDist.isSymmetric()
True
>>> gDist.getIndex(0,1)
112.0
>>> gDist.getIndex('a','r')
112.0
>>> gDist.setSymmetric(False)
>>> gDist.getIndex(0,1)
-112.0

>>> gDist.getAlphabet().getAlphabetType()
'Proteic alphabet'
>>> gDist.clone()
<bpp.GranthamAAChemicalDistance; proxy of <Swig Object of type 'GranthamAAChemicalDistance *' at 0x...> >
>>> gDist.getIndexMatrix()
<bpp.doubleMatrix; proxy of <Swig Object of type 'Matrix< double > *' at 0x...> >


{GranthamAAPolarityIndex.i}
[class] GranthamAAPolarityIndex:
>>> gPol = bpp.GranthamAAPolarityIndex()
>>> gPol.clone()
<bpp.GranthamAAPolarityIndex; proxy of <Swig Object of type 'GranthamAAPolarityIndex *' at 0x...> >
>>> gPol.getIndex(1)
10.5
>>> gPol.getIndex('R')
10.5
>>> gPol.getIndexVector()
<bpp.doubleVector; proxy of <Swig Object of type 'std::vector< double > *' at 0x...> >
>>> gPol.getAlphabet().getAlphabetType()
'Proteic alphabet'


{GranthamAAVolumeIndex.i}
[class] GranthamAAVolumeIndex:
>>> gVol = bpp.GranthamAAVolumeIndex()
>>> gVol.clone()
<bpp.GranthamAAVolumeIndex; proxy of <Swig Object of type 'GranthamAAVolumeIndex *' at 0x...> >
>>> gVol.getIndex(2)
56.0
>>> gVol.getIndex('N')
56.0
>>> gVol.getIndexVector()
<bpp.doubleVector; proxy of <Swig Object of type 'std::vector< double > *' at 0x...> >
>>> gVol.getAlphabet().getAlphabetType()
'Proteic alphabet'


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


{InvertebrateMitochondrialCodonAlphabet.i}
[class] InvertebrateMitochondrialCodonAlphabet:
>>> import bpp
>>> dna = bpp.DNA()
>>> imca = bpp.InvertebrateMitochondrialCodonAlphabet(dna)
>>> seq = bpp.Sequence("seq", "AAAGCT", imca)
>>> imgc = bpp.InvertebrateMitochondrialGeneticCode(dna)
>>> imgc.translate("AAA")
'K'
>>> imgc.translate(41)
7
>>> imgc.translate(seq).toString()
'KA'


{IOSequence.i}
[class] (partial) IOSequence:
>>> gb = bpp.GenBank()
>>> gb.getDataType()
'Sequence container'


{IOSequenceFactory.i}
[class] IOSequenceFactory:
>>> factory = bpp.IOSequenceFactory()
>>> factory.createReader(factory.FASTA_FORMAT).getFormatName()
'FASTA file'
>>> factory.createWriter(factory.FASTA_FORMAT).getFormatName()
'FASTA file'

>>> factory.FASTA_FORMAT
'Fasta'
>>> factory.MASE_FORMAT
'Mase'
>>> factory.CLUSTAL_FORMAT
'Clustal'
>>> factory.DCSE_FORMAT
'DCSE'
>>> factory.PHYLIP_FORMAT_INTERLEAVED
'Phylip I'
>>> factory.PHYLIP_FORMAT_SEQUENTIAL
'Phylip S'
>>> factory.PAML_FORMAT_INTERLEAVED
'PAML I'
>>> factory.PAML_FORMAT_SEQUENTIAL
'PAML S'


{ISequence.i}
[class] (interface) ISequence:
>>> fasta = bpp.Fasta()
>>> dna = bpp.DNA()

>>> input = bpp.ifstream("data1.fas")
>>> container0 = fasta.read(input, dna)
>>> container0.getNumberOfSequences()
3

>>> container1 = fasta.read("data1.fas", dna)
>>> container1.getNumberOfSequences()
3

[class] (interface) ISequence2:
>>> dcse = bpp.DCSE()
>>> rna = bpp.RNA()
>>> aseqs = dcse.read("data.bpp-ali", rna)
>>> aseqs.getNumberOfSequences()
4

>>> dcse = bpp.DCSE()
>>> rna = bpp.RNA()
>>> stream = bpp.ifstream("data.bpp-ali")
>>> aseqs1 = dcse.read(stream, rna)
>>> aseqs1.getNumberOfSequences()
4

{KleinAANetChargeIndex.i}
[class] KleinAANetChargeIndex
>>> klein = bpp.KleinAANetChargeIndex()
>>> klein.getIndex(0)
0.0
>>> klein.getIndex(1)
1.0
>>> klein.getIndex('s')
0.0
>>> klein.getIndexVector()
<bpp.doubleVector; proxy of <Swig Object of type 'std::vector< double > *' at 0x...> >
>>> klein.getAlphabet().getAlphabetType()
'Proteic alphabet'
>>> klein.clone()
<bpp.KleinAANetChargeIndex; proxy of <Swig Object of type 'KleinAANetChargeIndex *' at 0x...> >


{Mase.i}
[class] Mase:
>>> mase = bpp.Mase()
>>> mase.getFormatName()
'MASE file'
>>> mase.getFormatDescription()
'Optional file comments (preceeded by ;;), sequence comments (preceeded by ;), sequence name, sequence'
>>> input = bpp.ifstream("data1.mase")
>>> dna = bpp.DNA()
>>> container = bpp.VectorSequenceContainer(dna)
>>> mase.appendFromStream(input, container)

>>> mase.write(bpp.ApplicationTools.getMessage(), container)
>>> mase.write("output.mase", container)
>>> mase.checkNames()
True
>>> mase.checkNames(False)


{MiyataAAChemicalDistance.i}
[class] MiyataAAChemicalDistance.i:
>>> miyata = bpp.MiyataAAChemicalDistance()
>>> miyata.setSymmetric(True)
>>> miyata.isSymmetric()
True
>>> miyata.getIndex(0,1)
2.9...
>>> miyata.getIndex('a','r')
2.9...
>>> miyata.setSymmetric(False)
>>> miyata.getIndex(0,1)
-2.9...
>>> miyata.getAlphabet().getAlphabetType()
'Proteic alphabet'
>>> miyata.clone()
<bpp.MiyataAAChemicalDistance; proxy of <Swig Object of type 'MiyataAAChemicalDistance *' at 0x...> >


{NucleicAcidsReplication.i}
[class] NucleicAcidsReplication:
>>> dna = bpp.DNA()
>>> rna = bpp.RNA()
>>> nar = bpp.NucleicAcidsReplication(dna,rna)
>>> dnaSeq = bpp.Sequence("dna-seq", "ACGTCC",dna)

>>> nar.getSourceAlphabet().getAlphabetType()
'DNA alphabet'
>>> nar.getTargetAlphabet().getAlphabetType()
'RNA alphabet'

>>> nar.translate("A")
'U'
>>> nar.translate(1)
2
>>> newSeq = nar.translate(dnaSeq)
>>> newSeq.toString()
'UGCAGG'

>>> nar.reverse("U")
'A'
>>> nar.reverse(3)
0
>>> nar.reverse(newSeq).toString()
'ACGTCC'


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


{OrderedSequenceContainer.i}
[class] (interface) OrderedSequenceContainer:
>>> dna = bpp.DNA()
>>> site1 = bpp.Site(["A","G"], dna, 1)
>>> site2 = bpp.Site(["A","A"], dna, 2)
>>> site3 = bpp.Site(["C","C"], dna, 3)
>>> vsc = bpp.VectorSiteContainer([site1,site2,site3],dna)

>>> vsc.getContent(0)
(0, 0, 1)
>>> vsc.toString(0)
'AAC'
>>> vsc.getName(0)
'Seq_0'
>>> vsc.getSequencesNames()
('Seq_0', 'Seq_1')
>>> vsc.setComments(0, ["yup--comments", "more comments"])
>>> vsc.getComments(0)
('yup--comments', 'more comments')
>>> vsc.getSequencePosition("Seq_0")
0

>>> bpp.intp.frompointer(vsc.valueAt(0,1)).value()
0
>>> bpp.intp.frompointer(vsc.valueAt("Seq_0",1)).value()
0
>>> bpp.intp.frompointer(vsc(0,1)).value()
0
>>> bpp.intp.frompointer(vsc("Seq_0",1)).value()
0


{OSequence.i}
[class] (interface) OSequence:
>>> fasta = bpp.Fasta()
>>> input = bpp.ifstream("data1.fas")
>>> dna = bpp.DNA()
>>> container = bpp.VectorSequenceContainer(dna)
>>> fasta.appendFromStream(input, container)

>>> fasta.write(bpp.ApplicationTools.getMessage(), container)
>>> fasta.write("output-file.fas", container)


{PhredPhd.i}
[class] PhredPhd:
>>> phredphd = bpp.PhredPhd()
>>> phredphd.getFormatName()
'phd file'
>>> phredphd.getFormatDescription()
'Sequences following the phd format as describe in the phred documentation.'

>>> input = bpp.ifstream("data.phd")
>>> dna = bpp.DNA()
>>> container = bpp.VectorSequenceContainer(dna)
>>> phredphd.appendFromStream(input,container)
>>> container.getNumberOfSequences()
1
>>> container.getSequencesNames()
('ML4924R',)


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


{SequenceApplicationTools.i}
[class] SequenceApplicationTools:
>>> dna = bpp.DNA()

>>> options = bpp.strMap()
>>> options["alphabet"] = "RNA"
>>> bpp.SequenceApplicationTools.getAlphabet(options).getAlphabetType()
'RNA alphabet'

>>> options = bpp.strMap()
>>> options["sequence.file"] = "data1.fas"
>>> options["sequence.format"] = "Fasta"
>>> seqs = bpp.SequenceApplicationTools.getSequenceContainer(dna, options)
>>> seqs.getSequencesNames()
('seq1', 'seq2', 'seq3')
>>> seqs.toString('seq1')
'ATGCCGTGGTCCCGT'
>>> seqs.toString('seq2')
'TTTGGCGACCGTAACCCGT'
>>> seqs.toString('seq3')
'GAGACTAGCTGA'

>>> options = bpp.strMap()
>>> options["sequence.file"] = "data2.fas"
>>> options["sequence.format"] = "Fasta"
>>> sites = bpp.SequenceApplicationTools.getSiteContainer(dna, options)
>>> sites.getPositions()
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19)
>>> sites.getSite(0).toString()
'ATG'

>>> options = bpp.strMap()
>>> options["sequence.sites_to_use"] = "all"
>>> options["sequence.max_gap_allowed"] = "100%"
>>> sites1 = bpp.SequenceApplicationTools.getSitesToAnalyse(sites, options)
>>> sites1.getPositions()
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19)
>>> options["sequence.max_gap_allowed"] = "1"
>>> sites1 = bpp.SequenceApplicationTools.getSitesToAnalyse(sites, options)
>>> sites1.getPositions()
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)

>>> options = bpp.strMap()
>>> options["sequence.sites_to_use"] = "nogap"
>>> sites1 = bpp.SequenceApplicationTools.getSitesToAnalyse(sites, options)
>>> sites1.getPositions()
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)

>>> options = bpp.strMap()
>>> options["sequence.sites_to_use"] = "complete"
>>> sites1 = bpp.SequenceApplicationTools.getSitesToAnalyse(sites, options)
>>> sites1.getPositions()
(1, 2, 3, 4, 7, 8, 9, 10, 11, 12)

>>> options = bpp.strMap()
>>> options["output.sequence.file"] = "output.fas"
>>> options["output.sequence.format"] = "Fasta"
>>> options["output.sequence.length"] = "100"
>>> bpp.SequenceApplicationTools.writeSequenceFile(seqs, options)

>>> bpp.SequenceApplicationTools.printInputAlignmentHelp()
>>> bpp.SequenceApplicationTools.printOutputSequenceHelp()


{SequenceContainer.i}
[class] (interface) SequenceContainer:
>>> dna = bpp.DNA()
>>> seq0 =  bpp.Sequence("Sequence_0", "AGGTCT", dna)
>>> seq1 =  bpp.Sequence("Sequence_1", "TGTCAT", dna)
>>> vsc = bpp.VectorSequenceContainer([seq0,seq1],dna)

>>> vsc.getAlphabet().getAlphabetType()
'DNA alphabet'
>>> vsc.setComments(0, ["this is a comment", "so is this"])
>>> vsc.getComments(0)
('this is a comment', 'so is this')
>>> vsc.setGeneralComments(["well hello there"])
>>> vsc.getGeneralComments()
('well hello there',)
>>> vsc.deleteGeneralComments()
>>> vsc.getGeneralComments()
()


{SequenceContainerExceptions.i}
[class] SequenceNotFoundException:
>>> x = bpp.SequenceNotFoundException("can't find it!", "AGCT")
>>> x.getSequenceId()
'AGCT'
>>> x.what()
"SequenceNotFoundException: can't find it!(AGCT)"

[class] EmptyContainerException:
>>> dna = bpp.DNA()
>>> vsc = bpp.VectorSiteContainer(3,dna)
>>> x = bpp.EmptyContainerException("container's empty", vsc)
>>> x.getContainer()
<bpp.SequenceContainer; proxy of <Swig Object of type 'SequenceContainer *' at 0x...> >
>>> x.what()
"EmptyContainerException: container's empty"


{SequenceExceptions.i}
[class] SequenceException:
>>> import bpp
>>> dna = bpp.DNA()
>>> seq = bpp.Sequence("test", "AGGTCT", dna)

>>> x = bpp.SequenceException("bad sequence!", seq)
>>> x.what()
'SequenceException: bad sequence!(test)'
>>> x.getSequence()
<bpp.Sequence; proxy of <Swig Object of type 'Sequence *' at 0x...> >

[class] EmptySequenceException:
>>> x = bpp.EmptySequenceException("it's empty!", seq)
>>> x.what()
"SequenceException: EmptySequenceException: it's empty!(test)"
>>> x.getSequence()
<bpp.Sequence; proxy of <Swig Object of type 'Sequence *' at 0x...> >

[class] SequenceWithGapException:
>>> x = bpp.SequenceWithGapException("I hate gaps!", seq)
>>> x.what()
'SequenceException: SequenceWithGapException: I hate gaps!(test)'
>>> x.getSequence()
<bpp.Sequence; proxy of <Swig Object of type 'Sequence *' at 0x...> >

[class] SequenceNotAlignedException:
>>> x = bpp.SequenceNotAlignedException("I hate not being aligned!", seq)
>>> x.what()
'SequenceException: SequenceNotAlignedException: I hate not being aligned!(test)'
>>> x.getSequence()
<bpp.Sequence; proxy of <Swig Object of type 'Sequence *' at 0x...> >


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
>>> seq1 = bpp.Sequence("test", "GGG", dna)
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
>>> bpp.SequenceTools.getNumberOfSites(bpp.Sequence("test", "AH--TT", dna))
4
>>> bpp.SequenceTools.removeGaps(seqA).toString()
'AGTT'

>>> bpp.SequenceTools.bowkerTest(seq,seqA)
<bpp.BowkerTest; proxy of <Swig Object of type 'BowkerTest *' at 0x...> >

>>> hetero = bpp.Sequence("heterozygous", "ATTCGGGKWTATRYRM", dna)
>>> haplo = bpp.Sequence("haplotype", "ATTCGGGTATATGCAA", dna)
>>> bpp.SequenceTools.subtractHaplotype(hetero, haplo, "result").toString()
'ATTCGGGNNTATNNNN'
>>> bpp.SequenceTools.bowkerTest(seq,seqA)
<bpp.BowkerTest; proxy of <Swig Object of type 'BowkerTest *' at 0x...> >


{SimpleIndexDistance.i}
[class] <T>SimpleIndexDistance
>>> klein = bpp.KleinAANetChargeIndex()
>>> klein2 = bpp.doubleSimpleIndexDistance(klein)

>>> klein2.setSymmetric(True)
>>> klein2.isSymmetric()
True
>>> klein2.getIndex(0,1)
1.0
>>> klein2.getIndex(0,0)
0.0
>>> klein2.getIndex('a','r')
1.0
>>> klein2.getIndex('a','a')
0.0
>>> klein2.setSymmetric(False)
>>> klein2.getIndex(0,1)
1.0
>>> klein2.getIndex(1,0)
-1.0

>>> klein2.getAlphabet().getAlphabetType()
'Proteic alphabet'
>>> klein2.getIndexMatrix()
<bpp.doubleMatrix; proxy of <Swig Object of type 'Matrix< double > *' at 0x...> >
>>> klein2.clone()
<bpp.Clonable; proxy of <Swig Object of type 'Clonable *' at 0x...> >
>>> klein2.getAlphabetIndex1()
<bpp.doubleAlphabetIndex1; proxy of <Swig Object of type 'AlphabetIndex1< double > *' at 0x...> >


{SimpleScore.i}
[class] SimpleScore:
>>> alpha = bpp.DefaultAlphabet()
>>> ss = bpp.SimpleScore(alpha, 2.0, -1.0)
>>> ss.clone()
<bpp.SimpleScore; proxy of <Swig Object of type 'SimpleScore *' at 0x...> >
>>> ss.getIndex(0,0)
2.0
>>> ss.getIndex(0,1)
-1.0
>>> ss.getIndex('a','f')
-1.0
>>> ss.getIndex('z','z')
2.0
>>> ss.getAlphabet().getAlphabetType()
'Default alphabet'
>>> ss.getIndexMatrix()
<bpp.doubleMatrix; proxy of <Swig Object of type 'Matrix< double > *' at 0x...> >


{Site.i}
[class] Site:
>>> dna = bpp.DNA()
>>> bpp.Site("acg",dna)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> bpp.Site("acg",dna,52)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> bpp.Site(['a','c','g'],dna)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> bpp.Site(['a','c','g'],dna,52)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> bpp.intVecSite([0,1,2],dna)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> bpp.intVecSite([0,1,2],dna,52)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >

>>> site = bpp.Site("acg",dna,52)
>>> site.getPosition()
52
>>> site.setPosition(31)
>>> site.toString()
'ACG'

>>> bpp.Site(site)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> site.clone()
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >


{SiteContainer.i}
[class] (interface) SiteContainer:
>>> dna = bpp.DNA()
>>> site1 = bpp.Site(["A","G"], dna, 1)
>>> site2 = bpp.Site(["A","A"], dna, 2)
>>> site3 = bpp.Site(["C","C"], dna, 3)
>>> site4 = bpp.Site(["G","G"], dna, 4)
>>> site5 = bpp.Site(["T","T"], dna, 5)
>>> sites = bpp.VectorSiteContainer([site1,site2,site3,site4],dna)

>>> sites.getSite(0).toString()
'AG'
>>> sites.setSite(0, site5)
>>> sites.getSite(0).toString()
'TT'
>>> sites.removeSite(1)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> sites.deleteSite(1)
>>> sites.getNumberOfSites()
2
>>> sites.getSitePositions()
(5, 4)
>>> sites.reindexSites()
>>> sites.getSitePositions()
(1, 2)


{SiteContainerExceptions.i}
[class] SiteNotFoundException
>>> x = bpp.SiteNotFoundException("can't find!", "xxx")
>>> x.what()
"SequenceNotFoundException: can't find!(xxx)"
>>> x.getSiteId()
'xxx'


{SiteExceptions.i}
[class] SiteException
>>> dna = bpp.DNA()
>>> site = bpp.Site("acg",dna,47)

>>> x = bpp.SiteException("bad site!", site)
>>> x.what()
'bad site!(47)'
>>> x.getSite().toString()
'ACG'

[class] EmptySiteException
>>> site = bpp.Site("",dna,47)
>>> x = bpp.EmptySiteException("empty site!", site)
>>> x.what()
'empty site!(47)'
>>> x.getSite().toString()
''

[class] SiteWithGapException
>>> site = bpp.Site("AG-TC",dna,47)
>>> x = bpp.SiteWithGapException("gappy site!", site)
>>> x.what()
'gappy site!(47)'
>>> x.getSite().toString()
'AG-TC'


{SiteIterator.i}
[class] (interface) SiteIterator:
[class] (partial) AbstractSiteIterator:
[class] SimpleSiteIterator:
>>> dna = bpp.DNA()
>>> site1 = bpp.Site(["A","-"], dna, 1)
>>> site2 = bpp.Site(["A","N"], dna, 2)
>>> site3 = bpp.Site(["A","A"], dna, 3)
>>> sites = bpp.VectorSiteContainer([site1,site2,site3],dna)

>>> it = bpp.SimpleSiteIterator(sites)
>>> it.hasMoreSites()
True
>>> it.nextSite().toString()
'A-'
>>> it.nextSite().toString()
'AN'
>>> it.nextSite().toString()
'AA'
>>> it.hasMoreSites()
False

[class] NoGapsSiteIterator:
>>> it = bpp.NoGapSiteIterator(sites)
>>> it.hasMoreSites()
True
>>> it.nextSite().toString()
'AN'
>>> it.nextSiteWithoutGapPosition(0)
1
>>> it.previousSiteWithoutGapPosition(1)
-1

[class] CompleteSiteIterator:
>>> it = bpp.CompleteSiteIterator(sites)
>>> it.hasMoreSites()
True
>>> it.nextSite().toString()
'AA'
>>> it.nextCompleteSitePosition(0)
2
>>> it.previousCompleteSitePosition(2)
-1
>>> it.nextCompleteSitePosition(2)
3


{SiteTools.i}
[class] SiteTools:
>>> dna = bpp.DNA()
>>> site = bpp.Site("AG-TCR",dna,47)
>>> site1 = bpp.Site("AGGTCA",dna,47)
>>> bpp.SiteTools.hasGap(site)
True
>>> bpp.SiteTools.isGapOnly(site)
False
>>> bpp.SiteTools.isGapOrUnresolvedOnly(site)
False
>>> bpp.SiteTools.hasUnknown(site)
False
>>> bpp.SiteTools.isComplete(site1)
True
>>> bpp.SiteTools.isConstant(site)
False
>>> bpp.SiteTools.areSitesIdentical(site,site1)
False

>>> bpp.SiteTools.variabilityShannon(site, True)
1.2904003369692969
>>> bpp.SiteTools.variabilityFactorial(site)
4.7874917427820458
>>> bpp.SiteTools.mutualInformation(site,site1,True)
1.1412247897216785
>>> bpp.SiteTools.heterozygosity(site)
0.83333333333333337
>>> bpp.SiteTools.getNumberOfDistinctCharacters(site)
6
>>> bpp.SiteTools.getNumberOfDistinctCharacters(site1)
4
>>> bpp.SiteTools.hasSingleton(site)
True
>>> bpp.SiteTools.isParsimonyInformativeSite(site)
False
>>> bpp.SiteTools.isTriplet(site)
True


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


{StandardGeneticCode.i}
[class] StandardGeneticCode;
>>> dna = bpp.DNA()
>>> codons = bpp.StandardCodonAlphabet(dna)
>>> code = bpp.StandardGeneticCode(dna)
>>> code.getSourceAlphabet().getAlphabetType()
'Standard codon alphabet'
>>> code.getTargetAlphabet().getAlphabetType()
'Proteic alphabet'
>>> code.translate("agt")
'S'
>>> code.translate(9)
15
>>> seq = bpp.Sequence("seq", "ACCTCG",codons)
>>> code.translate(seq).toString()
'TS'


{StringSequenceTools.i}
[class] StringSequenceTools:
>>> bpp.StringSequenceTools.subseq("abcdefghij", 3, 5)
'def'
>>> bpp.StringSequenceTools.setToSizeR("abc", 6)
'abc---'
>>> bpp.StringSequenceTools.setToSizeL("abc", 6)
'---abc'
>>> bpp.StringSequenceTools.deleteChar("xahaxeaxlalxaoa", 'ax')
'hello'
>>> bpp.strp.frompointer(bpp.StringSequenceTools.reverse("olleh")).value()
'hello'
>>> bpp.strp.frompointer(bpp.StringSequenceTools.complement("ACTC")).value()
'TGAG'
>>> bpp.StringSequenceTools.getGCcontent("AGCGCATCGACTTCCG",2,8)
0.625
>>> dna = bpp.DNA()
>>> bpp.StringSequenceTools.codeSequence("AGCTCTT", dna)
(0, 2, 1, 3, 1, 3, 3)
>>> bpp.StringSequenceTools.decodeSequence([0,2,1,3,1,3,3], dna)
'AGCTCTT'
>>> bpp.StringSequenceTools.getAlphabetFromSequence("asccgcq").getAlphabetType() 
'Proteic alphabet'


{SymbolList.i}
[class] SymbolList:
>>> bpp.SymbolList(dna)
<bpp.SymbolList; proxy of <Swig Object of type 'SymbolList *' at 0x...> >
>>> bpp.intVecSymbolList([1,2],dna)
<bpp.SymbolList; proxy of <Swig Object of type 'SymbolList *' at 0x...> >

>>> symlist = bpp.SymbolList(["a","c"],dna)
>>> symlist.clone()
<bpp.SymbolList; proxy of <Swig Object of type 'SymbolList *' at 0x...> >
>>> bpp.SymbolList(symlist)
<bpp.SymbolList; proxy of <Swig Object of type 'SymbolList *' at 0x...> >

>>> symlist.getAlphabet().getAlphabetType()
'DNA alphabet'
>>> symlist.size()
2
>>> symlist.toString()
'AC'
>>> symlist.getContent()
(0, 1)
>>> symlist.intVecSetContent([1,2,5])
>>> symlist.toString()
'CGR'
>>> symlist.setContent(["a","m"])
>>> symlist.toString()
'AM'
>>> symlist.addElement("c")
>>> symlist.toString()
'AMC'
>>> symlist.addElement(3)
>>> symlist.toString()
'AMCT'
>>> symlist.addElement(1,"G")
>>> symlist.toString()
'AGMCT'
>>> symlist.addElement(0,0)
>>> symlist.toString()
'AAGMCT'
>>> symlist.setElement(1,"g")
>>> symlist.toString()
'AGGMCT'
>>> symlist.setElement(0,5)
>>> symlist.toString()
'RGGMCT'
>>> symlist.deleteElement(3)
>>> symlist.toString()
'RGGCT'
>>> symlist.getValue(1)
2


{SymbolListTools.i}
[class] SymbolListTools:
>>> dna = bpp.DNA()
>>> symlist = bpp.SymbolList("accttacgn",dna)
>>> symlist1 = bpp.SymbolList("catcatcat",dna)
>>> counts = bpp.intUintMap()
>>> bpp.SymbolListTools.getCounts(symlist,counts)
>>> counts[0],counts[1],counts[2],counts[3]
(2, 3, 1, 2)

>>> counts = bpp.intDoubleMap()
>>> bpp.SymbolListTools.getCounts(symlist,counts,False)
>>> counts[0],counts[1],counts[2],counts[3]
(2.0, 3.0, 1.0, 2.0)

>>> bpp.SymbolListTools.getCounts(symlist,counts,True)
>>> counts[0],counts[1],counts[2],counts[3]
(4.25, 6.25, 2.25, 4.25)

>>> counts = bpp.intIuiMapMap()
>>> bpp.SymbolListTools.getCounts(symlist,symlist1,counts)
>>> counts[1].keys()
[0, 1, 3]
>>> counts[1][1], counts[1][3]
(1, 1)

>>> counts = bpp.intIdMapMap()
>>> bpp.SymbolListTools.getCounts(symlist,symlist1,counts,True)
>>> counts[1].keys()
[0, 1, 3]
>>> counts[0][1],counts[0][3]
(1.0, 1.25)

>>> freqs = bpp.intDoubleMap()
>>> bpp.SymbolListTools.getFrequencies(symlist,freqs,False)
>>> freqs[0],freqs[1],freqs[2],freqs[3]
(0.222..., 0.333..., 0.111..., 0.222...)

>>> freqs = bpp.intIdMapMap()
>>> bpp.SymbolListTools.getFrequencies(symlist,symlist1,freqs,False)
>>> freqs[1].keys()
[0, 1, 3]
>>> freqs[1][1],freqs[1][3]
(0.012345679012345678, 0.012345679012345678)

>>> bpp.SymbolListTools.getGCContent(symlist)
0.5
>>> bpp.SymbolListTools.getNumberOfDistinctPositions(symlist,symlist1)
8

>>> bpp.SymbolListTools.changeUnresolvedCharactersToGaps(symlist)
>>> symlist.toString()
'ACCTTACG-'
>>> bpp.SymbolListTools.changeUnresolvedCharactersToGaps(symlist1)
>>> bpp.SymbolListTools.getNumberOfPositionsWithoutGap(symlist,symlist1)
8

>>> bpp.SymbolListTools.changeGapsToUnknownCharacters(symlist)
>>> symlist.toString()
'ACCTTACGN'


{Translator.i}
[class] interface Translator:
[class] partial AbstractTranslator:
>>> dna = bpp.DNA()
>>> codons = bpp.StandardCodonAlphabet(dna)
>>> code = bpp.StandardGeneticCode(dna)
>>> code.getSourceAlphabet().getAlphabetType()
'Standard codon alphabet'
>>> code.getTargetAlphabet().getAlphabetType()
'Proteic alphabet'
>>> code.translate("agt")
'S'
>>> code.translate(9)
15
>>> seq = bpp.Sequence("seq", "ACCTCG",codons)
>>> code.translate(seq).toString()
'TS'

[class] interface ReverseTranslator:
[class] partial AbstractReverseTranslator:
>>> d2r = bpp.DNAToRNA()
>>> dna = bpp.DNA()
>>> rna = bpp.RNA()
>>> dSeq = bpp.Sequence("dna-seq", "ACGT",dna)

>>> d2r.getSourceAlphabet().getAlphabetType()
'DNA alphabet'
>>> d2r.getTargetAlphabet().getAlphabetType()
'RNA alphabet'

>>> rSeq = d2r.translate(dSeq)
>>> rSeq.toString()
'ACGU'
>>> d2r.reverse(2)
2
>>> d2r.reverse("U")
'T'
>>> d2r.reverse(rSeq).toString()
'ACGT'


{VectorSequenceContainer.i}
[class] VectorSequenceContainer:
>>> dna = bpp.DNA()
>>> seq0 =  bpp.Sequence("Sequence_0", "AGGTCT", dna)
>>> seq1 =  bpp.Sequence("Sequence_1", "TGTCAT", dna)
>>> vsc = bpp.VectorSequenceContainer(dna)
>>> vsc.getNumberOfSequences()
0
>>> vsc.addSequence(seq0)
>>> vsc.getNumberOfSequences()
1
>>> vsc.addSequence(seq1,0)
>>> vsc.getNumberOfSequences()
2
>>> vsc.getSequencesNames()
('Sequence_1', 'Sequence_0')
>>> vsc.getSequence(0).getName()
'Sequence_1'
>>> vsc.getSequence("Sequence_0").getName()
'Sequence_0'
>>> vsc.getSequencePosition("Sequence_0")
1
>>> vsc.removeSequence(0).getName()
'Sequence_1'
>>> vsc.removeSequence("Sequence_0").getName()
'Sequence_0'

>>> vsc = bpp.VectorSequenceContainer([seq0,seq1],dna)
>>> vsc.setSequencesNames(["Seq-A","Seq-B"])
>>> vsc.getSequencesNames()
('Seq-A', 'Seq-B')
>>> vsc.valueAt("Seq-A",1)
<Swig Object of type 'int *' at 0x...>
>>> bpp.intp.frompointer(vsc.valueAt("Seq-A",1)).value()
2
>>> bpp.intp.frompointer(vsc("Seq-A",1)).value()
2
>>> bpp.intp.frompointer(vsc.valueAt(0,1)).value()
2
>>> bpp.intp.frompointer(vsc(0,1)).value()
2
>>> empty = vsc.createEmptyContainer()
>>> bpp.VectorSequenceContainer(empty).getNumberOfSequences()
0

>>> vsc.setComments(0, "this is a comment")
>>> vsc.setComments("Seq-B", "this is a comment too")
>>> vscC = bpp.VectorSequenceContainer(vsc)
>>> vscC.deleteSequence(1)
>>> vscC.deleteSequence("Seq-A")
>>> vscC.getNumberOfSequences()
0
>>> vsc.setSequence(0, seq0)
>>> vsc.setSequence("Seq-B", seq1)
>>> vsc.getSequencesNames()
('Sequence_0', 'Sequence_1')
>>> vsc.clear()
>>> vsc.getNumberOfSequences()
0
>>> vsc.clone()
<bpp.Clonable; proxy of <Swig Object of type 'Clonable *' at 0x...> >


{VectorSiteContainer.i}
[class] VectorSiteContainer:
>>> dna = bpp.DNA()
>>> site1 = bpp.Site(["A","G"], dna, 1)
>>> site2 = bpp.Site(["A","A"], dna, 2)
>>> site3 = bpp.Site(["C","C"], dna, 3)
>>> site4 = bpp.Site(["G","G"], dna, 4)
>>> site5 = bpp.Site(["T","T"], dna, 5)
>>> seqX = bpp.Sequence("seq-X", "AAA", dna)
>>> seqY = bpp.Sequence("seq-Y", "CCC", dna)
>>> vsc = bpp.VectorSiteContainer([site1,site3,site5],dna)

>>> vsc.getNumberOfSites()
3
>>> vsc.getSite(0).toString()
'AG'
>>> vsc.getNumberOfSequences()
2
>>> vsc.getSequencesNames()
('Seq_0', 'Seq_1')

>>> vsc.getPositions()
(1, 3, 5)
>>> vsc.getSitePositions()
(1, 3, 5)

>>> vsc.getSequence(0).toString()
'ACT'
>>> vsc.getSequence("Seq_1").toString()
'GCT'
>>> vsc.getSequencePosition("Seq_1")
1
>>> clone = vsc.clone()
>>> clone.setSequencesNames(["seq-A","seq-B"])
>>> clone.removeSequence("seq-A")
<bpp.Sequence; proxy of <Swig Object of type 'Sequence *' at 0x...> >
>>> clone.removeSequence(0)
<bpp.Sequence; proxy of <Swig Object of type 'Sequence *' at 0x...> >
>>> clone.addSequence(seqY)
>>> clone.addSequence(seqX,0)
>>> clone.getSite(0).toString()
'AC'
>>> clone.setComments(0, ["more comments"])
>>> clone.getComments(0)
('more comments',)

>>> clone.setSequence("seq-X", seqY,False)
>>> clone.setSequence(1, seqX, True)
>>> clone.getSequencesNames()
('seq-Y', 'seq-X')
>>> clone.deleteSequence("seq-Y")
>>> clone.deleteSequence(0)
>>> clone.getNumberOfSequences()
0
>>> clone.getNumberOfSites()
3

>>> vsc.setSite(1, site2)
>>> vsc.addSite(site3)
>>> vsc.addSite(site4, 3)
>>> vsc.getPositions()
(1, 2, 5, 4, 3)
>>> vsc.reindexSites()
>>> vsc.getPositions()
(1, 2, 3, 4, 5)
>>> vsc.getSequence(0).toString()
'AATGC'
>>> vsc.removeSite(3)
<bpp.Site; proxy of <Swig Object of type 'Site *' at 0x...> >
>>> vsc.deleteSite(3)

>>> bpp.intp.frompointer(vsc.valueAt(0,1)).value()
0
>>> bpp.intp.frompointer(vsc.valueAt("Seq_0",1)).value()
0
>>> bpp.intp.frompointer(vsc(0,1)).value()
0
>>> bpp.intp.frompointer(vsc("Seq_0",1)).value()
0

>>> bpp.VectorSiteContainer(vsc.createEmptyContainer()).getNumberOfSequences()
0
>>> bpp.VectorSiteContainer(500,dna).getNumberOfSequences()
500
>>> bpp.VectorSiteContainer(dna).getNumberOfSequences()
0
>>> bpp.VectorSiteContainer(["a","b"],dna).getNumberOfSequences()
2


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


{VertebrateMitochondrialCodonAlphabet.i}
[class] VertebrateMitochondrialCodonAlphabet:

>>> import bpp
>>> rna = bpp.RNA()
>>> vmca = bpp.VertebrateMitochondrialCodonAlphabet(rna)
>>> seq = bpp.Sequence("seq", "AAAGCU", vmca)
>>> vmgc = bpp.VertebrateMitochondrialGeneticCode(rna)
>>> vmgc.translate("AAA")
'K'
>>> vmgc.translate(41)
7
>>> vmgc.translate(seq).toString()
'KA'

"""


import doctest
import bpp
doctest.testmod(optionflags = 8)
