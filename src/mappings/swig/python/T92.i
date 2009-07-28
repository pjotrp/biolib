%module bpptest
%{
#include "T92.h"
using namespace bpp;
%}
%include "NucleotideSubstitutionModel.i"
%include "Constraints.i"
%include "NucleicAlphabet.i"
%include "SequenceContainer.i"

class T92:public NucleotideSubstitutionModel
{
  public:
    T92(const NucleicAlphabet * alpha, double kappa = 1., double theta = 0.5);
    virtual ~T92();
    T92* clone() const;

    double Pij_t    (int i, int j, double d) const;
    double dPij_dt  (int i, int j, double d) const;
    double d2Pij_dt2(int i, int j, double d) const;
    const Matrix<double> & getPij_t(double d) const;
    const Matrix<double> & getdPij_dt(double d) const;
    const Matrix<double> & getd2Pij_dt2(double d) const;
    string getName() const;
    void setFreqFromData(const SequenceContainer & data, unsigned int pseudoCount = 0);
};
