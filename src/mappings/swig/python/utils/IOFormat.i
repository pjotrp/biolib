%module bpp_ioformat
%{
#include "IOFormat.h"
#include <string>
%}

%include "Exceptions.i"
%include "std_string.i"

using namespace std;

namespace bpp
{

class IOFormat
{
	public:
		IOFormat() {}
		virtual ~IOFormat() {}

		virtual const string getDataType() const = 0;
		virtual const string getFormatName() const = 0;
		virtual const string getFormatDescription() const = 0;
};

} //end of namespace bpp.
