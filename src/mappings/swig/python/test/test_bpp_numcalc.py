"""

{AbstractDiscreteDistribution.i}
[class] AbstractDiscreteDistribution:
abstract

{AbstractNumericalDerivative.i}
[class] AbstractNumericalDerivative:
abstract

{AbstractOptimizer.i}
[class] AbstractOptimizer:
abstract

{AbstractParameterAliasable.i}
[class] AbstractParameterAliasable:
abstract


{AbstractParametrizable.i}
[class] AbstractParametrizable:
abstract

{AutoParameter.i}
[class] AutoParameter:
>>> p = bpp.Parameter("xxx",5)
>>> ap = bpp.AutoParameter(p)
>>> ap.getName()
'xxx'
>>> ap = bpp.AutoParameter()
>>> ap.getName()
''
>>> ap = bpp.AutoParameter("name", 5)
>>> ap.getName()
'name'


(Constraints)
[class] Constraint:
abstract
[class] Interval:
abstract

[class] IncludingPositiveReal:
>>> c = bpp.IncludingPositiveReal(1.0)
>>> c.getDescription()
'[ 1, +inf ['
>>> c.getLowerBound()
1.0
>>> c.setLowerBound(2.0)
>>> c.getLowerBound()
2.0
>>> c.isCorrect(3)
True
>>> c.isCorrect(1)
False
>>> c.isCorrect(2)
True
>>> c.getLimit(2)
2.0
>>> c.getLimit(3)
3.0
>>> c.getLimit(1)
2.0

[class] ExcludingPositiveReal:
>>> c = bpp.ExcludingPositiveReal(1.0)
>>> c.getDescription()
'] 1, +inf ['
>>> c.isCorrect(3)
True
>>> c.isCorrect(-1)
False
>>> c.isCorrect(1)
False
>>> c.getLimit(-1)
1.0
>>> c.setLowerBound(2)
>>> c.getLowerBound()
2.0

[class] IncludingNegativeReal:
>>> c = bpp.IncludingNegativeReal(1.0)
>>> c.getDescription()
'] -inf, 1 ]'
>>> c.isCorrect(1)
True
>>> c.isCorrect(2)
False
>>> c.getLimit(2)
1.0
>>> c.getLimit(0)
0.0
>>> c.setUpperBound(-1)
>>> c.getUpperBound()
-1.0

[class] ExcludingNegativeReal:
>>> c = bpp.ExcludingNegativeReal(-3.0)
>>> c.getDescription()
'] -inf, -3 ['
>>> c.isCorrect(1)
False
>>> c.isCorrect(-3)
False
>>> c.isCorrect(-4)
True
>>> c.getLimit(1)
-3.0
>>> c.getLimit(-4)
-4.0
>>> c.setUpperBound(-1)
>>> c.getUpperBound()
-1.0

[class] IncludingInterval:
>>> c = bpp.IncludingInterval(1, 3)
>>> c.getDescription()
'[ 1, 3 ]'
>>> c.getLowerBound()
1.0
>>> c.getUpperBound()
3.0
>>> c.isCorrect(2)
True
>>> c.isCorrect(3)
True
>>> c.isCorrect(4)
False
>>> c.getLimit(4)
3.0
>>> c.getLimit(0)
1.0
>>> c.setUpperBound(4)
>>> c.getUpperBound()
4.0
>>> c.setLowerBound(2)
>>> c.getLowerBound()
2.0

[class] ExcludingInterval:
>>> c = bpp.ExcludingInterval(1, 3)
>>> c.getDescription()
'] 1, 3 ['
>>> c.getLowerBound()
1.0
>>> c.getUpperBound()
3.0
>>> c.isCorrect(2)
True
>>> c.isCorrect(3)
False
>>> c.isCorrect(4)
False
>>> c.getLimit(4)
3.0
>>> c.getLimit(0)
1.0
>>> c.setUpperBound(4)
>>> c.setLowerBound(2)

[class] IncludingExcludingInterval:
>>> c = bpp.IncludingExcludingInterval(1, 3)
>>> c.getDescription()
'[ 1, 3 ['
>>> c.isCorrect(1)
True
>>> c.isCorrect(3)
False

[class] ExcludingIncludingInterval:
>>> c = bpp.ExcludingIncludingInterval(1, 3)
>>> c.getDescription()
'] 1, 3 ]'
>>> c.isCorrect(1)
False
>>> c.isCorrect(3)
True


{Domain.i}
[class] OutOfRangeException:
>>> x = bpp.OutOfRangeException("you missed", -5.5, 1, 10)
>>> x.what()
'you missedValue -5.5 is out of range [1, 10[.'

[class] Domain:
>>> d = bpp.Domain(1,10)
>>> d.getBounds()
(1.0, 10.0)
>>> d.getSize()
1
>>> d.getLowerBound()
1.0
>>> d.getUpperBound()
10.0
>>> d = bpp.Domain([1,10])
>>> d.getBounds()
(1.0, 10.0)

>>> d = bpp.Domain(0,24,3)
>>> d.getBounds()
(0.0, 8.0, 16.0, 24.0)
>>> d.getSize()
3
>>> d.getBound(0)
0.0
>>> d.getBound(1)
8.0
>>> d.getValue(0)
4.0
>>> d.getValue(1)
12.0
>>> d.getLowerValue()
4.0
>>> d.getUpperValue()
20.0
>>> d.getIndex(15)
1
>>> d.getNearestValue(15)
12.0
>>> d.getIndex(17)
2
>>> d.getNearestValue(17)
20.0

>>> d = bpp.Domain([0,10,20,30],[4,13,21])
>>> d.getNearestValue(19)
13.0
>>> d.getNearestValue(20)
21.0


{EigenValue.i}
[class] EigenValue:
>>> m = bpp.doubleRowMatrix()
>>> bpp.MatrixTools.getId(2,m)
>>> bpp.MatrixTools.scale(m,2,1)
>>> m[0],m[1]
((3.0, 1.0), (1.0, 3.0))
>>> ev = bpp.doubleEigenValue(m)
>>> ev.getRealEigenValues()
(2.0, 4.0)
>>> ev.getImagEigenValues()
(0.0, 0.0)
>>> ev.getV()[0],ev.getV()[1]
((0.70710678118654746, 0.70710678118654746), (-0.70710678118654746, 0.70710678118654746))
>>> ev.getD()[0],ev.getD()[1]
((2.0, 0.0), (0.0, 4.0))


{Function.i}
[class] Function:
abstract

[class] DerivableFirstOrder:
abstract

[class] DerivableSecondOrder:
abstract

[class] FunctionWrapper:
abstract


{FunctionTools.i}
[class] ParameterGrid:
>>> grid = bpp.ParameterGrid()
>>> grid.addDimension("x", [0,10])
>>> grid.addDimension("y", [-5,5,10])
>>> grid.getDimensionName(0)
'x'
>>> grid.getDimensionName(1)
'y'
>>> grid.getDimensionNames()
('x', 'y')
>>> grid.getNumberOfDimensions()
2
>>> grid.getTotalNumberOfPoints()
6
>>> grid.getPoints()
((0.0, 10.0), (-5.0, 5.0, 10.0))
>>> grid.getPointsForDimension(0)
(0.0, 10.0)
>>> grid.getPointsForDimension('y')
(-5.0, 5.0, 10.0)


{Matrix.i}
[class] RowMatrix:
>>> m = bpp.intRowMatrix()
>>> m.nRows()
0
>>> m.nCols()
0
>>> n = bpp.intRowMatrix(4, 5)
>>> n.nRows()
4
>>> n.nCols()
5
>>> m.resize(3,4)
>>> m.nRows()
3
>>> m.nCols()
4

>>> o = bpp.intRowMatrix(m)
>>> o.nRows()
3
>>> o = n.clone()
>>> o.nRows()
4

>>> m[0]
(0, 0, 0, 0)
>>> m.row(0)
(0, 0, 0, 0)
>>> m.col(1)
(0, 0, 0)

>>> x = bpp.doubleRowMatrix(3, 3)
>>> x[0]
(0.0, 0.0, 0.0)


{MatrixTools.i}
[class] MatrixTools:
>>> m = bpp.intRowMatrix()
>>> bpp.MatrixTools.getId(2,m)
>>> m[0],m[1]
((1, 0), (0, 1))
>>> n = bpp.intRowMatrix()
>>> bpp.MatrixTools.getId(2,n)
>>> bpp.MatrixTools.add(m,n)
>>> m[0],m[1]
((2, 0), (0, 2))

>>> bpp.MatrixTools.fill(m,5)
>>> m[0],m[1]
((5, 5), (5, 5))
>>> bpp.MatrixTools.scale(m,3)
>>> m[0],m[1]
((15, 15), (15, 15))
>>> bpp.MatrixTools.scale(m,2,2)
>>> m[0],m[1]
((32, 32), (32, 32))

>>> m = bpp.intRowMatrix()
>>> v = bpp.intVector()
>>> v.append(1)
>>> v.append(2)
>>> v.append(3)
>>> bpp.MatrixTools.diag(v,m)
>>> m[0],m[1],m[2]
((1, 0, 0), (0, 2, 0), (0, 0, 3))

>>> bpp.MatrixTools.fill(5,m)
>>> bpp.MatrixTools.diag(m,v)
>>> v[0],v[1],v[2]
(5, 5, 5)

>>> bpp.MatrixTools.fill(m,5)
>>> bpp.MatrixTools.getId(3,n)
>>> n[0],n[1],n[2]
((1, 0, 0), (0, 1, 0), (0, 0, 1))
>>> a = bpp.intRowMatrix()
>>> bpp.MatrixTools.mult(m,n,a)
>>> a[0],a[1],a[2]
((5, 5, 5), (5, 5, 5), (5, 5, 5))
>>> bpp.MatrixTools.mult(m,v,n,a)
>>> a[0],a[1],a[2]
((25, 25, 25), (25, 25, 25), (25, 25, 25))

>>> v.clear()
>>> v.append(2)
>>> v.append(4)
>>> v.append(6)
>>> bpp.MatrixTools.diag(v,m)
>>> m[0],m[1],m[2]
((2, 0, 0), (0, 4, 0), (0, 0, 6))
>>> bpp.MatrixTools.whichmax(m)
(2, 2)
>>> bpp.MatrixTools.whichmin(m)
(0, 1)
>>> bpp.MatrixTools._print(m)
3x3
[
[2, 0, 0]
[0, 4, 0]
[0, 0, 6]
]
>>> bpp.MatrixTools.isSquare(m)
True

>>> bpp.MatrixTools.getId(3,id)
>>> bpp.MatrixTools.getId(2,i)
>>> bpp.MatrixTools.inv(id,a)
>>> a[0],a[1],a[2]
((1, 0, 0), (0, 1, 0), (0, 0, 1))

>>> bpp.MatrixTools.getId(2,id)
>>> m = bpp.intRowMatrix(2,2)
>>> bpp.MatrixTools.fill(m,3)
>>> bpp.MatrixTools.kroneckerSum(id,m,a)
>>> a[0],a[1],a[2],a[3]
((1, 0, 5, 0), (0, 1, 5, 0), (5, 5, 3, 3), (0, 0, 3, 3))
>>> bpp.MatrixTools.kroneckerMult(id,m,a)
>>> a[0],a[1],a[2],a[3]
((3, 3, 0, 0), (3, 3, 0, 0), (0, 0, 3, 3), (0, 0, 3, 3))
>>> bpp.MatrixTools.copy(a,n)
>>> n[0],n[1],n[2],n[3]
((3, 3, 0, 0), (3, 3, 0, 0), (0, 0, 3, 3), (0, 0, 3, 3))

>>> m = bpp.doubleRowMatrix(3,3)
>>> a = bpp.doubleRowMatrix()
>>> bpp.MatrixTools.fill(m,2)
>>> bpp.MatrixTools.pow(m,3,a)
>>> a[0],a[1],a[2]
((72.0, 72.0, 72.0), (72.0, 72.0, 72.0), (72.0, 72.0, 72.0))

>>> id = bpp.doubleRowMatrix()
>>> bpp.MatrixTools.getId(2,id)
>>> bpp.MatrixTools.exp(id,a)
>>> a[0],a[1]
((2.7182818284590451, 0.0), (0.0, 2.7182818284590451))

>>> m = bpp.doubleRowMatrix(2,2)
>>> a = bpp.doubleRowMatrix()
>>> bpp.MatrixTools.fill(m,2)
>>> m.resize(1,2)
>>> m.resize(2,2)
>>> m[0],m[1]
((2.0, 2.0), (0.0, 0.0))
>>> bpp.MatrixTools.transpose(m,a)
>>> a[0],a[1]
((2.0, 0.0), (2.0, 0.0))


{NumCalcApplicationTools.i}
[class] NumCalcApplicationTools:
>>> bpp.NumCalcApplicationTools.seqFromString("2,4,6")
(2, 4, 6)
>>> bpp.NumCalcApplicationTools.seqFromString("2,4,6-10")
(2, 4, 6, 7, 8, 9, 10)
>>> bpp.NumCalcApplicationTools.getVector("1.0, 2.5, 3.25, 4.0")
(1.0, 2.5, 3.25, 4.0)
>>> bpp.NumCalcApplicationTools.getVector("seq(from=1,to=5,step=2)")
(1.0, 3.0, 5.0)
>>> bpp.NumCalcApplicationTools.getVector("seq(from=1,to=5,size=4)")
(1.0, 2.0, 3.0, 5.0)

>>> pl = bpp.ParameterList()
>>> pl.addParameter(bpp.Parameter("a",1))
>>> pl.addParameter(bpp.Parameter("b",2))
>>> pl.addParameter(bpp.Parameter("c",3))
>>> bpp.NumCalcApplicationTools.getDefaultValue(pl,"a",-666)
1.0
>>> bpp.NumCalcApplicationTools.getDefaultValue(pl,"d",-666)
-666.0

>>> map = bpp.strMap()
>>> map["grid.number_of_parameters"] = '2'
>>> map["grid.parameter1.name"] = 'x'
>>> map["grid.parameter1.values"] = "5,6"
>>> map["grid.parameter2.name"] = 'y'
>>> map["grid.parameter2.values"] = "1,2,3"
>>> g = bpp.NumCalcApplicationTools.getParameterGrid(map)
>>> g.getPoints()
((5.0, 6.0), (1.0, 2.0, 3.0))


{NumConstants.i}
[class] NumConstants:
>>> bpp.NumConstants.GOLDEN_RATIO_PHI
1.6180339887498949
>>> bpp.NumConstants.GOLDEN_RATIO_R
0.6180339887498949
>>> bpp.NumConstants.GOLDEN_RATIO_C
0.3819660112501051
>>> bpp.NumConstants.TINY
9.9999999999999998e-13
>>> bpp.NumConstants.VERY_TINY
9.9999999999999995e-21
>>> bpp.NumConstants.VERY_BIG
1.7e+23
>>> bpp.NumConstants.PI
3.1415929999999999


{NumTools.i}
[class] NumTools
>>> bpp.NumTools.abs(-5)
5
>>> bpp.NumTools.abs(-5.0)
5.0
>>> bpp.NumTools.sign(5)
1
>>> bpp.NumTools.sign(-5)
-1
>>> bpp.NumTools.sign(600.0)
1.0
>>> bpp.NumTools.sign(4,-5)
-4
>>> bpp.NumTools.sign(4,23)
4
>>> bpp.NumTools.max(4,5)
5
>>> bpp.NumTools.min(4,5)
4
>>> bpp.NumTools.sqr(4)
16
>>> bpp.NumTools.pow(2,5)
32
>>> bpp.NumTools.fact(4)
24
>>> a = bpp.intp()
>>> a.assign(4)
>>> b = bpp.intp()
>>> b.assign(21)
>>> bpp.NumTools.swap(a,b)
>>> a.value()
21
>>> b.value()
4

>>> bpp.NumTools.shift(a,b,5)
>>> bpp.NumTools.shift(a,b,6)
>>> a.value()
5
>>> b.value()
6
>>> bpp.NumTools.shift(a,b,36)
>>> a.value()
6
>>> b.value()
36
>>> c = bpp.intp()
>>> c.assign(-16)
>>> bpp.NumTools.shift(a,b,c,30)
>>> a.value()
36
>>> b.value()
-16
>>> c.value()
30


{Optimizer.i}
[class] OptimizationEvent:
>>> oe = bpp.OptimizationEvent(bpp.BrentOneDimension())
>>> oe.getOptimizer()
<bpp.Optimizer; proxy of <Swig Object of type 'Optimizer *' at 0x...> >

[class] OptimizationListener:
abstract, no known inheritor

[class] Optimizer:
abstract


{Parameter.i}
[class] Parameter:
>>> p = bpp.Parameter("xxx", 5)
>>> p.getName()
'xxx'
>>> p.getValue()
5.0
>>> p.setName("yyy")
>>> p.setValue(6)
>>> p.hasConstraint()
False
>>> p = bpp.Parameter("xxx", 5, bpp.IncludingPositiveReal(-5))
>>> p.hasConstraint()
True
>>> p.getConstraint()
<bpp.Constraint; proxy of <Swig Object of type 'Constraint *' at 0x...> >

[class] ParameterListener:
# other functions segfault, because they rely on ConstraintException (see ParameterExceptions)
# ParameterListener is abstract
# addParameterListener relies on classes inheriting from ParameterListener, which are all nested--they can't be done in SWIG right now

[class] ParameterEvent:
>>> e = bpp.ParameterEvent(bpp.Parameter())
>>> e.clone()
<bpp.Clonable; proxy of <Swig Object of type 'Clonable *' at 0x95afd58> >
>>> e.getParameter()
<bpp.Parameter; proxy of <Swig Object of type 'Parameter *' at 0x95a5538> >
>>> e.getParameter().getName()


{ParameterAliasable.i}
[class] ParameterAliasable:
abstract

[class] ParameterAliasableAdapter:
abstract


{ParameterExceptions.i}
[class] ParameterException:
>>> x = bpp.ParameterException("bad parameter", bpp.Parameter())
>>> x.what()
'ParameterException: bad parameter()'

[class] ParameterNotFoundException:
>>> x = bpp.ParameterNotFoundException("aaa", "bbb")
>>> x.what()
'ParameternotFoundException: aaa(bbb)'

[class] ConstraintException:
# ConstraintException segfaults, even in straight C++


{ParameterList.i}
[class] ParameterList:
>>> pl = bpp.ParameterList()
>>> pl.addParameter(bpp.Parameter("one", 1))
>>> pl.addParameter(bpp.Parameter("two", 2))
>>> pl.addParameter(bpp.Parameter("three", 3))
>>> pl.printParameters(bpp.ApplicationTools.getMessage())
Name:	Value:	Constraint:
_________________________________________________
one	1
two	2
three	3
>>> pl1 = pl.clone()
>>> pl1.deleteParameter("one")
>>> pl1.setParameterValue("two", -2)
>>> pl1.printParameters(bpp.ApplicationTools.getMessage())
Name:	Value:	Constraint:
_________________________________________________
two	-2
three	3
>>> pl1.setAllParametersValues(pl)
>>> pl1.printParameters(bpp.ApplicationTools.getMessage())
Name:	Value:	Constraint:
_________________________________________________
two	2
three	3
>>> pl.getParameterNames()
('one', 'two', 'three')

>>> pl2 = bpp.ParameterList()
>>> pl2.addParameter(bpp.Parameter("four", 4))
>>> pl2.addParameter(bpp.Parameter("five", 5))
>>> pl.addParameters(pl2)
>>> pl.deleteParameters(["two","four"])
>>> pl.getParameterNames()
('one', 'three', 'five')
>>> pl.whichParameterHasName("five")
2
>>> pl3 = pl.subList(1)
>>> pl3.getParameterNames()
('three',)
>>> pl3 = pl.intVectorSubList([1,2])
>>> pl3.getParameterNames()
('three', 'five')
>>> pl3 = pl.subList(["one","three"])
>>> pl3.getParameterNames()
('one', 'three')
>>> pl3.getParameter("one").getValue()
1.0

>>> pl3.hasParameter("two")
False
>>> pl1.getCommonParametersWith(pl3).getParameterNames()
('three',)

>>> pl1.getParameterNames()
('two', 'three')
>>> pl1.setParameterValue('two', -2)
>>> pl1.setParameterValue('three', -3)
>>> pl.matchParameters(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())
Name:	Value:	Constraint:
_________________________________________________
one	1
three	-3
five	5
>>> pl.setParameterValue('three', 3)
>>> pl.matchParametersValues(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())
Name:	Value:	Constraint:
_________________________________________________
one	1
three	-3
five	5

>>> pl1.deleteParameter("two")
>>> pl.setParameterValue('three', 3)
>>> pl.setParameters(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())
Name:	Value:	Constraint:
_________________________________________________
one	1
three	-3
five	5
>>> pl.setParameterValue('three', 3)
>>> pl.setParametersValues(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())
Name:	Value:	Constraint:
_________________________________________________
one	1
three	-3
five	5

>>> pl1 = pl.clone()
>>> pl.setParameterValue('three', 3)
>>> pl.setAllParametersValues(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())
Name:	Value:	Constraint:
_________________________________________________
one	1
three	-3
five	5

>>> pl1.intVectorDeleteParameters([0,2])
>>> pl1.getParameterNames()
('three',)
>>> pl.reset()
>>> pl.getParameterNames()
()


{Parametrizable.i}
[class] Parametrizable:
abstract

[class] ParametrizableAdapter:
abstract

{RandomFactory.i}
[class] RandomFactory:
object is abstract


{RandomTools.i}
[class] RandomTools:
>>> u = bpp.Uniform01K(3)
>>> bpp.RandomTools.flipCoin(u)
False
>>> bpp.RandomTools.giveIntRandomNumberBetweenZeroAndEntry(100,u)
31
>>> bpp.RandomTools.giveRandomNumberBetweenZeroAndEntry(100.0,u)
60.814047800000004
>>> bpp.RandomTools.randGaussian(0.0, 1.0, u)
-0.62069527689490023
>>> bpp.RandomTools.randGamma(0.5, u)
0.30268821638682947
>>> bpp.RandomTools.randGamma(0.5, 1.0, u)
0.01802603635810052
>>> bpp.RandomTools.randExponential(10.0, u)
19.300665788857199
>>> bpp.RandomTools.setSeed(123)
>>> bpp.RandomTools.intGetSample([1,2,3,10,20,30],4)
(20, 2, 30, 10)
>>> bpp.RandomTools.intGetSample([1,2,3,10,20,30],7,True)
(3, 1, 2, 3, 1, 3, 2)
>>> bpp.RandomTools.doubleGetSample([1.0,2.0,3.0,10.0,20.0,30.0],4)
(1.0, 20.0, 2.0, 3.0)
>>> bpp.RandomTools.doubleGetSample([1.0,2.0,3.0,10.0,20.0,30.0],7,True)
(3.0, 30.0, 30.0, 10.0, 30.0, 3.0, 10.0)
>>> bpp.RandomTools.randMultinomial(3, [0.1,0.2,0.7])
(2, 1, 0)
>>> bpp.RandomTools.qNorm(0.8)
0.84162122160185238
>>> bpp.RandomTools.lnGamma(10)
12.801827480080648
>>> bpp.RandomTools.incompleteGamma(1,2,3)
0.013155790587229233
>>> bpp.RandomTools.qChisq(0.5,1)
0.45493642315776361
>>> bpp.RandomTools.pChisq(2,2)
0.63212055877757123
>>> bpp.RandomTools.qGamma(0.5,1,1)
0.69314718056711344
>>> bpp.RandomTools.pGamma(2,1,1)
0.86466471676068735


{StatTest.i}
[class] StatTest:
object is abstract


{TestUnit.i}
[class] TestUnit:
>>> bpp.TestUnit().testEigen()
M=
2x2
[
[2.3, 1.4]
[5, -0.9]
]
D=
2x2
[
[3.79192, 0]
[0, -2.39192]
]
V1=
2x2
[
[0.684285, -0.330851]
[0.729215, 1.10881]
]
V2=
2x2
[
[1.10881, 0.330851]
[-0.729215, 0.684285]
]
V1 . D . V2=
2x2
[
[2.3, 1.4]
[5, -0.9]
]
False


{Uniform01K.i}
[class] Uniform01K:
>>> u = bpp.Uniform01K(2)
>>> u.drawNumber()
0.29863335200000002
>>> u.drawNumber()
0.92540093800000001
>>> u.setSeed(2)
>>> u.drawNumber()
0.29863335200000002


{Uniform01QD.i}
[class] Uniform01QD:
>>> u = bpp.Uniform01QD(1)
>>> u.drawNumber()
0.51387007813900709
>>> u.drawNumber()
0.82425869675353169
>>> u.setSeed(1)
>>> u.drawNumber()
0.51387007813900709


{Uniform01WH.i}
[class] Uniform01WH:
>>> u = bpp.Uniform01WH(10000)
>>> u.drawNumber()
0.54945270025470894
>>> u.drawNumber()
0.95144549201369322
>>> u.setSeed(10000)
>>> u.drawNumber()
0.54945270025470894

{VectorExceptions.i}
[class] VectorException:
>>> vi = bpp.intVector()
>>> vi.append(1)
>>> vi.append(2)
>>> vd = bpp.doubleVector()
>>> vd.append(1.0)
>>> vd.append(2.0)

>>> x = bpp.intVectorException("silly vector", vi)
>>> x.what()
'VectorException: silly vector'
>>> x.getVector()[0]
1
>>> x = bpp.doubleVectorException("silly double vector", vd)
>>> x.what()
'VectorException: silly double vector'
>>> x.getVector()[0]
1.0

[class] EmptyVectorException:
>>> x = bpp.intEmptyVectorException("silly empty vector", vi)
>>> x.what()
'VectorException: EmptyVectorException: silly empty vector'
>>> x.getVector()[0]
1

[class] DimensionException:
>>> x = bpp.DimensionException("bad dimension!", 2, 3)
>>> x.what()
'DimensionException (found 2, should be 3bad dimension!'
>>> x.getDimension()
2
>>> x.getCorrectDimension()
3

[class] ElementNotFoundException:
>>> p = bpp.intp()
>>> x = bpp.intElementNotFoundException("I'm lost!", vi, p)
>>> x.what()
"VectorException: ElementNotFoundException: I'm lost!"
>>> x.getVector()[0]
1
>>> x.getElement()
<Swig Object of type 'int *' at 0x8fbf750>
>>> bpp.intp.frompointer(x.getElement()).value()
0


"""


import doctest
import bpp
doctest.testmod(optionflags = 8)
