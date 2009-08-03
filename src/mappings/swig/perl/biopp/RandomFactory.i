%module bpp_
%{
#include "RandomFactory.h"
using namespace bpp;
%}

class RandomFactory {
	public:
		RandomFactory();
		virtual ~RandomFactory();

		virtual void setSeed(long seed) = 0;
		virtual double drawNumber() const = 0;
};
