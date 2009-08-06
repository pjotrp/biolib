%module bpp_string
%{
#include "BppString.h"
using namespace bpp;
%}

%include "Clonable.i"
%include "std_string.i"

using std::string;

class String: public string, public Clonable
{
	public:
		String(const char * value): string(value);
		String(const string & value): string(value);
		virtual ~String();

		String * clone() const;
};