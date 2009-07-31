%module bpptest
%{
#include "SubstitutionModel.h"
using namespace bpp;
%}
//#include <cstdlib>
%include "std_map.i"
%include "std_string.i"
%include "Alphabet.i"
%include "SequenceContainer.i"
%include "Exceptions.i"
%include "Parameter.i"
%include "ParameterList.i"
%include "ParameterAliasable.i"
%include "VectorTools.i"
%include "Matrix.i"

class SubstitutionModel;
class SubstitutionModelException:public Exception
{
  public:
    SubstitutionModelException(const char *   text, const SubstitutionModel * sm = NULL);
    SubstitutionModelException(const string & text, const SubstitutionModel * sm = NULL);
    ~SubstitutionModelException() throw ();

    virtual const SubstitutionModel * getSubstitutionModel() const;
};

%ignore SubstitutionModel::SubstitutionModel;
%ignore SubstitutionModel::~SubstitutionModel;

class SubstitutionModel:public virtual ParameterAliasable
{
  public:
    SubstitutionModel();
    virtual ~SubstitutionModel();
    SubstitutionModel * clone() const = 0;

    virtual string getName() const = 0;
    virtual double freq(int i) const = 0;
    virtual double Qij(int i, int j) const = 0;
    virtual double Pij_t(int i, int j, double t) const = 0;
    virtual double dPij_dt(int i, int j, double t) const = 0;
    virtual double d2Pij_dt2(int i, int j, double t) const = 0;
    virtual const Vdouble & getFrequencies() const = 0;
    virtual const Matrix<double> & getGenerator() const = 0;
    virtual const Matrix<double> & getPij_t(double t) const = 0;
    virtual const Matrix<double> & getdPij_dt(double t) const = 0;
    virtual const Matrix<double> & getd2Pij_dt2(double t) const = 0;
    virtual const Vdouble & getEigenValues() const = 0;
    virtual const Matrix<double> & getRowLeftEigenVectors() const = 0;
    virtual const Matrix<double> & getColumnRightEigenVectors() const = 0;
    virtual const Alphabet * getAlphabet() const = 0;
    virtual unsigned int getNumberOfStates() const = 0;
    virtual double getInitValue(int i, int state) const throw (BadIntException) = 0;
    virtual void setFreqFromData(const SequenceContainer & data, unsigned int pseudoCount = 0) = 0;
    virtual int getState(int i) const = 0;
};

%ignore ReversibleSubstitutionModel::ReversibleSubstitutionModel;
%ignore ReversibleSubstitutionModel::~ReversibleSubstitutionModel;

class ReversibleSubstitutionModel:public virtual SubstitutionModel
{
  public:
    ReversibleSubstitutionModel();
    virtual ~ReversibleSubstitutionModel();
    ReversibleSubstitutionModel * clone() const = 0;

    virtual const Matrix<double> & getExchangeabilityMatrix() const = 0;
    virtual double Sij(int i, int j) const = 0;
};
