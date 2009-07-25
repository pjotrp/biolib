%module bpptest
%{
#include "AbstractOSequence.h"
using namespace bpp;
%}
%include "VectorSequenceContainer.i"
%include "Alphabet.i"
%include "OSequence.i"
%include "std_string.i"
//#include <fstream>
using namespace std;

class AbstractOSequence:public virtual OSequence
{
  public: 
    AbstractOSequence();
    virtual ~AbstractOSequence();

    void write(ostream & output, const SequenceContainer & sc) const throw (Exception) = 0;
    void write(const string & path, const SequenceContainer & sc, bool overwrite=true) const throw (Exception);
};
