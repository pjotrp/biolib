%module bpptest
%{
#include "VertebrateMitochondrialGeneticCode.h"
using namespace bpp;
%}
%include "GeneticCode.i"
%include "NucleicAlphabet.i"
using namespace std;

class VertebrateMitochondrialGeneticCode:public GeneticCode
{
	public:
		VertebrateMitochondrialGeneticCode(const NucleicAlphabet * alpha);
		virtual ~VertebrateMitochondrialGeneticCode();
		int translate(int state) const throw (Exception);
		string translate(const string & state) const throw (Exception);
		Sequence * translate(const Sequence & sequence) const throw (Exception);
};
