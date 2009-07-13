%module bpp_
%{
#include "Uniform01QD.h"
%}
%include "RandomFactory.i"
namespace bpp
{
class Uniform01QD : public RandomFactory {
	public: 
		Uniform01QD(long seed);
		~Uniform01QD();

		void setSeed(long seed);
		double drawNumber() const;
};
} 
