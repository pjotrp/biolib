%module bpp_
%{
#include "NewtonOneDimension.h"
%}
%include "AbstractOptimizer.i"
namespace bpp
{
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
} 
