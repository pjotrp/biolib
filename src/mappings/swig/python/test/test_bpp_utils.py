"""

{ApplicationTools.i}
[class] ApplicationTools:
>>> m = bpp.strMap()
>>> m['xxx'] = '1'
>>> m['yyy'] = '2.5'
>>> bpp.ApplicationTools.parameterExists("xxx", m)
True
>>> bpp.ApplicationTools.parameterExists("zzz", m)
False
>>> bpp.ApplicationTools.getDoubleParameter("xxx", m, 0.0)
1.0
>>> bpp.ApplicationTools.getDoubleParameter("yyy", m, 0.0)
2.5
>>> bpp.ApplicationTools.getIntParameter("xxx", m, 0)
1
>>> bpp.ApplicationTools.getIntParameter("yyy", m, 0)
2
>>> bpp.ApplicationTools.getIntParameter("zzz", m, 99)
WARNING!!! Parameter zzz not specified. Default used instead: 99
99
>>> bpp.ApplicationTools.getStringParameter("xxx", m, "zip")
'1'
>>> bpp.ApplicationTools.getStringParameter("yyy", m, "zip")
'2.5'
>>> bpp.ApplicationTools.getStringParameter("zzz", m, "zip")
WARNING!!! Parameter zzz not specified. Default used instead: zip
'zip'
>>> bpp.ApplicationTools.getBooleanParameter("xxx", m, False)
True
>>> bpp.ApplicationTools.getBooleanParameter("yyy", m, False)
False
>>> bpp.ApplicationTools.getBooleanParameter("zzz", m, False)
WARNING!!! Parameter zzz not specified. Default used instead: 0
False

>>> bpp.ApplicationTools.getParameter("xxx", m, 616)
1
>>> bpp.ApplicationTools.getParameter("xxx", m, 616.0)
1.0
>>> bpp.ApplicationTools.getParameter("xxx", m, 'stringy')
'1'
>>> bpp.ApplicationTools.getParameter("xxx", m, False)
1

>>> m = bpp.strMap()
>>> m['one'] = 'fake file'
>>> m['two'] = '..'
>>> bpp.ApplicationTools.getAFilePath("one", m)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
bpp.Exception: <bpp.Exception; proxy of <Swig Object of type 'Exception *' at 0x...> >
>>> bpp.ApplicationTools.getAFilePath("two", m)
'..'

>>> bpp.ApplicationTools.displayResult("The answer is", 1)
The answer is..........................: 1
>>> bpp.ApplicationTools.displayResult("The answer is", 1.0)
The answer is..........................: 1
>>> bpp.ApplicationTools.displayResult("The answer is", "result")
The answer is..........................: result
>>> bpp.ApplicationTools.displayResult("The answer is", True)
The answer is..........................: 1
>>> bpp.ApplicationTools.displayResult("The answer is", False)
The answer is..........................: 0

>>> m = bpp.strMap()
>>> m['xxx'] = '1.5,2.5'
>>> m['yyy'] = '1,2,3'
>>> bpp.ApplicationTools.getIntVectorParameter('xxx', m, ',', '5')
(1, 2)
>>> bpp.ApplicationTools.getIntVectorParameter('yyy', m, ',', '5')
(1, 2, 3)
>>> bpp.ApplicationTools.getIntVectorParameter('zzz', m, ',', '5')
WARNING!!! Parameter zzz not specified. Default used instead: 5
(5,)
>>> bpp.ApplicationTools.getDoubleVectorParameter('xxx', m, ',', '5')
(1.5, 2.5)
>>> bpp.ApplicationTools.getDoubleVectorParameter('yyy', m, ',', '5')
(1.0, 2.0, 3.0)
>>> bpp.ApplicationTools.getDoubleVectorParameter('zzz', m, ',', '5')
WARNING!!! Parameter zzz not specified. Default used instead: 5
(5.0,)

>>> bpp.ApplicationTools.displayMessage("hello")
hello
>>> bpp.ApplicationTools.displayError("hello")
ERROR!!! hello
>>> bpp.ApplicationTools.displayWarning("hello")
WARNING!!! hello
>>> bpp.ApplicationTools.displayTask("hello", True)
hello..................................: 
>>> bpp.ApplicationTools.displayTaskDone()
Done.
>>> bpp.ApplicationTools.startTimer()
>>> bpp.ApplicationTools.displayTime("hello")
hello 0d, 0h, 0m, 0s.
>>> bpp.ApplicationTools.getTime()
0.0
>>> bpp.ApplicationTools.displayGauge(23, 50)
[>>>>>>>>>>>>>>>>>                     ]  46%
>>> bpp.ApplicationTools.displayGauge(29, 50, '*')
[**********************                ]  58%
>>> bpp.ApplicationTools.displayGauge(49, 50, '*', "time's running out")
time's running out[************************************* ]  98%


{AttributesTools.i}
[class] AttributesTools:
>>> l = ["first is ignored","a=b","x=y"]
>>> bpp.AttributesTools.getVector(3,l)
('', 'a=b', 'x=y')

>>> v = bpp.strVector()
>>> v.append("a=b")
>>> v.append("x=y")
>>> m = bpp.AttributesTools.getAttributesMap(v)
>>> m.keys()
['a', 'x']
>>> m['a']
'b'
>>> m['x']
'y'
>>> n = bpp.strMap()
>>> bpp.AttributesTools.getAttributesMap(v,n)
>>> n.keys()
['a', 'x']

>>> m = bpp.AttributesTools.getAttributesMapFromFile("file","=")
Parsing file file for options.
>>> m.keys()
['c', 's']
>>> m['c']
'd'
>>> m['s']
't'
>>> n = bpp.strMap()
>>> bpp.AttributesTools.getAttributesMapFromFile("file",n,"=")
Parsing file file for options.
>>> n.keys()
['c', 's']

>>> m=bpp.strMap()
>>> n=bpp.strMap()
>>> m['a'] = 'b'
>>> m['x'] = 'y'
>>> n['a'] = 'B'
>>> n['s'] = 't'
>>> bpp.AttributesTools.actualizeAttributesMap(m,n)
>>> m.keys()
['a', 's', 'x']
>>> m.values()
['B', 't', 'y']

>>> m = bpp.strMap()
>>> m['a'] = '$(b)'
>>> m['b'] = 'c'
>>> m.items()
[('a', '$(b)'), ('b', 'c')]
>>> bpp.AttributesTools.resolveVariables(m)
>>> m.items()
[('a', 'c'), ('b', 'c')]

>>> l = ["1st ignored","a=b","x=y","param=file"]
>>> m = bpp.AttributesTools.parseOptions(4,l)
Parsing file file for options.
>>> m.items()
[('a', 'b'), ('c', 'd'), ('s', 't'), ('x', 'y')]


{BppVector.i}
[class] BppVector:
>>> bpp.intVector()
<bpp.intVector; proxy of <Swig Object of type 'std::vector< int > *' at 0x...> >
>>> bpp.doubleVector()
<bpp.doubleVector; proxy of <Swig Object of type 'std::vector< double > *' at 0x...> >



{ColorManager.i}
[class] XFigColorManager:
>>> cm = bpp.XFigColorManager()
>>> cm.getCodes()
(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
>>> cm.getColors()
(<bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >)
>>> i = bpp.uintp()
>>> i.assign(30)
>>> c = cm.getColor(i)
>>> cm.getCode(c)
30
>>> c
<bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >
>>> c.toString()
'[R255,G223,B222]'


{ColorTools.i}
[class] ColorTools:
>>> bpp.ColorTools.RED.toHex()
'#FF0000'
>>> bpp.ColorTools.ORANGE.toHex()
'#FF7F00'
>>> bpp.ColorTools.YELLOW.toHex()
'#FFFF00'
>>> bpp.ColorTools.GREEN.toHex()
'#00FF00'
>>> bpp.ColorTools.CYAN.toHex()
'#00FFFF'
>>> bpp.ColorTools.BLUE.toHex()
'#0000FF'
>>> bpp.ColorTools.MAGENTA.toHex()
'#FF00FF'
>>> bpp.ColorTools.BLACK.toHex()
'#000000'
>>> bpp.ColorTools.WHITE.toHex()
'#FFFFFF'
>>> bpp.ColorTools.gray(0.5).toHex()
'#808080'
>>> bpp.ColorTools.cmyk2rgb(0.5, 0.0, 0.1, 0.0).toHex()
'#80FFE6'

>>> bpp.ColorTools.gradient(5, bpp.ColorTools.BLACK, bpp.ColorTools.RED)
(<bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >)
>>> bpp.ColorTools.gradient(5, bpp.ColorTools.BLACK, bpp.ColorTools.RED)[3].toHex()
'#BF0000'
>>> bpp.ColorTools.gradient(5, bpp.ColorTools.BLACK, bpp.ColorTools.GREEN, bpp.ColorTools.RED)
(<bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >, <bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x...> >)


{DefaultColorSet.i}
[class] DefaultColorSet:
>>> cs = bpp.DefaultColorSet()
>>> cs.getNumberOfColors()
8
>>> cs.getColorNames()
('black', 'blue', 'cyan', 'green', 'magenta', 'red', 'white', 'yellow')
>>> cs.getColor('black')
<bpp.RGBColor; proxy of <Swig Object of type 'RGBColor *' at 0x98ede94> >
>>> cs.getColor('black').toHex()
'#000000'
>>> cs.getColor(5).toHex()
'#FF0000'


{DvipsColorSet.i}
[class] DvipsColorSet:
>>> cs = bpp.DvipsColorSet()
>>> cs.getNumberOfColors()
68
>>> cs.getColorNames()
('Apricot', 'Aquamarine', 'Bittersweet', 'Black', 'Blue', 'BlueGreen', 'BlueViolet', 'BrickRed', 'Brown', 'BurntOrange', 'CadetBlue', 'CarnationPink', 'Cerulean', 'CornflowerBlue', 'Cyan', 'Dandelion', 'DarkOrchid', 'Emerald', 'ForestGreen', 'Fuchsia', 'Goldenrod', 'Gray', 'Green', 'GreenYellow', 'JungleGreen', 'Lavender', 'LimeGreen', 'Magenta', 'Mahogany', 'Maroon', 'Melon', 'MidnightBlue', 'Mulberry', 'NavyBlue', 'OliveGreen', 'Orange', 'OrangeRed', 'Orchid', 'Peach', 'Periwinkle', 'PineGreen', 'Plum', 'ProcessBlue', 'Purple', 'RawSienna', 'Red', 'RedOrange', 'RedViolet', 'Rhodamine', 'RoyalBlue', 'RoyalPurple', 'RubineRed', 'Salmon', 'SeaGreen', 'Sepia', 'SkyBlue', 'SpringGreen', 'Tan', 'TealBlue', 'Thistle', 'Turquoise', 'Violet', 'VioletRed', 'White', 'WildStrawberry', 'Yellow', 'YellowGreen', 'YellowOrange')
>>> cs.getColor('Rhodamine').toHex()
'#FF2EFF'
>>> cs.getColor(21).toHex()
'#808080'


{Exceptions.i}
[class] Exception:
>>> x = bpp.Exception("except this!")
>>> x.what()
'except this!'

[class] IOException:
>>> x = bpp.IOException("IO is silly")
>>> x.what()
'IO is silly'

[class] NullPointerException:
>>> x = bpp.NullPointerException("nullishness")
>>> x.what()
'nullishness'

[class] ZeroDivisionException:
>>> x = bpp.ZeroDivisionException("ILLOGICAL!")
>>> x.what()
'ILLOGICAL!'

[class] BadIntegerException:
>>> x = bpp.BadIntegerException("Bad integer! No cookie!", -1)
>>> x.what()
'Bad integer! No cookie!(-1)'
>>> x.getBadInteger()
-1

[class] BadNumberException:
>>> x = bpp.BadNumberException("Numbers are bad!", 0.001)
>>> x.what()
'Numbers are bad!(0.001)'
>>> x.getBadNumber()
0.001

[class] NumberFormatException:
>>> s = bpp.stringp()
>>> s.assign("20X6")
>>> x = bpp.NumberFormatException("badly done", s)
>>> x.what()
'badly done(20X6)'

[class] IndexOutOfBoundsException:
>>> x = bpp.IndexOutOfBoundsException("out of bounds!", -1, 1, 10)
>>> x.what()
'out of [1, 10])out of bounds!(-1)'
>>> x.getBounds()
<Swig Object of type 'int *' at 0x...>


{FileTools.i}
[class] FileTools:
>>> bpp.FileTools.fileExists(".")
True
>>> bpp.FileTools.fileExists("asdf")
False
>>> bpp.FileTools.directoryExists("asdf")
False
>>> bpp.FileTools.directoryExists(".")
True
>>> bpp.FileTools.directoryExists("..")
True

This shouldn't be static
#>>> bpp.FileTools.getParent("xxx/yyy.zzz")
#'xxx'
>>> bpp.FileTools.getFileName("xxx/yyy.zzz")
'yyy'
>>> bpp.FileTools.getFileName("xxx\yyy.zzz", '\\\\')
'yyy'
>>> bpp.FileTools.getExtension("xxx/yyy.zzz")
'zzz'

>>> bpp.FileTools.putStreamIntoVectorOfStrings(bpp.ifstream("file"))
...
>>> stream = bpp.ifstream("file")
>>> bpp.FileTools.getNextLine(stream)
...


[class] Font:
>>> x = bpp.Font("default", "default", 12)
>>> y = x.clone()
>>> z = bpp.Font("default", "default", 13)
>>> x==y
True
>>> x==z
False
>>> x.getFamily()
'default'
>>> x.getSeries()
''
>>> x.getType()
'default'
>>> x.getSize()
12
>>> y.setFamily("family")
>>> y.setSeries("series")
>>> y.setType("type")
>>> y.setSize(24)
>>> y.toString()
'family/series/type/24'
>>> x==y
False


{FontManager.i}
[class] XFigLaTeXFontManager:
>>> fm = bpp.XFigLaTeXFontManager()
>>> fm
<bpp.XFigLaTeXFontManager; proxy of <Swig Object of type 'XFigLaTeXFontManager *' at 0x...> >
>>> fm.getFonts()
(<bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >)
>>> fm.getNumberOfFonts()
6
>>> fm.getCodes()
(0, 1, 2, 3, 4, 5)
>>> i = bpp.intp()
>>> i.assign(2)
>>> fm.getFont(i)
<bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >
>>> f = fm.getFont(i)
>>> fm.getCode(f)
2

[class] XFigPostscriptFontManager:
>>> fm = bpp.XFigPostscriptFontManager()
>>> fm
<bpp.XFigPostscriptFontManager; proxy of <Swig Object of type 'XFigPostscriptFontManager *' at 0x...> >
>>> fm.getFonts()
(<bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >, <bpp.Font; proxy of <Swig Object of type 'Font *' at 0x...> >)
>>> fm.getNumberOfFonts()
36
>>> fm.getCodes()
(-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34)
>>> f = fm.getFont(i)
>>> fm.getCode(f)
2
>>> f.toString()
'Times//Bold/12'


{IOFormat.i}
[class] IOFormat
>>> gb = bpp.GenBank()
>>> gb.getFormatName()
'GenBank file'
>>> gb.getFormatDescription()
'Sequences following the GenBank data base format.'
>>> gb.getDataType()
'Sequence container'


{KeyvalTools.i}
[class] KeyvalTools:
x = bpp.KeyvalException("bad keyval thingy")
>>> x.what()
'bad keyval thingy'

>>> x = bpp.strp()
>>> y = bpp.strp()
>>> bpp.KeyvalTools.singleKeyval("a=b",x,y)
>>> x.value()
'a'
>>> y.value()
'b'

>>> m = bpp.strMap()
>>> bpp.KeyvalTools.multipleKeyvals("a=b,c=d",m)
>>> m['a']
'b'
>>> m['c']
'd'

>>> bpp.KeyvalTools.parseProcedure("func(a=b,c=d)",x,m)
>>> x.value()
'func'
>>> m['a']
'b'
>>> m['c']
'd'


{MapTools.i}
[class] MapTools:
>>> m = bpp.intMap()
>>> m[0] = 1
>>> m[5] = 10
>>> bpp.MapTools.getIntKeys(m)
(0, 5)
>>> bpp.MapTools.getIntValues(m)
(1, 10)

>>> n = bpp.strMap()
>>> n["hello"] = "there"
>>> n["yippy"] = "skippy"
>>> bpp.MapTools.getStrKeys(n)
('hello', 'yippy')
>>> bpp.MapTools.getStrValues(n)
('there', 'skippy')


{MolscriptColorSet.i}
[class] MolscriptColorSet:
>>> cs = bpp.MolscriptColorSet()
>>> cs.getNumberOfColors()
164
>>> cs.getColorNames()
('aliceblue', 'antiquewhite', 'aquamarine', 'azure', 'beige', 'bisque', 'black', 'blanchedalmond', 'blue', 'blueviolet', 'brown', 'burlywood', 'cadetblue', 'chartreuse', 'chocolate', 'coral', 'cornflowerblue', 'cornsilk', 'crimson', 'cyan', 'darkblue', 'darkcyan', 'darkgoldenrod', 'darkgray', 'darkgreen', 'darkgrey', 'darkkhaki', 'darkmagenta', 'darkolivegreen', 'darkorange', 'darkorchid', 'darkred', 'darksalmon', 'darkseagreen', 'darkslateblue', 'darkslategray', 'darkslategrey', 'darkturquoise', 'darkviolet', 'deeppink', 'deepskyblue', 'dimgray', 'dimgrey', 'dodgerblue', 'firebrick', 'floralwhite', 'forestgreen', 'gainsboro', 'ghostwhite', 'gold', 'goldenrod', 'gray', 'green', 'greenyellow', 'grey', 'honeydew', 'hotpink', 'indianred', 'indigo', 'ivory', 'khaki', 'lavender', 'lavenderblush', 'lawngreen', 'lemonchiffon', 'lightblue', 'lightcoral', 'lightcyan', 'lightgoldenrod', 'lightgoldenrodyellow', 'lightgray', 'lightgreen', 'lightgrey', 'lightpink', 'lightsalmon', 'lightseagreen', 'lightskyblue', 'lightslateblue', 'lightslategray', 'lightslategrey', 'lightsteelblue', 'lightyellow', 'limegreen', 'linen', 'magenta', 'maroon', 'mediumaquamarine', 'mediumblue', 'mediumorchid', 'mediumpurple', 'mediumseagreen', 'mediumslateblue', 'mediumspringgreen', 'mediumturquoise', 'mediumvioletred', 'midnightblue', 'mintcream', 'mistyrose', 'moccasin', 'navajowhite', 'navy', 'navyblue', 'oldlace', 'olivedrab', 'orange', 'orangered', 'orchid', 'palegoldenrod', 'palegreen', 'paleturquoise', 'palevioletred', 'papayawhip', 'peachpuff', 'peru', 'pink', 'plum', 'powderblue', 'purple', 'red', 'rosybrown', 'royalblue', 'saddlebrown', 'salmon', 'sandybrown', 'seagreen', 'seashell', 'sgibeet', 'sgibrightgray', 'sgibrightgrey', 'sgichartreuse', 'sgidarkgray', 'sgidarkgrey', 'sgilightblue', 'sgilightgray', 'sgilightgrey', 'sgimediumgray', 'sgimediumgrey', 'sgiolivedrab', 'sgisalmon', 'sgislateblue', 'sgiteal', 'sgiverydarkgray', 'sgiverydarkgrey', 'sgiverylightgray', 'sgiverylightgrey', 'sienna', 'skyblue', 'slateblue', 'slategray', 'slategrey', 'snow', 'springgreen', 'steelblue', 'tan', 'thistle', 'tomato', 'turquoise', 'violet', 'violetred', 'wheat', 'white', 'whitesmoke', 'yellow', 'yellowgreen')
>>> cs.getColor('aliceblue').toHex()
'#F0F8FF'
>>> cs.getColor(100).toHex()
'#000080'


{Number.i}
[class] Number:
>>> x = bpp.intNumber(5)
>>> x.getValue()
5
>>> x.clone()
<bpp.intNumber; proxy of <Swig Object of type 'Number< int > *' at 0x...> >

>>> y = bpp.doubleNumber(5)
>>> y.getValue()
5.0


{PGFGraphicDevice.i}
[class] PGFGraphicDevice:
>>> stream = bpp.ApplicationTools.getMessage()
>>> gd = bpp.PGFGraphicDevice(stream, 2.0)
>>> gd.beginDocument()
>>> gd.setCurrentForegroundColor(bpp.ColorTools.RED)
>>> gd.setCurrentBackgroundColor(bpp.ColorTools.BLUE)
>>> gd.setCurrentFont(bpp.Font())
>>> gd.setCurrentPointSize(1)
>>> gd.setCurrentLineType(gd.LINE_DASHED)
>>> gd.setCurrentLayer(0)
>>> gd.drawLine(5.0, 0.0, 1.7, 2.0)
>>> gd.drawRect(10.0, 20.0, 5.0, 10.0)
>>> gd.drawCircle(10.0, 10.0, 7.5)
>>> gd.drawText(5.0, 15.0, "Hiya!")
>>> gd.comment("this is a comment")
>>> gd.endDocument()
\documentclass{article}
% This figure was generated by the Bio++ PGF Graphic Device.
% Althought this file can be compiled 'as is' it may not be displayed correctly, depending on the size of the picture.
% You may consider copying the pgfpicture environment to your own LaTeX file and play with pgf settings (e.g. the pgfpages module).
\usepackage{pgf}
\definecolor{usercolor2}{rgb}{0,0,1}
\definecolor{usercolor1}{rgb}{1,0,0}
\begin{document}
\pgfdeclarelayer{0}
\pgfsetlayers{0}
\begin{pgfpicture}
\pgfsetxvec{\pgfpoint{2cm}{0cm}}
\pgfsetyvec{\pgfpoint{0cm}{-2cm}}
\pgfsetstrokecolor{usercolor1}

\pgfsetfillcolor{usercolor2}

\fontfamily{default}
\fontshape{}
\fontsize{12}{12}
\selectfont

\pgfsetlinewidth{2}

\pgfsetdash{{3mm}{2mm}}{0pt}

\begin{pgfonlayer}{0}
\pgfsetstrokecolor{usercolor1}
\pgfsetfillcolor{usercolor2}

\pgfpathmoveto{\pgfpointxy{5}{0}}
\pgfpathlineto{\pgfpointxy{1.7}{2}}
\pgfpathclose
\pgfusepath{stroke}

\pgfpathrectangle{\pgfpointxy{10}{20}}{\pgfpointxy{5}{10}}
\pgfusepath{stroke}

\pgfpathcircle{\pgfpointxy{10}{10}}{7.5}
\pgfusepath{stroke}

\pgftransformrotate{0}
\pgftext[bottom,left,at=\pgfpointxy{5}{15}]{\textcolor{usercolor1}Hiya!}

%this is a comment
\end{pgfonlayer}{0}

\end{pgfpicture}
\end{document}


{RColorSet.i}
[class] RColorSet:
>>> cs = bpp.RColorSet()
>>> cs.getNumberOfColors()
657
>>> cs.getColorNames()
('aliceblue', 'antiquewhite', 'antiquewhite1', 'antiquewhite2', 'antiquewhite3', 'antiquewhite4', 'aquamarine', 'aquamarine1', 'aquamarine2', 'aquamarine3', 'aquamarine4', 'azure', 'azure1', 'azure2', 'azure3', 'azure4', 'beige', 'bisque', 'bisque1', 'bisque2', 'bisque3', 'bisque4', 'black', 'blanchedalmond', 'blue', 'blue1', 'blue2', 'blue3', 'blue4', 'blueviolet', 'brown', 'brown1', 'brown2', 'brown3', 'brown4', 'burlywood', 'burlywood1', 'burlywood2', 'burlywood3', 'burlywood4', 'cadetblue', 'cadetblue1', 'cadetblue2', 'cadetblue3', 'cadetblue4', 'chartreuse', 'chartreuse1', 'chartreuse2', 'chartreuse3', 'chartreuse4', 'chocolate', 'chocolate1', 'chocolate2', 'chocolate3', 'chocolate4', 'coral', 'coral1', 'coral2', 'coral3', 'coral4', 'cornflowerblue', 'cornsilk', 'cornsilk1', 'cornsilk2', 'cornsilk3', 'cornsilk4', 'cyan', 'cyan1', 'cyan2', 'cyan3', 'cyan4', 'darkblue', 'darkcyan', 'darkgoldenrod', 'darkgoldenrod1', 'darkgoldenrod2', 'darkgoldenrod3', 'darkgoldenrod4', 'darkgray', 'darkgreen', 'darkgrey', 'darkkhaki', 'darkmagenta', 'darkolivegreen', 'darkolivegreen1', 'darkolivegreen2', 'darkolivegreen3', 'darkolivegreen4', 'darkorange', 'darkorange1', 'darkorange2', 'darkorange3', 'darkorange4', 'darkorchid', 'darkorchid1', 'darkorchid2', 'darkorchid3', 'darkorchid4', 'darkred', 'darksalmon', 'darkseagreen', 'darkseagreen1', 'darkseagreen2', 'darkseagreen3', 'darkseagreen4', 'darkslateblue', 'darkslategray', 'darkslategray1', 'darkslategray2', 'darkslategray3', 'darkslategray4', 'darkslategrey', 'darkturquoise', 'darkviolet', 'deeppink', 'deeppink1', 'deeppink2', 'deeppink3', 'deeppink4', 'deepskyblue', 'deepskyblue1', 'deepskyblue2', 'deepskyblue3', 'deepskyblue4', 'dimgray', 'dimgrey', 'dodgerblue', 'dodgerblue1', 'dodgerblue2', 'dodgerblue3', 'dodgerblue4', 'firebrick', 'firebrick1', 'firebrick2', 'firebrick3', 'firebrick4', 'floralwhite', 'forestgreen', 'gainsboro', 'ghostwhite', 'gold', 'gold1', 'gold2', 'gold3', 'gold4', 'goldenrod', 'goldenrod1', 'goldenrod2', 'goldenrod3', 'goldenrod4', 'gray', 'gray0', 'gray1', 'gray10', 'gray100', 'gray11', 'gray12', 'gray13', 'gray14', 'gray15', 'gray16', 'gray17', 'gray18', 'gray19', 'gray2', 'gray20', 'gray21', 'gray22', 'gray23', 'gray24', 'gray25', 'gray26', 'gray27', 'gray28', 'gray29', 'gray3', 'gray30', 'gray31', 'gray32', 'gray33', 'gray34', 'gray35', 'gray36', 'gray37', 'gray38', 'gray39', 'gray4', 'gray40', 'gray41', 'gray42', 'gray43', 'gray44', 'gray45', 'gray46', 'gray47', 'gray48', 'gray49', 'gray5', 'gray50', 'gray51', 'gray52', 'gray53', 'gray54', 'gray55', 'gray56', 'gray57', 'gray58', 'gray59', 'gray6', 'gray60', 'gray61', 'gray62', 'gray63', 'gray64', 'gray65', 'gray66', 'gray67', 'gray68', 'gray69', 'gray7', 'gray70', 'gray71', 'gray72', 'gray73', 'gray74', 'gray75', 'gray76', 'gray77', 'gray78', 'gray79', 'gray8', 'gray80', 'gray81', 'gray82', 'gray83', 'gray84', 'gray85', 'gray86', 'gray87', 'gray88', 'gray89', 'gray9', 'gray90', 'gray91', 'gray92', 'gray93', 'gray94', 'gray95', 'gray96', 'gray97', 'gray98', 'gray99', 'green', 'green1', 'green2', 'green3', 'green4', 'greenyellow', 'grey', 'grey0', 'grey1', 'grey10', 'grey100', 'grey11', 'grey12', 'grey13', 'grey14', 'grey15', 'grey16', 'grey17', 'grey18', 'grey19', 'grey2', 'grey20', 'grey21', 'grey22', 'grey23', 'grey24', 'grey25', 'grey26', 'grey27', 'grey28', 'grey29', 'grey3', 'grey30', 'grey31', 'grey32', 'grey33', 'grey34', 'grey35', 'grey36', 'grey37', 'grey38', 'grey39', 'grey4', 'grey40', 'grey41', 'grey42', 'grey43', 'grey44', 'grey45', 'grey46', 'grey47', 'grey48', 'grey49', 'grey5', 'grey50', 'grey51', 'grey52', 'grey53', 'grey54', 'grey55', 'grey56', 'grey57', 'grey58', 'grey59', 'grey6', 'grey60', 'grey61', 'grey62', 'grey63', 'grey64', 'grey65', 'grey66', 'grey67', 'grey68', 'grey69', 'grey7', 'grey70', 'grey71', 'grey72', 'grey73', 'grey74', 'grey75', 'grey76', 'grey77', 'grey78', 'grey79', 'grey8', 'grey80', 'grey81', 'grey82', 'grey83', 'grey84', 'grey85', 'grey86', 'grey87', 'grey88', 'grey89', 'grey9', 'grey90', 'grey91', 'grey92', 'grey93', 'grey94', 'grey95', 'grey96', 'grey97', 'grey98', 'grey99', 'honeydew', 'honeydew1', 'honeydew2', 'honeydew3', 'honeydew4', 'hotpink', 'hotpink1', 'hotpink2', 'hotpink3', 'hotpink4', 'indianred', 'indianred1', 'indianred2', 'indianred3', 'indianred4', 'ivory', 'ivory1', 'ivory2', 'ivory3', 'ivory4', 'khaki', 'khaki1', 'khaki2', 'khaki3', 'khaki4', 'lavender', 'lavenderblush', 'lavenderblush1', 'lavenderblush2', 'lavenderblush3', 'lavenderblush4', 'lawngreen', 'lemonchiffon', 'lemonchiffon1', 'lemonchiffon2', 'lemonchiffon3', 'lemonchiffon4', 'lightblue', 'lightblue1', 'lightblue2', 'lightblue3', 'lightblue4', 'lightcoral', 'lightcyan', 'lightcyan1', 'lightcyan2', 'lightcyan3', 'lightcyan4', 'lightgoldenrod', 'lightgoldenrod1', 'lightgoldenrod2', 'lightgoldenrod3', 'lightgoldenrod4', 'lightgoldenrodyellow', 'lightgray', 'lightgreen', 'lightgrey', 'lightpink', 'lightpink1', 'lightpink2', 'lightpink3', 'lightpink4', 'lightsalmon', 'lightsalmon1', 'lightsalmon2', 'lightsalmon3', 'lightsalmon4', 'lightseagreen', 'lightskyblue', 'lightskyblue1', 'lightskyblue2', 'lightskyblue3', 'lightskyblue4', 'lightslateblue', 'lightslategray', 'lightslategrey', 'lightsteelblue', 'lightsteelblue1', 'lightsteelblue2', 'lightsteelblue3', 'lightsteelblue4', 'lightyellow', 'lightyellow1', 'lightyellow2', 'lightyellow3', 'lightyellow4', 'limegreen', 'linen', 'magenta', 'magenta1', 'magenta2', 'magenta3', 'magenta4', 'maroon', 'maroon1', 'maroon2', 'maroon3', 'maroon4', 'mediumaquamarine', 'mediumblue', 'mediumorchid', 'mediumorchid1', 'mediumorchid2', 'mediumorchid3', 'mediumorchid4', 'mediumpurple', 'mediumpurple1', 'mediumpurple2', 'mediumpurple3', 'mediumpurple4', 'mediumseagreen', 'mediumslateblue', 'mediumspringgreen', 'mediumturquoise', 'mediumvioletred', 'midnightblue', 'mintcream', 'mistyrose', 'mistyrose1', 'mistyrose2', 'mistyrose3', 'mistyrose4', 'moccasin', 'navajowhite', 'navajowhite1', 'navajowhite2', 'navajowhite3', 'navajowhite4', 'navy', 'navyblue', 'oldlace', 'olivedrab', 'olivedrab1', 'olivedrab2', 'olivedrab3', 'olivedrab4', 'orange', 'orange1', 'orange2', 'orange3', 'orange4', 'orangered', 'orangered1', 'orangered2', 'orangered3', 'orangered4', 'orchid', 'orchid1', 'orchid2', 'orchid3', 'orchid4', 'palegoldenrod', 'palegreen', 'palegreen1', 'palegreen2', 'palegreen3', 'palegreen4', 'paleturquoise', 'paleturquoise1', 'paleturquoise2', 'paleturquoise3', 'paleturquoise4', 'palevioletred', 'palevioletred1', 'palevioletred2', 'palevioletred3', 'palevioletred4', 'papayawhip', 'peachpuff', 'peachpuff1', 'peachpuff2', 'peachpuff3', 'peachpuff4', 'peru', 'pink', 'pink1', 'pink2', 'pink3', 'pink4', 'plum', 'plum1', 'plum2', 'plum3', 'plum4', 'powderblue', 'purple', 'purple1', 'purple2', 'purple3', 'purple4', 'red', 'red1', 'red2', 'red3', 'red4', 'rosybrown', 'rosybrown1', 'rosybrown2', 'rosybrown3', 'rosybrown4', 'royalblue', 'royalblue1', 'royalblue2', 'royalblue3', 'royalblue4', 'saddlebrown', 'salmon', 'salmon1', 'salmon2', 'salmon3', 'salmon4', 'sandybrown', 'seagreen', 'seagreen1', 'seagreen2', 'seagreen3', 'seagreen4', 'seashell', 'seashell1', 'seashell2', 'seashell3', 'seashell4', 'sienna', 'sienna1', 'sienna2', 'sienna3', 'sienna4', 'skyblue', 'skyblue1', 'skyblue2', 'skyblue3', 'skyblue4', 'slateblue', 'slateblue1', 'slateblue2', 'slateblue3', 'slateblue4', 'slategray', 'slategray1', 'slategray2', 'slategray3', 'slategray4', 'slategrey', 'snow', 'snow1', 'snow2', 'snow3', 'snow4', 'springgreen', 'springgreen1', 'springgreen2', 'springgreen3', 'springgreen4', 'steelblue', 'steelblue1', 'steelblue2', 'steelblue3', 'steelblue4', 'tan', 'tan1', 'tan2', 'tan3', 'tan4', 'thistle', 'thistle1', 'thistle2', 'thistle3', 'thistle4', 'tomato', 'tomato1', 'tomato2', 'tomato3', 'tomato4', 'turquoise', 'turquoise1', 'turquoise2', 'turquoise3', 'turquoise4', 'violet', 'violetred', 'violetred1', 'violetred2', 'violetred3', 'violetred4', 'wheat', 'wheat1', 'wheat2', 'wheat3', 'wheat4', 'white', 'whitesmoke', 'yellow', 'yellow1', 'yellow2', 'yellow3', 'yellow4', 'yellowgreen')
>>> cs.getColor('aliceblue').toHex()
'#F0F8FF'
>>> cs.getColor(200).toHex()
'#858585'


{RGBColor.i}
[class] RGBColor:
>>> x = bpp.RGBColor()
>>> x.toHex()
'#000000'
>>> y = bpp.RGBColor(10,20,30)
>>> y.toString()
'[R10,G20,B30]'
>>> z = bpp.RGBColor(0,0,0)
>>> x==z
True
>>> x==y
False
>>> x < z
False
>>> x < y
True
>>> bpp.uintp.frompointer(y.__aref__(0)).value()
10


{StringTokenizer.i}
[class] StringTokenizer:
>>> st = bpp.StringTokenizer("Hi there! How are you?")
>>> st.getToken(0)
'Hi'
>>> st.getToken(1)
'there!'
>>> st.getToken(2)
'How'
>>> st.getTokens()
('Hi', 'there!', 'How', 'are', 'you?')
>>> st.getToken(2)
'How'
>>> st.nextToken()
'Hi'
>>> st.nextToken()
'there!'
>>> st.numberOfRemainingTokens()
3
>>> st.hasMoreToken()
True


{SVGGraphicDevice.i}
[class] SVGGraphicDevice:
>>> stream = bpp.ApplicationTools.getMessage()
>>> gd = bpp.SVGGraphicDevice(stream)
>>> gd.beginDocument()
>>> gd.setCurrentForegroundColor(bpp.ColorTools.RED)
>>> gd.setCurrentBackgroundColor(bpp.ColorTools.BLUE)
>>> gd.setCurrentFont(bpp.Font())
>>> gd.setCurrentPointSize(1)
>>> gd.setCurrentLineType(gd.LINE_DASHED)
>>> gd.setCurrentLayer(0)
>>> gd.drawLine(5.0, 0.0, 1.7, 2.0)
>>> gd.drawRect(10.0, 20.0, 5.0, 10.0)
>>> gd.drawCircle(10.0, 10.0, 7.5)
>>> gd.drawText(5.0, 15.0, "Hiya!")
>>> gd.endDocument()
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg width="100%" height="100%" version="1.1"
 xmlns="http://www.w3.org/2000/svg"
 >
<g id="layer0" >
<line x1="5" y1="0" x2="1.7" y2="2" style="stroke:rgb(255,0,0);stroke-width:1;stroke-dasharray:4,4" />
<rect x="10" y="20" width="5" height="10" style="stroke:rgb(255,0,0);stroke-width:1" />
<rect cx="10" cy="10" cr="7.5" style="stroke:rgb(255,0,0);stroke-width:1" />
<text x="5" y="15" rotate="0" style="font-family:default;font-style:;font-size:12px;dominant-baseline:before-edge;text-anchor:start;fill:rgb(255,0,0)" >Hiya!</text>
</g>
</svg>
>>> bpp.SVGGraphicDevice.colorToText(bpp.ColorTools.CYAN)
'rgb(0,255,255)'


{TextTools.i}
[class] TextTools:
>>> bpp.TextTools.isEmpty("")
True
>>> bpp.TextTools.isEmpty("a")
False

>>> bpp.TextTools.toUpper('aBc DeF')
'ABC DEF'

>>> bpp.TextTools.toLower('aBc DeF')
'abc def'

>>> bpp.TextTools.isWhiteSpaceCharacter(" ")
True
>>> bpp.TextTools.isWhiteSpaceCharacter("a")
False
>>> bpp.TextTools.isWhiteSpaceCharacter("  ")
Traceback (most recent call last):
...
TypeError: in method 'TextTools_isWhiteSpaceCharacter', argument 1 of type 'char'

>>> bpp.TextTools.removeWhiteSpaces(" icky bicky beebop ")
'ickybickybeebop'
>>> bpp.TextTools.removeFirstWhiteSpaces(" icky bicky beebop ")
'icky bicky beebop '
>>> bpp.TextTools.removeLastWhiteSpaces(" icky bicky beebop ")
' icky bicky beebop'
>>> bpp.TextTools.removeSurroundingWhiteSpaces(" icky bicky beebop ")
'icky bicky beebop'

>>> bpp.TextTools.isNewLineCharacter("\\n")
True
>>> bpp.TextTools.isNewLineCharacter("x")
False
>>> bpp.TextTools.removeNewLines("hello\\nthere\\nwoohoo\\n")
'hellotherewoohoo'
>>> bpp.TextTools.removeLastNewLines("hello\\nthere\\nwoohoo\\n")
'hello\\nthere\\nwoohoo'

>>> bpp.TextTools.isDecimalNumber("9")
True
>>> bpp.TextTools.isDecimalNumber("x")
False
>>> bpp.TextTools.isDecimalNumber("987.6")
True
>>> bpp.TextTools.isDecimalNumber("987.6","~")
False
>>> bpp.TextTools.isDecimalNumber("987~6","~")
True

>>> bpp.TextTools.toString(5);
'5'
>>> bpp.TextTools.toString(-340);
'-340'
>>> bpp.TextTools.toString('5');
'5'
>>> bpp.TextTools.toString(5.1234567);
'5.12346'
>>> bpp.TextTools.toInt('5.1234567');
5
>>> bpp.TextTools.toDouble('5.25');
5.25

>>> bpp.TextTools.resizeRight("abc", 6)
'abc   '
>>> bpp.TextTools.resizeLeft("abc", 6, "!")
'!!!abc'

>>> bpp.TextTools.removeSubstrings("one fish", 'n', 'i')
'osh'

>>> bpp.TextTools.removeChar("fffishyf", 'f')
'ishy'
>>> bpp.TextTools.count("fififishyf", 'fi')
3

>>> bpp.TextTools.startsWith("fishy", "zz")
False
>>> bpp.TextTools.startsWith("fishy", "fi")
True
>>> bpp.TextTools.endsWith("fishy", "zz")
False
>>> bpp.TextTools.endsWith("fishy", "shy")
True

>>> bpp.TextTools.split("abcdef", 2)
('ab', 'cd', 'ef')

>>> bpp.TextTools.intToString(51)
'51'
>>> bpp.TextTools.intFromString("51")
51
>>> bpp.TextTools.intTo("51")
51

>>> bpp.TextTools.doubleToString(51.5)
'51.5'
>>> bpp.TextTools.doubleToString(51.5555555, 5)
'51.556'
>>> bpp.TextTools.doubleFromString("51.5")
51.5
>>> bpp.TextTools.doubleTo("51.5")
51.5

>>> bpp.TextTools.charToString('X')
'X'
>>> bpp.TextTools.charFromString("X")
'X'
>>> bpp.TextTools.charTo("X")
'X'


{XFigGraphicDevice.i}
[class] XFigGraphicDevice:
>>> stream = bpp.ApplicationTools.getMessage()
>>> gd = bpp.XFigGraphicDevice(stream)
>>> gd.beginDocument()
>>> gd.setCurrentForegroundColor(bpp.ColorTools.RED)
>>> gd.setCurrentBackgroundColor(bpp.ColorTools.BLUE)
>>> gd.setCurrentFont(bpp.XFigPostscriptFontManager().getFonts()[1])
>>> gd.setCurrentPointSize(1)
>>> gd.setCurrentLineType(gd.LINE_DASHED)
>>> gd.setCurrentLayer(0)
>>> gd.drawLine(5.0, 0.0, 1.7, 2.0)
>>> gd.drawRect(10.0, 20.0, 5.0, 10.0)
>>> gd.drawCircle(10.0, 10.0, 7.5)
>>> gd.drawText(5.0, 15.0, "Hiya!")
>>> gd.endDocument()
#FIG 3.2 Produced by TreeMap version 0.1
Portrait
Flush left
Metric
A4
100
Single
0
72 2
#Color definitions:
2 1 1 1 4 1 0 -1 -1 -1 0 0 0 0 0 2
5 0
1.7 2
2 2 0 1 4 1 0 -1 -1 -1 0 0 0 0 0 5
10 20
15 20
15 30
10 30
10 20
1 3 0 1 4 1 0 -1 -1 -1 1 0 10 10 7.5 7.5 17.5 10 17.5 10

4 0 4 50 -1 0 12 0 4 -1 -1 5 14 Hiya!\001
"""


import doctest
import bpp
doctest.testmod(optionflags = 8)
