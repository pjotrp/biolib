%module bpptest
%{
#include "SequenceContainer.h"
#include "OSequence.h"
using namespace bpp;
%}
%include "SequenceContainer.i"
%include "IOSequence.i"
%include "Exceptions.i"

class OSequence:public virtual IOSequence
{
	public:
		OSequence();
		virtual ~OSequence();

		virtual void write(ostream & output, const SequenceContainer & sc) const throw (Exception) = 0;
		virtual void write(const string & path, const SequenceContainer & sc, bool overwrite) const throw (Exception) = 0;
};
