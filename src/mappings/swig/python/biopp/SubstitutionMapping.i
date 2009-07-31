%module bpptest
%{
#include "SubstitutionMapping.h"
using namespace bpp;
%}
%include "Tree.i"
%include "TreeTemplate.i"
%include "Clonable.i"

%ignore SubstitutionMapping::SubstitutionMapping;
%ignore SubstitutionMapping::~SubstitutionMapping;

class SubstitutionMapping:public virtual Clonable
{
  public:
    SubstitutionMapping();
    virtual ~SubstitutionMapping();
    SubstitutionMapping * clone() const = 0;

    virtual const Tree * getTree() const = 0;
    virtual unsigned int getNumberOfSites() const = 0;
    virtual unsigned int getNumberOfBranches() const = 0;
    virtual int getSitePosition(unsigned int index) const = 0;
};

class AbstractSubstitutionMapping:public SubstitutionMapping
{
  public:
    AbstractSubstitutionMapping();
    virtual ~AbstractSubstitutionMapping();

    virtual const TreeTemplate<Node> * getTree() const;
    int getSitePosition(unsigned int index) const;
};
