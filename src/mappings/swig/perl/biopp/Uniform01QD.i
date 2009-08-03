%module bpp_
%{
#include "Uniform01QD.h"
using namespace bpp;
%}
%include "RandomFactory.i"

class Uniform01QD : public RandomFactory {
	public: 
		Uniform01QD(long seed);
		~Uniform01QD();

		void setSeed(long seed);
		double drawNumber() const;
};
