%module bpptest
%{
#include "Clustal.h"
using namespace bpp;
%}
%include "AbstractISequence2.i"
%include "AlignedSequenceContainer.i"
%include "std_iostream.i"
using namespace std;

class Clustal:public virtual AbstractISequence2
{
  public:
    bool _checkNames;

    Clustal(bool checkNames = true): _checkNames(checkNames);
    virtual ~Clustal();

    void appendFromStream(istream & input, AlignedSequenceContainer & sc) const throw (Exception);
    const string getFormatName() const;
    const string getFormatDescription() const;
    bool checkNames() const;
    void checkNames(bool yn);
};
