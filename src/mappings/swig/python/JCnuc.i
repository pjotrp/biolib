%module bpptest
%{
#include "JCnuc.h"
using namespace bpp;
%}
%include "NucleotideSubstitutionModel.i"

class JCnuc:public NucleotideSubstitutionModel
{
  public:
    JCnuc(const NucleicAlphabet * alpha);
    virtual ~JCnuc();
    JCnuc* clone() const;

    double Pij_t    (int i, int j, double d) const;
    double dPij_dt  (int i, int j, double d) const;
    double d2Pij_dt2(int i, int j, double d) const;
    const Matrix<double> & getPij_t    (double d) const;
    const Matrix<double> & getdPij_dt  (double d) const;
    const Matrix<double> & getd2Pij_dt2(double d) const;
    string getName() const;
    void setFreqFromData(const SequenceContainer & data);
};
