%module bpp_
%{
#include "NewtonOneDimension.h"
using namespace bpp;
%}
%include "AbstractOptimizer.i"

class NewtonOneDimension:
  public AbstractOptimizer
{
	public:
		NewtonOneDimension(DerivableSecondOrder * function = NULL);
		virtual ~NewtonOneDimension();
    NewtonOneDimension* clone() const;

		void doInit(const ParameterList & params) throw (Exception);
    double doStep() throw (Exception);
    void setMaximumNumberOfCorrections(unsigned int mx);
};
