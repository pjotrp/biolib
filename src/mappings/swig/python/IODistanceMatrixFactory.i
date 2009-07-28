%module bpptest
%{
#include "IODistanceMatrixFactory.h"
using namespace bpp;
%}
%include "iodistance"
%include "std_string.i"
using namespace std;

class IODistanceMatrixFactory
{
public:
  static const string PHYLIP_FORMAT;  

  IODistanceMatrixFactory();
  virtual ~IODistanceMatrixFactory();
  virtual IDistanceMatrix * createReader(const string & format) throw (Exception);
  virtual ODistanceMatrix * createWriter(const string & format) throw (Exception);
};
