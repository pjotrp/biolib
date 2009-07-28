%module bpptest
%{
#include "MarkovModulatedSubstitutionModel.h"
using namespace bpp;
%}
%include "SubstitutionModel.i"
%include "AbstractParameterAliasable.i"

%rename(__assign__) MarkovModulatedSubstitutionModel::operator=;

class MarkovModulatedSubstitutionModel:public ReversibleSubstitutionModel,public AbstractParameterAliasable
{
  public:
    MarkovModulatedSubstitutionModel(ReversibleSubstitutionModel* model, bool normalizeRateChanges, const string& prefix);
    MarkovModulatedSubstitutionModel(const MarkovModulatedSubstitutionModel & model);
    MarkovModulatedSubstitutionModel & operator=(const MarkovModulatedSubstitutionModel & model);
    virtual ~MarkovModulatedSubstitutionModel();
    MarkovModulatedSubstitutionModel* clone() const = 0;

    const Alphabet * getAlphabet() const;
    unsigned int getNumberOfStates() const;
    const Vdouble & getFrequencies() const;
    const Matrix<double> & getExchangeabilityMatrix() const;
    const Matrix<double> & getGenerator() const;
    const Matrix<double> & getPij_t(double t) const;
    const Matrix<double> & getdPij_dt(double t) const;
    const Matrix<double> & getd2Pij_dt2(double t) const;
    const Vdouble & getEigenValues() const;
    const Matrix<double> & getRowLeftEigenVectors() const;
    const Matrix<double> & getColumnRightEigenVectors() const;
    double freq(int i) const;
    double Sij(int i, int j) const;
    double Qij(int i, int j) const;
    double Pij_t    (int i, int j, double t) const;
    double dPij_dt  (int i, int j, double t) const;
    double d2Pij_dt2(int i, int j, double t) const;
    double getInitValue(int i, int state) const throw (BadIntException);
    void setFreqFromData(const SequenceContainer & data, unsigned int pseudoCount = 0);
    int getState(int i) const;
    int getRate(int i) const;
    virtual void fireParameterChanged(const ParameterList & parameters);
    void setNamespace(const string& prefix);
};
