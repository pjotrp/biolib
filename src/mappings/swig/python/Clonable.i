%module bpp_clonable
%{
#include "Clonable.h"
%}
namespace bpp
{

class Clonable
{
	public:
		Clonable();
		virtual ~Clonable();

		virtual Clonable * clone() const = 0;
};

} //end of namespace bpp.
