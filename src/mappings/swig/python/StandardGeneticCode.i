%module bpptest
%{
#include "StandardGeneticCode.h"
using namespace bpp;
%}
%include "GeneticCode.i"
%include "NucleicAlphabet.i"
using namespace std;

class StandardGeneticCode:public GeneticCode
{
  public:
    StandardGeneticCode(const NucleicAlphabet * alpha);
    virtual ~StandardGeneticCode();

    int    translate(           int state) const throw (Exception);
    string translate(const string & state) const throw (Exception);
    Sequence * translate(const Sequence & sequence) const throw (Exception);
};
