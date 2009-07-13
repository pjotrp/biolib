%module bpp_
%{
#include "Uniform01K.h"
%}
%include "RandomFactory.i"
namespace bpp
{
class Uniform01K : public RandomFactory {
	public: 
		Uniform01K(long seed);
		~Uniform01K();

		void setSeed(long seed);
		double drawNumber() const;
};
} 
