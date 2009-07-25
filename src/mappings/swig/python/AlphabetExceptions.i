%module bpptest
%{
#include "AlphabetExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"
%include "std_vector.i"
using namespace std;

class Alphabet;
class AlphabetException:public Exception
{
  public:
    AlphabetException(const string & text, const Alphabet * alpha = NULL);
    virtual ~AlphabetException() throw ();

    virtual const Alphabet * getAlphabet() const;
};

class BadCharException:public AlphabetException
{
  public:
    BadCharException(const string & badChar, const string & text = "", const Alphabet * alpha = NULL);
    virtual ~BadCharException() throw();

    virtual string getBadChar() const;
};

class BadIntException:public AlphabetException
{
  public:
    BadIntException(int badInt, const string & text = "", const Alphabet * alpha = NULL);
    virtual ~BadIntException() throw();

    virtual int getBadInt() const;
};


class AlphabetMismatchException : public Exception
{
  public:
    AlphabetMismatchException(const char * text = "", const Alphabet * alpha1 = NULL, const Alphabet * alpha2 = NULL);
    %rename (charAlphabetMismatchException) AlphabetMismatchException(const char * text = "", const Alphabet * alpha1 = NULL, const Alphabet * alpha2 = NULL);
    AlphabetMismatchException(const string & text = "", const Alphabet * alpha1 = NULL, const Alphabet * alpha2 = NULL);
    virtual ~AlphabetMismatchException() throw();

    vector<const Alphabet *> getAlphabets() const;
};

class CharStateNotSupportedException : public AlphabetException
{
  public:
    CharStateNotSupportedException(const string & text = "", const Alphabet * alpha = NULL);
    virtual ~CharStateNotSupportedException() throw();
};
