%module bpptest
%{
#include "VertebrateMitochondrialCodonAlphabet.h"
using namespace bpp;
%}
%include "CodonAlphabet.i"

class VertebrateMitochondrialCodonAlphabet : public CodonAlphabet
{
	public:
		VertebrateMitochondrialCodonAlphabet(const NucleicAlphabet * alpha);
		virtual ~VertebrateMitochondrialCodonAlphabet();

		unsigned int getSize() const;
		unsigned int getNumberOfTypes() const;
		string getAlphabetType() const;
		bool isStop(      int      codon) const;
		bool isStop(const string & codon) const;
};
