"""

{AlleleInfo.i}
[class] (interface) AlleleInfo:
>>> bai = bpp.BasicAlleleInfo("Nifty Allele")
>>> bai.setId("Niftier Allele")
>>> bai.getId()
'Niftier Allele'


{BasicAlleleInfo.i}
[class] BasicAlleleInfo:
>>> bai = bpp.BasicAlleleInfo("Nifty Allele")
>>> bai1 = bpp.BasicAlleleInfo(bai)
>>> bai==bai1
True
>>> bai1.setId("Niftier Allele")
>>> bai1.getId()
'Niftier Allele'
>>> bai!=bai1
True
>>> bai.clone()
<bpp.Clonable; proxy of <Swig Object of type 'Clonable *' at 0x...> >


{BiAlleleMonolocusGenotype.i}
[class] BiAlleleMonolocusGenotype:
>>> genotype = bpp.BiAlleleMonolocusGenotype(61,63)
>>> genotype = bpp.BiAlleleMonolocusGenotype([61,63])
>>> genotype1 = bpp.BiAlleleMonolocusGenotype(genotype)
>>> genotype.getAlleleIndex()
(61, 63)
>>> genotype.getFirstAlleleIndex()
61
>>> genotype.getSecondAlleleIndex()
63
>>> genotype == genotype1
True
>>> genotype.isHomozygous()
False
>>> genotype = bpp.BiAlleleMonolocusGenotype([61,61])
>>> genotype.isHomozygous()
True
>>> genotype.clone()
<bpp.Clonable; proxy of <Swig Object of type 'Clonable *' at 0x...> >


{Coord.i}
[class] Coord<T>:
>>> a = bpp.intCoord(1,2)
>>> a.getX()
1
>>> a.getY()
2
>>> b = a.clone()
>>> a
<bpp.intCoord; proxy of <Swig Object of type 'Coord< int > *' at 0x...> >
>>> b
<bpp.intCoord; proxy of <Swig Object of type 'Coord< int > *' at 0x...> >
>>> a==b
True
>>> b.setX(3)
>>> b.setY(4)
>>> a==b
False
>>> a!=b
True
>>> a.hasSameCoordsAs(b)
False

>>> d = bpp.doubleCoord(3,4)
>>> d.getX()
3.0

{CoordsTools.i}
[class] CoordsTools<t>
>>> a = bpp.doubleCoord(1,2)
>>> b = bpp.doubleCoord(3,4)
>>> bpp.doubleCoordsTools.getDistanceBetween(a,b)
2.8284271247461903


{Date.i}
[class] Date:
>>> d0 = bpp.Date()
>>> d1 = bpp.Date(19,3,2007)
>>> d2 = bpp.Date(d1)

>>> d0.getDateStr()
'01012000'
>>> d0.getDate()
<bpp.Date; proxy of <Swig Object of type 'Date *' at 0x...> >

>>> d1.getYear()
2007
>>> d1.getMonth()
3
>>> d1.getDay()
19

>>> d0.setYear(2006)
>>> d0.setMonth(3)
>>> d0.setDay(19)
>>> d1==d2
True
>>> d0<d1
True
>>> d0<=d1
True
>>> d0>d1
False
>>> d0>=d1
False
>>> d0!=d1
True


{GeneralExceptions.i}
[class] BadIdentifierException:
>>> x = bpp.BadIdentifierException("Bad ID'er!", "THX1138")
>>> x.what()
"BadIdentifierException: Bad ID'er!(THX1138)"
>>> x.getIdentifier()
'THX1138'
>>> x = bpp.BadIdentifierException("Bad ID'er!", 1138)
>>> x.what()
"BadIdentifierException: Bad ID'er!(1138)"
>>> x.getIdentifier()
'1138'

[class] LocusNotFoundException:
>>> x = bpp.LocusNotFoundException("Can't find Locus!", "L61")
>>> x.what()
"BadIdentifierException: LocusNotFoundException: Can't find Locus!(L61)(L61)"
>>> x.getIdentifier()
'L61'
>>> x = bpp.LocusNotFoundException("Can't find Locus!", 61)
>>> x.what()
"BadIdentifierException: LocusNotFoundException: Can't find Locus!(61)(61)"
>>> x.getIdentifier()
'61'

[class] AlleleNotFoundException:
>>> x = bpp.AlleleNotFoundException("Can't find allele!", "A666")
>>> x.what()
"BadIdentifierException: AlleleNotFoundException: Can't find allele!(A666)(A666)"
>>> x.getIdentifier()
'A666'
>>> x = bpp.AlleleNotFoundException("Can't find allele!", 666)
>>> x.what()
"BadIdentifierException: AlleleNotFoundException: Can't find allele!(666)(666)"
>>> x.getIdentifier()
'666'

[class] LocalityNotFoundException:
>>> x = bpp.LocalityNotFoundException("Can't find locality!", "Nirvana21")
>>> x.what()
"BadIdentifierException: LocalityNotFoundException: Can't find locality!(Nirvana21)(Nirvana21)"
>>> x.getIdentifier()
'Nirvana21'
>>> x = bpp.LocalityNotFoundException("Can't find locality!", 21)
>>> x.what()
"BadIdentifierException: LocalityNotFoundException: Can't find locality!(21)(21)"
>>> x.getIdentifier()
'21'

[class] IndividualNotFoundException:
>>> x = bpp.IndividualNotFoundException("Can't find individual!", "Waldo")
>>> x.what()
"BadIdentifierException: IndividualNotFoundException: Can't find individual!(Waldo)(Waldo)"
>>> x.getIdentifier()
'Waldo'
>>> x = bpp.IndividualNotFoundException("Can't find individual!", 69)
>>> x.what()
"BadIdentifierException: IndividualNotFoundException: Can't find individual!(69)(69)"
>>> x.getIdentifier()
'69'

[class] GroupNotFoundException:
>>> x = bpp.GroupNotFoundException("Can't find group!", "group35")
>>> x.what()
"BadIdentifierException: GroupNotFoundException: Can't find group!(group35)(group35)"
>>> x.getIdentifier()
'group35'
>>> x = bpp.GroupNotFoundException("Can't find group!", 35)
>>> x.what()
"BadIdentifierException: GroupNotFoundException: Can't find group!(35)(35)"
>>> x.getIdentifier()
'35'


{Locality.i}
[class] Locality<T>:
>>> l0 = bpp.intLocality("locality",5,10)
>>> l1 = l0.clone()

>>> l0==l1
True
>>> l0.getName()
'locality'
>>> l1.setName("other-locality")
>>> l0==l1
False
>>> l0!=l1
True

>>> x = bpp.doubleCoord()
>>> ld = bpp.doubleLocality("real numbers!",x)


{LocusInfo.i}
[class] LocusInfo:
>>> bpp.LocusInfo.HAPLODIPLOID.fget()
0
>>> bpp.LocusInfo.HAPLOID.fget()
1
>>> bpp.LocusInfo.DIPLOID.fget()
2
>>> bpp.LocusInfo.UNKNOWN.fget()
9999

>>> lInfo = bpp.LocusInfo("some locus",bpp.LocusInfo.DIPLOID.fget())
>>> baInfo0 = bpp.BasicAlleleInfo("A616")
>>> baInfo1 = bpp.BasicAlleleInfo("A999")
>>> lInfo.addAlleleInfo(baInfo0)
>>> lInfo.addAlleleInfo(baInfo1)

>>> lInfo.getName()
'some locus'
>>> lInfo.getPloidy()
2
>>> lInfo.getNumberOfAlleles()
2

>>> lInfo.getAlleleInfoByKey(0).getId()
'A616'
>>> lInfo.getAlleleInfoById("A999").getId()
'A999'
>>> lInfo.getAlleleInfoKey("A999")
1

>>> lInfo.clear()
>>> lInfo.getNumberOfAlleles()
0

>>> bpp.LocusInfo(lInfo)
<bpp.LocusInfo; proxy of <Swig Object of type 'LocusInfo *' at 0x...> >


{MonoAlleleMonolocusGenotype.i}
[class] MonoAlleleMonolocusGenotype:
>>> genotype = bpp.MonoAlleleMonolocusGenotype(61)
>>> genotype = bpp.MonoAlleleMonolocusGenotype([61])
>>> genotype.getAlleleIndex()
(61,)
>>> genotype1 = bpp.MonoAlleleMonolocusGenotype(genotype)
>>> genotype == genotype1
True
>>> genotype2 = bpp.MonoAlleleMonolocusGenotype(21)
>>> genotype2 != genotype1
True
>>> genotype.clone()
<bpp.Clonable; proxy of <Swig Object of type 'Clonable *' at 0x...> >
>>> 


{MonolocusGenotype.i}
[class] (interface) MonolocusGenotype:
>>> genotype = bpp.MultiAlleleMonolocusGenotype([61,63,65,67])
>>> genotype.getAlleleIndex()
(61, 63, 65, 67)


{MonolocusGenotypeTools.i}
[class] MonolocusGenotypeTools:
>>> genotype = bpp.MonolocusGenotypeTools.buildMonolocusGenotypeByAlleleKey([61,61,61,61])
>>> genotype.getAlleleIndex()
(61, 61, 61, 61)


{MultiAlleleMonolocusGenotype.i}
[class] MultiAlleleMonolocusGenotype:
>>> genotype = bpp.MultiAlleleMonolocusGenotype([61,63,65,67])
>>> genotype1 = bpp.MultiAlleleMonolocusGenotype(genotype)
>>> genotype.getAlleleIndex()
(61, 63, 65, 67)
>>> genotype == genotype1
True
>>> genotype.isHomozygous()
False
>>> genotype = bpp.MultiAlleleMonolocusGenotype([61,61,61,61])
>>> genotype.isHomozygous()
True
>>> genotype.clone()
<bpp.Clonable; proxy of <Swig Object of type 'Clonable *' at 0x...> >


{MultilocusGenotype.i}
[class] MultilocusGenotype:
>>> genotype = bpp.MultilocusGenotype(2)
>>> mono0 = bpp.BiAlleleMonolocusGenotype(61,63)
>>> mono1 = bpp.BiAlleleMonolocusGenotype(65,65)

>>> lInfo = bpp.LocusInfo("locus5")
>>> baInfo0 = bpp.BasicAlleleInfo("A616")
>>> baInfo1 = bpp.BasicAlleleInfo("A999")
>>> lInfo.addAlleleInfo(baInfo0)
>>> lInfo.addAlleleInfo(baInfo1)

>>> genotype.size()
2
>>> genotype.countNonMissingLoci()
0
>>> genotype.setMonolocusGenotype(0,mono0)
>>> genotype.setMonolocusGenotype(1,mono1)
>>> genotype.countNonMissingLoci()
2
>>> genotype.countHomozygousLoci()
1
>>> genotype.countHeterozygousLoci()
1
>>> genotype.isMonolocusGenotypeMissing(0)
False
>>> genotype.getMonolocusGenotype(1).getAlleleIndex()
(65, 65)
>>> genotype.setMonolocusGenotypeByAlleleId(0, ["A616","A999"], lInfo)
>>> genotype.getMonolocusGenotype(0).getAlleleIndex()
(0, 1)
>>> genotype.setMonolocusGenotypeAsMissing(0)

"""


import doctest
import bpp
doctest.testmod(optionflags = 8)
