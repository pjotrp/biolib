%module bpp_
%{
#include "AbstractParameterAliasable.h"
using namespace bpp;
%}
%include "AbstractParametrizable.i"
%include "ParameterAliasable.i"
%include "std_map.i"
using namespace std;

class AbstractParameterAliasable:public AbstractParametrizable,public virtual ParameterAliasable
{
  public:
    AbstractParameterAliasable(const string& prefix) : AbstractParametrizable(prefix);
    AbstractParameterAliasable(const AbstractParameterAliasable & ap);
    AbstractParameterAliasable & operator=(const AbstractParameterAliasable & ap);
    virtual ~AbstractParameterAliasable();

    void setNamespace(const string& prefix);
    const ParameterList & getIndependentParameters() const;
    unsigned int getNumberOfIndependentParameters() const;
    void aliasParameters(const string & p1, const string & p2) throw (ParameterNotFoundException, Exception);
    void unaliasParameters(const string & p1, const string & p2) throw (ParameterNotFoundException, Exception);
    void fireParameterChanged(const ParameterList& parameters);
};
