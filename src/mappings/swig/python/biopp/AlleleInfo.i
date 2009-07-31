%module bpptest
%{
#include "AlleleInfo.h"
using namespace bpp;
%}
%include "std_string.i"
using namespace std;
%include "Clonable.i"

%ignore AlleleInfo::AlleleInfo;
%ignore AlleleInfo::~AlleleInfo;

class AlleleInfo:public virtual Clonable
{
  public: 
    virtual ~AlleleInfo();

    virtual void setId(const string & allele_id) = 0;
    virtual string getId() const = 0;
};
