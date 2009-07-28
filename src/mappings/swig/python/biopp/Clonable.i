%module bpp_clonable
%{
#include "Clonable.h"
using namespace bpp;
%}

class Clonable
{
	public:
		Clonable();
		virtual ~Clonable();

		virtual Clonable * clone() const = 0;
};
