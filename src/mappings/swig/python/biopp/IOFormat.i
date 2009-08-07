%module bpp_ioformat
%{
#include "IOFormat.h"
using namespace bpp;
%}

%include "Exceptions.i"
%include "std_string.i"

using namespace std;

class IOFormat
{
  public:
    IOFormat();
    virtual ~IOFormat();

    virtual const string getDataType() const = 0;
    virtual const string getFormatName() const = 0;
    virtual const string getFormatDescription() const = 0;
};
