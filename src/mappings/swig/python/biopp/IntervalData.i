%module bpp_
%{
#include "IntervalData.h"
using namespace bpp;
%}
%include "Domain.i"
%include "std_iostream.i"
using namespace std;

%rename(_print) IntervalData::print;

class IntervalData
{
	public:
		IntervalData(const Domain & domain, const string & name = "");
		virtual ~IntervalData();

		virtual Domain getDomain() const;
		virtual double getDomainValue(double x) const;
		virtual void setName(const string & name);
		virtual string getName() const;
		virtual unsigned int getFreq(unsigned int i) const;
		virtual double getDensity(unsigned int i) const;
		virtual vector<unsigned int> getFrequencies() const;
		virtual Vdouble getDensities() const;
		virtual void addValue(double value) throw (OutOfRangeException);
		virtual unsigned int getSize() const;
		virtual double getMinValue() const;
		virtual double getMaxValue() const;
		virtual double getMean() const;
		virtual double getSD() const;
		virtual double getSDP() const;
		virtual void reset();
		virtual void print(ostream & out) const;
};
