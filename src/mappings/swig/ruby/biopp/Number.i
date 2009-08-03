%module bpp_number
%{
#include "Number.h"
using namespace bpp;
%}

%include "Clonable.i"

%rename(__assign__) *::operator=;

template<class T> class Number : public Clonable
{
	public:
		Number(const T & value = 0): _value(value);
		virtual ~Number();
		Number<T> & operator=(const T & t);
		Number<T> * clone() const;
		T getValue();
};

%template(intNumber) Number<int>;
%template(doubleNumber) Number<double>;
