%module bpptest
%{
#include "AbstractISequence2.h"
using namespace bpp;
%}
%include "AlignedSequenceContainer.i"
%include "Alphabet.i"
%include "ISequence.i"
%include "std_string.i"
%include "std_iostream.i"
//#include <fstream>
using namespace std;

class AbstractISequence2:public virtual ISequence2
{
	public:
		AbstractISequence2();
		virtual ~AbstractISequence2();

		virtual void read(istream & input, AlignedSequenceContainer & sc) const throw (Exception);

		virtual void read(const string & path, AlignedSequenceContainer & sc) const throw (Exception);

		virtual AlignedSequenceContainer * read(istream & input, const Alphabet * alpha) const throw (Exception);

		virtual AlignedSequenceContainer * read(const string & path , const Alphabet * alpha) const throw (Exception);
}; 
