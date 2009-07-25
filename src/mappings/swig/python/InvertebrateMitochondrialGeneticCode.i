%module bpptest
%{
#include "InvertebrateMitochondrialGeneticCode.h"
using namespace bpp;
%}
%include "GeneticCode.i"
%include "NucleicAlphabet.i"
using namespace std;

class InvertebrateMitochondrialGeneticCode:public GeneticCode
{
  public:
    InvertebrateMitochondrialGeneticCode(const NucleicAlphabet * alpha);
    virtual ~InvertebrateMitochondrialGeneticCode();

    int    translate(           int state) const throw (Exception);
    string translate(const string & state) const throw (Exception);
    Sequence * translate(const Sequence & sequence) const throw (Exception);
};
