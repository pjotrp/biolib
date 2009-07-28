%module bpptest
%{
#include "IOTreeFactory.h"
using namespace bpp;
%}
%include "iotree"

class IOTreeFactory
{
  public:
    static const string NEWICK_FORMAT;  

    IOTreeFactory();
    virtual ~IOTreeFactory();
    virtual ITree * createReader(const string & format) throw (Exception);
    virtual OTree * createWriter(const string & format) throw (Exception);
};
  