%module bpptest
%{
#include "IOSequence.h"
using namespace bpp;
%}

%include "Exceptions.i"
%include "IOFormat.i"
%include "std_string.i"

using namespace std;

class IOSequence: public virtual IOFormat
{
  public:
    IOSequence();
    virtual ~IOSequence();

    const string getDataType() const;
};

