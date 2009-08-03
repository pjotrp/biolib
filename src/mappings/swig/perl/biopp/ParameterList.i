%module bpp_paramlist
%{
#include "ParameterList.h"
using namespace bpp;
%}
%include "Parameter.i"
%include "Clonable.i"
%include "std_vector.i"
%include "std_string.i"
//%include "std_iostream.i"
using namespace std;

//%template(intVector) std::vector<int>;
//%template(intVector) std::vector<int*>;
//%template(paramPVector) std::vector<Parameter *>;
//%template(paramPVector) std::vector<Parameter*>;

%template(paramPVector) std::vector<Parameter*>;

%ignore ParameterList::operator=;

//class ParameterList:public std::vector<Parameter *>
//,public Clonable

//class ParameterList:public std::vector<int>
class ParameterList:public std::vector<Parameter*>, public Clonable
{
  public:
    ParameterList();
    ParameterList(const ParameterList & pl);
    ParameterList & operator=(const ParameterList & pl);
    ParameterList * clone() const;
    virtual ~ParameterList();

    virtual const Parameter & getParameter(const string & name) const throw (ParameterNotFoundException);
    virtual Parameter & getParameter(const string & name) throw (ParameterNotFoundException);
    virtual ParameterList subList(const vector<string> & names) const throw (ParameterNotFoundException);
    virtual ParameterList subList(const string & name) const throw (ParameterNotFoundException);
    virtual ParameterList subList(vector<unsigned int> parameters) const;
    virtual ParameterList subList(unsigned int parameter) const;
    virtual ParameterList getCommonParametersWith(const ParameterList & params) const;
    virtual vector<string> getParameterNames() const;
    virtual void addParameter(const Parameter & param) throw (ParameterException);
    virtual void addParameters(const ParameterList & params) throw (ParameterException);
    virtual void setParameterValue(const string & name, double value) throw (ParameterNotFoundException, ConstraintException);
    virtual void setAllParametersValues(const ParameterList & params) throw (ParameterNotFoundException, ConstraintException);
    virtual void setParametersValues(const ParameterList & params) throw (ParameterNotFoundException, ConstraintException);
    virtual bool hasParameter(const string& name) const;
    virtual void matchParametersValues(const ParameterList & params) throw (ConstraintException);
    virtual void setAllParameters(const ParameterList & params) throw (ParameterNotFoundException);
    virtual void setParameters(const ParameterList & params) throw (ParameterNotFoundException);
    virtual void matchParameters(const ParameterList & params);
    virtual void deleteParameter(const string & name) throw (ParameterNotFoundException);
    virtual void deleteParameters(const vector<string> & names) throw (ParameterNotFoundException);
    virtual void deleteParameter(unsigned int index) throw (IndexOutOfBoundsException);
    virtual void deleteParameters(const vector<unsigned int> & indices) throw (IndexOutOfBoundsException);
    virtual unsigned int whichParameterHasName(const string & name) const throw (ParameterNotFoundException);
    virtual void printParameters(ostream & out) const;
    virtual void reset();
};
