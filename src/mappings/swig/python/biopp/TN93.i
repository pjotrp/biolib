%module bpptest
%{
#include "TN93.h"
using namespace bpp;
%}
%include "NucleotideSubstitutionModel.i"
%include "Constraints.i"
%include "NucleicAlphabet.i"
%include "SequenceContainer.i"

class TN93:public NucleotideSubstitutionModel
{
  public:
    TN93(const NucleicAlphabet * alpha, double kappa1 = 1., double kappa2 = 1., double piA = 0.25, double piC = 0.25, double piG = 0.25, double piT = 0.25);
    virtual ~TN93();
    TN93* clone() const;

    double Pij_t (int i, int j, double d) const;
    double dPij_dt (int i, int j, double d) const;
    double d2Pij_dt2(int i, int j, double d) const;
    const Matrix<double> & getPij_t (double d) const;
    const Matrix<double> & getdPij_dt (double d) const;
    const Matrix<double> & getd2Pij_dt2(double d) const;
    string getName() const;
    void setFreqFromData(const SequenceContainer & data, unsigned int pseudoCount = 0);
};
