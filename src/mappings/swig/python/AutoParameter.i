%module bpp_
%{
#include "AutoParameter.h"
%}
%include "Parameter.i"
namespace bpp
{
class AutoParameter:public Parameter
{
	public:
		AutoParameter(const string & name = "", double value = 0, Constraint * constraint = NULL, bool attachConstraint = false) throw (ConstraintException);
		AutoParameter(const Parameter & param);
		AutoParameter(const AutoParameter & param);
		AutoParameter & operator=(const AutoParameter & param);
		virtual ~AutoParameter();
		AutoParameter * clone() const;

		virtual void setValue(double value) throw (ConstraintException);

		virtual void setMessageHandler(ostream * mh);

		static string CONSTRAINTS_AUTO;
		static string CONSTRAINTS_IGNORE;
		static string CONSTRAINTS_KEEP;
};
} 
