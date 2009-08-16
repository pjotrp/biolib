"""

{AbstractDiscreteDistribution.i}
[class] AbstractDiscreteDistribution:
>>> gamma = bpp.GammaDiscreteDistribution(3,1.0,1.0,"namespace")
>>> gamma._print(bpp.ApplicationTools.getMessage())
>>> gamma.getNumberOfCategories()
3
>>> gamma.getCategory(1)
0.71231792758713031
>>> gamma.getProbability(1)
0.33333333333333331
>>> gamma.getProbability(gamma.getCategory(1))
0.33333333333333331
>>> gamma.getCategories()
(0.18906978373849975, 0.71231792758713031, 2.0986122886743699)
>>> gamma.getProbabilities()
(0.33333333333333331, 0.33333333333333331, 0.33333333333333331)

#>>> gamma.rand()
#...
#>>> gamma.randC()
#...

>>> gamma.getDomain().getBounds()
(0.0, 0.40546510813254732, 1.0986122886880603, 1.7e+23)

>>> gamma.getInfCumulativeProbability(0)
1.0
>>> gamma.getInfCumulativeProbability(1)
1.0
>>> gamma.getInfCumulativeProbability(2)
1.0
>>> gamma.getIInfCumulativeProbability(0)
0.0
>>> gamma.getIInfCumulativeProbability(1)
0.0
>>> gamma.getIInfCumulativeProbability(2)
0.0
>>> gamma.getSupCumulativeProbability(0)
0.0
>>> gamma.getSupCumulativeProbability(1)
0.0
>>> gamma.getSupCumulativeProbability(2)
0.0
>>> gamma.getSSupCumulativeProbability(0)
0.0
>>> gamma.getSSupCumulativeProbability(1)
0.0
>>> gamma.getSSupCumulativeProbability(2)
0.0

>>> con = bpp.ConstantDistribution(0.5)
>>> con.getCategories()
(0.5,)
>>> con.getProbabilities()
(1.0,)
>>> con.set(0.5, 0.25)
>>> con.getCategories()
(0.5,)
>>> con.getProbabilities()
(0.25,)
>>> con.add(1.0,0.25)
>>> con.getCategories()
(0.5, 1.0)
>>> con.getProbabilities()
(0.25, 0.25)


{AbstractParameterAliasable.i}
[class] AbstractParameterAliasable:
>>> gamma = bpp.GammaDiscreteDistribution(3,1.0,1.0)
>>> gamma.getIndependentParameters().getParameterNames()
('alpha', 'beta')
>>> gamma.getNumberOfIndependentParameters()
2
>>> gamma.aliasParameters("alpha", "beta")
>>> gamma.getIndependentParameters().getParameterNames()
('alpha',)
>>> gamma.getParameterValue("alpha"), gamma.getParameterValue("beta")
(1.0, 1.0)
>>> gamma.setParameterValue("alpha", 2.0)
>>> gamma.getParameterValue("alpha"), gamma.getParameterValue("beta")
(2.0, 2.0)
>>> gamma.setParameterValue("beta", 3.0)
>>> gamma.getParameterValue("alpha"), gamma.getParameterValue("beta")
(2.0, 3.0)
>>> gamma.unaliasParameters("alpha", "beta")
>>> gamma.getIndependentParameters().getParameterNames()
('alpha', 'beta')
>>> gamma.setNamespace("ns")
>>> gamma.getIndependentParameters().getParameterNames()
('nsalpha', 'nsbeta')


{AbstractParametrizable.i}
[class] AbstractParametrizable:
>>> gamma = bpp.GammaDiscreteDistribution(3,1.0,1.0,"namespace")
>>> gamma.getNamespace()
'namespace'
>>> gamma.getNumberOfParameters()
2
>>> gamma.getParameters().getParameterNames()
('namespacealpha', 'namespacebeta')
>>> gamma.hasParameter("alpha")
True
>>> gamma.hasParameter("zeta")
False
>>> gamma.getParameter("alpha").getValue()
1.0
>>> gamma.getParameterValue("alpha")
1.0
>>> gamma.setParameterValue("beta", 2.0)
>>> gamma.getParameterValue("beta")
2.0
>>> gamma.getParameterNameWithoutNamespace("namespaceblerg")
'blerg'
>>> gamma.setNamespace("")

>>> pList = gamma.getParameters()
>>> gamma.fireParameterChanged(pList)

>>> gamma.getCategories()
(0.094534891869249876, 0.35615896379356515, 1.0493061443371849)
>>> gamma.getParameterValue("beta")
2.0
>>> gamma.setParameterValue("beta", 1.0)
>>> gamma.getCategories()
(0.18906978373849975, 0.71231792758713031, 2.0986122886743699)
>>> gamma.getProbabilities()
(0.33333333333333331, 0.33333333333333331, 0.33333333333333331)

>>> pList = gamma.getParameters()
>>> pList.getParameterNames()
('alpha', 'beta')
>>> b2List = pList.clone()
>>> b2List.setParameterValue("beta", 2.0)

>>> g1 = gamma.clone()
>>> g1.getParameterValue("beta")
1.0
>>> g1.matchParametersValues(b2List)
>>> g1.getParameterValue("beta")
2.0
>>> g1.setParametersValues(pList)
>>> g1.getParameterValue("beta")
1.0
>>> g1.setAllParametersValues(b2List)
>>> g1.getParameterValue("beta")
2.0


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


{ConstantDistribution.i}
[class] ConstantDistribution:
>>> con = bpp.ConstantDistribution(0.5)
>>> con._print(bpp.ApplicationTools.getMessage())
>>> con.randC()
0.5
>>> con.getDomain().getBounds()
(0.5, 0.5)


(Constraints.i)
[class] Constraint:
abstract, see IncludingPositveReal
[class] Interval:
abstract, see IncludingInterval

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


{DataTable.i}
[class] DataTable:
>>> table = bpp.DataTable(2,3)
>>> table.getNumberOfRows()
2
>>> table.getNumberOfColumns()
3
>>> table.addRow(["a","b","c"])
>>> table.deleteRow(0)
>>> clone = table.clone()
>>> bpp.DataTable.write(clone, bpp.ApplicationTools.getMessage())
		
a	b	c
>>> table.getRow(0)
('', '', '')
>>> table.getRow(1)
('a', 'b', 'c')
>>> table.hasRowNames()
False
>>> table.hasColumnNames()
False
>>> table.setRowNames(["alice", "bob"])
>>> table.getRow("alice")
('', '', '')
>>> table.deleteRow("alice")
>>> table.hasRow("alice")
False
>>> table.getRowName(0)
'bob'
>>> table.addRow("carol", ["x","y","z"])
>>> table.getRowNames()
('bob', 'carol')
>>> copy = bpp.DataTable(table)
>>> copy.getColumn(1)
<bpp.strVector; proxy of <Swig Object of type 'std::vector< std::string > *' at 0x...> >
>>> copy.getColumn(1)[0], copy.getColumn(1)[1]
('b', 'y')

>>> copy.setColumnNames(["col1","col2","col3"])
>>> copy.hasColumnNames()
True
>>> copy.getColumn("col3")
<bpp.strVector; proxy of <Swig Object of type 'std::vector< std::string > *' at 0x...> >
>>> copy.deleteColumn("col2")
>>> copy.hasColumn("col2")
False
>>> copy.getColumnNames()
('col1', 'col3')
>>> copy.getRow("carol")
('x', 'z')
>>> copy.deleteColumn(1)
>>> copy.getRow("bob")
('a',)
>>> copy.getColumnName(0)
'col1'
>>> named = bpp.DataTable(["alpha","bravo","charlie"])
>>> named.getColumnNames()
('alpha', 'bravo', 'charlie')


{DataTableExceptions.i}
[class] TableNameNotFoundException:
>>> x = bpp.TableNameNotFoundException("Except this!","tablename")
>>> x.getName()
'tablename'
>>> x.what()
'TableNameNotFoundException: tablename. Except this!'

[class] TableRowNameNotFoundException:
>>> x = bpp.TableRowNameNotFoundException("Missing row!", "rowname")
>>> x.getName()
'rowname'
>>> x.what()
'TableNameNotFoundException: rowname. TableRowNameNotFoundException: rowname. Missing row!'

[class] TableColumnNameNotFoundException:
>>> x = bpp.TableColumnNameNotFoundException("Missing column!", "colname")
>>> x.getName()
'colname'
>>> x.what()
'TableNameNotFoundException: colname. TableColumnNameNotFoundException: colname. Missing column!'

[class] NoTableRowNamesException:
>>> x = bpp.NoTableRowNamesException("Stupid table!")
>>> x.what()
'NoTableRowNamesException: Stupid table!'

[class] NoTableColumnNamesException:
>>> x = bpp.NoTableColumnNamesException("No columns either!")
>>> x.what()
'NoTableColumnNamesException: No columns either!'

[class] TableRowNamesException:
>>> x = bpp.TableRowNamesException("Something's fishy")
>>> x.what()
"TableRowNamesException: Something's fishy"

[class] TableColumnNamesException:
>>> x = bpp.TableColumnNamesException("These tables suck!")
>>> x.what()
'TableColumnNamesException: These tables suck!'

[class] DuplicatedTableRowNameException:
>>> x = bpp.DuplicatedTableRowNameException("Seeing double!")
>>> x.what()
'DuplicatedTableRowNameException: Seeing double!'

[class] DuplicatedTableColumnNameException:
>>> x = bpp.DuplicatedTableColumnNameException("You listed Doric twice.")
>>> x.what()
'DuplicatedTableColumnNameException: You listed Doric twice.'


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


{DiscreteDistribution.i}
[class] DiscreteDistribution:
abstract, see AbstractDiscreteDistribution


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


{ExponentialDiscreteDistribution.i}
[class] ExponentialDiscreteDistribution:
>>> exp = bpp.ExponentialDiscreteDistribution(2,1,False)
>>> exp
<bpp.ExponentialDiscreteDistribution; proxy of <Swig Object of type 'ExponentialDiscreteDistribution *' at 0x...> >
>>> exp.getDomain().getBounds()
(0.0, 0.69314718055994529, 1.7e+23)

#>>> exp.randC()


{Function.i}
[xlass] Function:
abstract

[xlass] DerivableFirstOrder:
abstract

[xlass] DerivableSecondOrder:
abstract

[xlass] FunctionWrapper:
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


{GammaDiscreteDistribution.i}
[GammaDiscreteDistribution]
>>> gamma = bpp.GammaDiscreteDistribution(3,1.0,1.0,"namespace")
>>> gamma.clone()
<bpp.GammaDiscreteDistribution; proxy of <Swig Object of type 'GammaDiscreteDistribution *' at 0x...> >
>>> gamma.getDomain().getBounds()
(0.0, 0.40546510813254732, 1.0986122886880603, 1.7e+23)

#>>> gamma.randC()



{IntervalData.i}
[class IntervalData]
>>> d = bpp.Domain(0,100,10)
>>> data = bpp.IntervalData(d, "decile-buckets")
>>> data.getName()
'decile-buckets'
>>> data.getFrequencies()
(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
>>> data.getDensities()
(nan, nan, nan, nan, nan, nan, nan, nan, nan, nan)
>>> data.addValue(21.5)
>>> data.addValue(35.4)
>>> data.addValue(16)
>>> data.addValue(41)
>>> data.addValue(89.25)
>>> data.addValue(15.5)
>>> data.addValue(12)
>>> data.addValue(24)

>>> data._print(bpp.ApplicationTools.getMessage())
>>> data.getFrequencies()
(0, 3, 2, 1, 1, 0, 0, 0, 1, 0)
>>> data.getDensities()
(0.0, 0.375, 0.25, 0.125, 0.125, 0.0, 0.0, 0.0, 0.125, 0.0)

>>> data.getFreq(3)
1
>>> data.getDensity(3)
0.125

>>> data.getSize()
8
>>> data.getMinValue()
12.0
>>> data.getMaxValue()
89.25
>>> data.getMean()
31.831250000000001
>>> data.getSD()
559.0493359374999
>>> data.getSDP()
559.0493359374999

>>> data.getDomain()
<bpp.Domain; proxy of <Swig Object of type 'Domain *' at 0x...> >
>>> data.getDomainValue(36.4)
35.0
>>> data.reset()


{InvariantMixedDiscreteDistribution.i}
[class] InvariantMixedDiscreteDistribution:

Important Note: InvariantMixedDiscreteDistribution can be tested, but
only on its own. There is a bug in its destructor that causes it to
seg fault. (This also happens when using it in straight C++.)  If the
following lines are uncommented, it will appear to work fine, but the
entire numcalc test will seg fault near the end, preventing the final
testing results from being displayed.

#>>> con = bpp.ConstantDistribution(3)
#>>> invar = bpp.InvariantMixedDiscreteDistribution(con,0.5)
#>>> invar.rand()
#>>> i1 = invar.clone()
#>>> i2 = bpp.InvariantMixedDiscreteDistribution(invar)

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

>>> bpp.MatrixTools.fill(m,5)
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
>>> bpp.MatrixTools.isSquare(m)
True

>>> id = bpp.intRowMatrix()
>>> bpp.MatrixTools.getId(3,id)
>>> bpp.MatrixTools.inv(id,a)
>>> a[0],a[1],a[2]
((1, 0, 0), (0, 1, 0), (0, 0, 1))

>>> bpp.MatrixTools.getId(2,id)
>>> m = bpp.intRowMatrix(2,2)
>>> bpp.MatrixTools.fill(m,3)
>>> bpp.MatrixTools.kroneckerSum(id,m,a)
>>> a[0],a[1],a[2],a[3]
((1, 0, 0, 0), (0, 1, 0, 0), (0, 0, 3, 3), (0, 0, 3, 3))
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


#{NumConstants.i}
#[class] NumConstants:
#>>> bpp.NumConstants.GOLDEN_RATIO_PHI
#1.6180339887498949
#>>> bpp.NumConstants.GOLDEN_RATIO_R
#0.6180339887498949
#>>> bpp.NumConstants.GOLDEN_RATIO_C
#0.3819660112501051
#>>> bpp.NumConstants.TINY
#9.9999999999999998e-13
#>>> bpp.NumConstants.VERY_TINY
#9.9999999999999995e-21

#>>> bpp.NumConstants.VERY_BIG
#1.7e+23

#>>> bpp.NumConstants.PI
#3.1415929999999999


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


{OneDimensionOptimizationTools.i}
[class] Point:
>>> p = bpp.Point(1.0,2.0)
>>> p.x
1.0
>>> p.f
2.0
>>> p.set(3,4)
>>> p.x
3.0
>>> p.f
4.0

[class] Bracket:
>>> bracket = bpp.Bracket()
>>> bracket.setA(1,2)
>>> bracket.setB(3,4)
>>> bracket.setC(5,6)
>>> bracket.a.x
1.0
>>> bracket.b.f
4.0
>>> bracket.c.x
5.0


{Optimizer.i}
[class] OptimizationEvent:
>>> oe = bpp.OptimizationEvent(bpp.BrentOneDimension())
>>> oe.getOptimizer()
<bpp.Optimizer; proxy of <Swig Object of type 'Optimizer *' at 0x...> >

[class] OptimizationListener:
abstract, no known inheritor

[xlass] Optimizer:
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
>>> param = bpp.Parameter()
>>> e = bpp.ParameterEvent(param)
>>> e.clone()
<bpp.Clonable; proxy of <Swig Object of type 'Clonable *' at 0x...> >
>>> e.getParameter()
<bpp.Parameter; proxy of <Swig Object of type 'Parameter *' at 0x...> >
>>> e.getParameter().getName()
''


{ParameterAliasable.i}
[class] ParameterAliasable:
abstract, see AbstractParameterAliasable

[class] ParameterAliasableAdapter:
abstract, see AbstractParameterAliasable


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

#Name:	Value:	Constraint:
#_________________________________________________
#one	1
#two	2
#three	3
>>> pl1 = pl.clone()
>>> pl1.deleteParameter("one")
>>> pl1.setParameterValue("two", -2)
>>> pl1.printParameters(bpp.ApplicationTools.getMessage())

#Name:	Value:	Constraint:
#_________________________________________________
#two	-2
#three	3
>>> pl1.setAllParametersValues(pl)
>>> pl1.printParameters(bpp.ApplicationTools.getMessage())

#Name:	Value:	Constraint:
#_________________________________________________
#two	2
#three	3
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

#Name:	Value:	Constraint:
#_________________________________________________
#one	1
#three	-3
#five	5
>>> pl.setParameterValue('three', 3)
>>> pl.matchParametersValues(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())

#Name:	Value:	Constraint:
#_________________________________________________
#one	1
#three	-3
#five	5

>>> pl1.deleteParameter("two")
>>> pl.setParameterValue('three', 3)
>>> pl.setParameters(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())

#Name:	Value:	Constraint:
#_________________________________________________
#one	1
#three	-3
#five	5
>>> pl.setParameterValue('three', 3)
>>> pl.setParametersValues(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())

#Name:	Value:	Constraint:
#_________________________________________________
#one	1
#three	-3
#five	5

>>> pl1 = pl.clone()
>>> pl.setParameterValue('three', 3)
>>> pl.setAllParametersValues(pl1)
>>> pl.printParameters(bpp.ApplicationTools.getMessage())

#Name:	Value:	Constraint:
#_________________________________________________
#one	1
#three	-3
#five	5

>>> pl1.intVectorDeleteParameters([0,2])
>>> pl1.getParameterNames()
('three',)
>>> pl.reset()
>>> pl.getParameterNames()
()


{Parametrizable.i}
[class] Parametrizable:
abstract, see AbstractParametrizable

[class] ParametrizableAdapter:
abstract, see AbstractParametrizable


{RandomFactory.i}
[class] RandomFactory:
abstract, see Uniform01K


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



{SimpleDiscreteDistribution.i}
[class] SimpleDiscreteDistribution:
note: known bug in getDomain()--aborts
>>> import bpp
>>> map = bpp.doubleMap()
>>> map[.5] = .25
>>> map[1] = .75
>>> dist = bpp.SimpleDiscreteDistribution(map)
>>> [dist.rand()]
[...]


{StatTest.i}
[class] StatTest:
abstract, see seq/BowkerTest


{TestUnit.i}
[class] TestUnit:
>>> bpp.TestUnit().testEigen()
False

#M=
#2x2
#[
#[2.3, 1.4]
#[5, -0.9]
#]
#D=
#2x2
#[
#[3.79192, 0]
#[0, -2.39192]
#]
#V1=
#2x2
#[
#[0.684285, -0.330851]
#[0.729215, 1.10881]
#]
#V2=
#2x2
#[
#[1.10881, 0.330851]
#[-0.729215, 0.684285]
#]
#V1 . D . V2=
#2x2
#[
#[2.3, 1.4]
#[5, -0.9]
#]


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
<Swig Object of type 'int *' at 0x...>

#>>> bpp.intp.frompointer(x.getElement()).value()
#0


"""


import doctest
import bpp
doctest.testmod(optionflags = 8)
