%module bpptest
%{
#include "ProbabilisticSubstitutionMapping.h"
using namespace bpp;
%}
%include "SubstitutionMapping.i"
%include "TreeExceptions.i"
%include "std_vector.i"
%include "TextTools.i"

%rename(__assign__) ProbabilisticSubstitutionMapping::operator=;
%rename(__funcall__) ProbabilisticSubstitutionMapping::operator();
%rename(__aref__) ProbabilisticSubstitutionMapping::operator[];

class ProbabilisticSubstitutionMapping:public AbstractSubstitutionMapping
{
  public:
    ProbabilisticSubstitutionMapping(const Tree & tree, unsigned int numberOfSites);
    ProbabilisticSubstitutionMapping(const Tree & tree);
    ProbabilisticSubstitutionMapping(const ProbabilisticSubstitutionMapping & psm);
    ProbabilisticSubstitutionMapping & operator=(const ProbabilisticSubstitutionMapping & psm);
    ProbabilisticSubstitutionMapping *clone() const;
    virtual ~ProbabilisticSubstitutionMapping();

    unsigned int getNumberOfSites() const;
    unsigned int getNumberOfBranches() const;
    virtual double getNumberOfSubstitutions(int nodeId, unsigned int siteIndex) const;
    virtual const Node * getNode(unsigned int nodeIndex) const;
    virtual vector<double> getBranchLengths() const;
    virtual unsigned int getNodeIndex(int nodeId) const throw (NodeNotFoundException);
    virtual void setTree(const Tree & tree);
    virtual void setNumberOfSites(unsigned int numberOfSites);
    virtual double & operator()(unsigned int nodeIndex, unsigned int siteIndex);
    virtual const double & operator()(unsigned int nodeIndex, unsigned int siteIndex) const;
    vector<double> & operator[](unsigned int siteIndex);
    const vector<double> & operator[](unsigned int siteIndex) const;
    void setSitePosition(unsigned int index, int position);
};
