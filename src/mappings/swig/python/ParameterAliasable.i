%module bpp_
%{
#include "ParameterAliasable.h"
using namespace bpp;
%}
%include "Parametrizable.i"
%include "ParameterExceptions.i"
%include "ParameterList.i"
%include "std_string.i"

class ParameterAliasable :public virtual Parametrizable
{
  public:
    ParameterAliasable();
    virtual ~ParameterAliasable();

    virtual unsigned int getNumberOfIndependentParameters() const = 0;
    virtual void aliasParameters(const string & p1, const string & p2) throw (ParameterNotFoundException, Exception) = 0; 
    virtual void unaliasParameters(const string & p1, const string & p2) throw (ParameterNotFoundException, Exception)  = 0;
    virtual const ParameterList & getIndependentParameters() const = 0;
};

class ParameterAliasableAdapter:public ParametrizableAdapter
{
	public:
		ParameterAliasableAdapter();
		virtual ~ParameterAliasableAdapter();

		const ParameterList & getIndependentParameters() const;
    void aliasParameters(const string & p1, const string & p2) throw (ParameterNotFoundException, Exception);
    void unaliasParameters(const string & p1, const string & p2) throw (ParameterNotFoundException, Exception);
    unsigned int getNumberOfIndependentParameters() const;
};
