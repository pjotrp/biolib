%module bpp_
%{
#include "Uniform01K.h"
using namespace bpp;
%}
%include "RandomFactory.i"

class Uniform01K : public RandomFactory {
	public: 
		Uniform01K(long seed);
		~Uniform01K();

		void setSeed(long seed);
		double drawNumber() const;
};

