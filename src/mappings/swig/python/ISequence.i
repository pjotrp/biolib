%module bpptest
%{
#include "ISequence.h"
using namespace bpp;
%}
%include "IOSequence.i"
%include "Sequence.i"
%include "SequenceContainer.i"
%include "SiteContainer.i"
%include "Exceptions.i"
%include "std_iostream.i"
%include "std_string.i"
using namespace std;

class ISequence:public virtual IOSequence
{
  public:
    ISequence();
    virtual ~ISequence();

    virtual SequenceContainer * read(istream & input, const Alphabet * alpha) const throw (Exception) = 0;
    virtual SequenceContainer * read(const string & path, const Alphabet * alpha) const throw (Exception) = 0;
};

class ISequence2:public virtual ISequence
{
  public:
    ISequence2();
    virtual ~ISequence2();
    virtual SiteContainer * read(istream & input, const Alphabet * alpha) const throw (Exception) = 0;
    virtual SiteContainer * read(const string & path, const Alphabet * alpha) const throw (Exception) = 0;
};
