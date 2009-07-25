%module bpptest
%{
#include "EchinodermMitochondrialGeneticCode.h"
using namespace bpp;
%}
%include "GeneticCode.i"
%include "NucleicAlphabet.i"
using namespace std;

class EchinodermMitochondrialGeneticCode:public GeneticCode
{
  public:
    EchinodermMitochondrialGeneticCode(const NucleicAlphabet * alpha);
    virtual ~EchinodermMitochondrialGeneticCode();

    int    translate(           int state) const throw (Exception);
    string translate(const string & state) const throw (Exception);
    Sequence * translate(const Sequence & sequence) const throw (Exception);
};
