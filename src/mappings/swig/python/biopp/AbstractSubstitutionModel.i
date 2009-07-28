%module bpptest
%{
#include "AbstractSubstitutionModel.h"
using namespace bpp;
%}
%include "SubstitutionModel.i"
%include "AbstractParameterAliasable.i"

class AbstractSubstitutionModel :public virtual SubstitutionModel,public AbstractParameterAliasable
{
  public:
    AbstractSubstitutionModel(const Alphabet * alpha, const string& prefix);
    virtual ~AbstractSubstitutionModel();
    virtual AbstractSubstitutionModel * clone() const = 0;

    const Alphabet * getAlphabet() const;
    const Vdouble & getFrequencies() const;
    const Matrix<double> & getGenerator() const;
    const Matrix<double> & getPij_t(double t) const;
    const Matrix<double> & getdPij_dt(double t) const;
    const Matrix<double> & getd2Pij_dt2(double t) const;
    const Vdouble & getEigenValues() const;
    const Matrix<double> & getRowLeftEigenVectors() const;
    const Matrix<double> & getColumnRightEigenVectors() const;
    double freq(int i) const;
    double Qij(int i, int j) const;
    double Pij_t (int i, int j, double t) const;
    double dPij_dt (int i, int j, double t) const;
    double d2Pij_dt2(int i, int j, double t) const;
    double getInitValue(int i, int state) const throw (BadIntException);
    void setFreqFromData(const SequenceContainer & data, unsigned int pseudoCount = 0);
    int getState(int i) const;
    void fireParameterChanged(const ParameterList & parameters);
};

class AbstractReversibleSubstitutionModel:public AbstractSubstitutionModel,public ReversibleSubstitutionModel
{
  public:
    AbstractReversibleSubstitutionModel(const Alphabet * alpha, const string& prefix);
    virtual ~AbstractReversibleSubstitutionModel();
    virtual AbstractReversibleSubstitutionModel * clone() const = 0;

    const Matrix<double> & getExchangeabilityMatrix() const;
    double Sij(int i, int j) const;
    virtual void updateMatrices();
};
