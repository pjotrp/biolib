"""
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


3

"""
#>>> bpp.TextTools.split("abcd", 2)
#<Swig Object of type 'std::vector< std::string > *' at 0x...>
#<Swig Object of type 'std::vector< std::string >...
import doctest
import bpp
doctest.testmod()

#    static vector<string> split(const string & s, unsigned int n);
