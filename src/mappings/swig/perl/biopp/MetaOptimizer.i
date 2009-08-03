%module bpp_
%{
#include "MetaOptimizer.h"
using namespace bpp;
%}
%include "AbstractOptimizer.i"
%include "std_vector.i"
using namespace std;

%ignore MetaOptimizerInfos::operator=;

class MetaOptimizerInfos:public virtual Clonable
{
  public:
    static string IT_TYPE_STEP;
    static string IT_TYPE_FULL;

    MetaOptimizerInfos();
    MetaOptimizerInfos(const MetaOptimizerInfos & infos);
    MetaOptimizerInfos& operator=(const MetaOptimizerInfos & infos);
    virtual ~MetaOptimizerInfos();

    MetaOptimizerInfos * clone() const;

    virtual void addOptimizer(const string & name, Optimizer * optimizer, const vector<string> & params, const short derivatives = 0, const string & type = IT_TYPE_STEP);
    virtual const string & getName(unsigned int i) const;
    virtual Optimizer * getOptimizer(unsigned int i);
    virtual const Optimizer * getOptimizer(unsigned int i) const;
    virtual vector<string> & getParameterNames(unsigned int i);
    virtual const vector<string> & getParameterNames(unsigned int i) const;
    virtual string & getIterationType(unsigned int i);
    virtual const string & getIterationType(unsigned int i) const;
    virtual bool requiresFirstOrderDerivatives(unsigned int i) const;  
    virtual bool requiresSecondOrderDerivatives(unsigned int i) const;  
    virtual unsigned int getNumberOfOptimizers() const;
};

%ignore MetaOptimizer::operator=;

class MetaOptimizer:public AbstractOptimizer
{
  public:
    MetaOptimizer(Function * function, MetaOptimizerInfos * desc, unsigned int n = 1);
    virtual ~MetaOptimizer();
    MetaOptimizer(const MetaOptimizer & opt);
    MetaOptimizer & operator=(const MetaOptimizer & opt);
    MetaOptimizer* clone() const;

    void setFunction(Function * function);
    void doInit(const ParameterList & parameters) throw (Exception);
    double doStep() throw (Exception);
    MetaOptimizerInfos * getOptimizers();
    const MetaOptimizerInfos * getOptimizers() const;
};
