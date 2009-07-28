%module bpptest
%{
#include "RE08.h"
using namespace bpp;
%}
%include "SubstitutionModel.i"
%include "AbstractSubstitutionModel.i"

%rename(__assign__) RE08::operator=;

class RE08:public AbstractReversibleSubstitutionModel
{
  public:
    RE08(ReversibleSubstitutionModel *simpleModel, double lambda = 0, double mu = 0);
    RE08(const RE08 & model);
    RE08& operator=(const RE08 & model);
    virtual ~RE08();
    RE08 * clone() const;

    double Pij_t (int i, int j, double d) const;
    double dPij_dt (int i, int j, double d) const;
    double d2Pij_dt2(int i, int j, double d) const;
    const Matrix<double> & getPij_t    (double d) const;
    const Matrix<double> & getdPij_dt  (double d) const;
    const Matrix<double> & getd2Pij_dt2(double d) const;
    string getName() const;
    void setFreqFromData(const SequenceContainer & data);
    void fireParameterChanged(const ParameterList &parameters);
    unsigned int getNumberOfStates() const;
    double getInitValue(int i, int state) const throw (BadIntException);
    void setNamespace(const string& prefix);
};
