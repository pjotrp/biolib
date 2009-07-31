%module bpptest
%{
#include "BasicAlleleInfo.h"
using namespace bpp;
%}
%include "AlleleInfo.i"
%include "GeneralExceptions.i"

%rename(__assign__) BasicAlleleInfo::operator=;
%rename(__eq__) BasicAlleleInfo::operator==;
%rename(__ne__) BasicAlleleInfo::operator!=;

class BasicAlleleInfo:public AlleleInfo
{
  public: 
    BasicAlleleInfo(const string & id);
    BasicAlleleInfo(const BasicAlleleInfo &allele);
    virtual ~BasicAlleleInfo();

    virtual BasicAlleleInfo & operator= (const BasicAlleleInfo & allele);
    virtual bool operator== (const BasicAlleleInfo & allele) const;
    virtual bool operator!= (const BasicAlleleInfo & allele) const;
    Clonable * clone() const;
    void setId(const string & allele_id);
    string getId() const;
};
