%module bpptest
%{
#include "JCprot.h"
using namespace bpp;
%}
%include "ProteicAlphabet.i"
%include "ProteinSubstitutionModel.i"

class JCprot:public ProteinSubstitutionModel
{
  public:
    JCprot(const ProteicAlphabet * alpha);
    virtual ~JCprot();
    JCprot* clone() const;

    double Pij_t    (int i, int j, double d) const;
    double dPij_dt  (int i, int j, double d) const;
    double d2Pij_dt2(int i, int j, double d) const;
    const Matrix<double> & getPij_t    (double d) const;
    const Matrix<double> & getdPij_dt  (double d) const;
    const Matrix<double> & getd2Pij_dt2(double d) const;
    string getName() const;
};
