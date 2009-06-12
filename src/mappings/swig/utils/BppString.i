%module bpp_string
%{
#include "Clonable.h"
#include <string>
%}

%include "Clonable.h"
%include "std_string.i"

using std::string;
namespace bpp
{

class String: public string, public Clonable
{
	public:
		
		String(const char * value): string(value) {}
		String(const string & value): string(value) {}
		virtual ~String() {}
	
	public:
		String * clone() const { return new String(*this); }
};

} //end of namespace bpp.
