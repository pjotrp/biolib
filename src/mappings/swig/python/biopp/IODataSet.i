%module bpptest
%{
#include "IODataSet.h"
using namespace bpp;
%}
%include "DataSet.i"
%include "std_iostream.i"
//#include <fstream>
using namespace std;

%ignore IODataSet::IODataSet;
%ignore IODataSet::~IODataSet;

class IODataSet
{
  public: 
    virtual ~IODataSet();

    virtual const string getFormatName() = 0;
    virtual const string getFormatDescription() = 0;
};
