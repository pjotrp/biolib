%module bpp_number
%{
#include "Clonable.h"
%}

%include "Clonable.i"

namespace bpp
{

%rename(__assign__)	     Number::operator=;

template<class T> class Number: public Clonable
{
	public:
		Number(const T & value = 0): _value(value) {}
		virtual ~Number() {}
		Number<T> & operator=(const T & t);
		Number<T> * clone() const;
		T getValue();
};

} //end of namespace bpp.
