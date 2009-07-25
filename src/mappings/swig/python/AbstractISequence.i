%module bpptest
%{
#include "AbstractISequence.h"
using namespace bpp;
%}
%include "VectorSequenceContainer.i"
%include "Alphabet.i"
%include "ISequence.i"
%include "std_string.i"
%include "std_iostream.i"
//#include <fstream>
using namespace std;

class AbstractISequence:public virtual ISequence
{
  public: 
    AbstractISequence();
    virtual ~AbstractISequence();

    virtual void read(istream & input, VectorSequenceContainer & sc) const throw (Exception);

    virtual void read(const string & path , VectorSequenceContainer & sc) const throw (Exception);

    virtual VectorSequenceContainer * read(istream & input, const Alphabet * alpha) const throw (Exception);

    virtual VectorSequenceContainer * read(const string & path , const Alphabet * alpha) const throw (Exception);

    readFromFile(const string & path , const Alphabet * alpha) const throw (Exception);
};
