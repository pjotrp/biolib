%module bpp_
%{
#include "Constraints.h"
%}
%include "std_string.i"
using namespace std;
%include "Clonable.i"
%include "TextTools.i"
namespace bpp
{
class Constraint : public Clonable
{
	public:
		Constraint();
		virtual ~Constraint();
    Constraint * clone() const = 0;

		virtual bool isCorrect(double value) const = 0;
		virtual double getLimit(double value) const = 0;
		virtual string getDescription() const = 0;		
};

class IncludingPositiveReal: public Constraint
{
	public:
		IncludingPositiveReal(double lowerBound): _lower(lowerBound);
		virtual ~IncludingPositiveReal();
    IncludingPositiveReal * clone() const;

		bool isCorrect(double value) const;
		double getLimit(double value) const;
		string getDescription() const;
    void setLowerBound(double lowerBound);
    double getLowerBound() const;
};

class ExcludingPositiveReal: public Constraint
{
	public:
		ExcludingPositiveReal(double lowerBound): _lower(lowerBound);
		virtual ~ExcludingPositiveReal();
    ExcludingPositiveReal * clone() const;

		bool isCorrect(double value) const;
		double getLimit(double value) const;
		string getDescription() const;
    void setLowerBound(double lowerBound);
    double getLowerBound() const;
};

class IncludingNegativeReal: public Constraint
{
	public:
		IncludingNegativeReal(double upperBound): _upper(upperBound);
		virtual ~IncludingNegativeReal();
    IncludingNegativeReal * clone() const;

		bool isCorrect(double value) const;
		double getLimit(double value) const;
		string getDescription() const;
    void setUpperBound(double upperBound);
    double getUpperBound() const;
};

class ExcludingNegativeReal: public Constraint
{
	public:
		ExcludingNegativeReal(double upperBound): _upper(upperBound);
		virtual ~ExcludingNegativeReal();
    ExcludingNegativeReal * clone() const;

		bool isCorrect(double value) const;
		double getLimit(double value) const;
		string getDescription() const;
    void setUpperBound(double upperBound);
    double getUpperBound() const;
};

class Interval: public Constraint
{
	public:
		Interval(double lowerBound, double upperBound): _lower(lowerBound), _upper(upperBound);
		virtual ~Interval();
    Interval * clone() const = 0;

		bool isCorrect(double value) const = 0;
		double getLimit(double value) const;
		string getDescription() const = 0;
    virtual void setLowerBound(double lowerBound);
    virtual void setUpperBound(double upperBound);
    virtual double getLowerBound() const;
    virtual double getUpperBound() const;
};

class IncludingInterval: public Interval
{
	public:
		IncludingInterval(double lowerBound, double upperBound) :
			Interval(lowerBound, upperBound);
		virtual ~IncludingInterval();
    IncludingInterval * clone() const;

		bool isCorrect(double value) const;
		string getDescription() const;
};

class ExcludingInterval: public Interval
{
	public:
		ExcludingInterval(double lowerBound, double upperBound):
			Interval(lowerBound, upperBound);
    virtual ~ExcludingInterval();
    ExcludingInterval * clone() const;

		bool isCorrect(double value) const;
		string getDescription() const;
};

class IncludingExcludingInterval: public Interval
{
	public:
		IncludingExcludingInterval(double lowerBound, double upperBound):
			Interval(lowerBound, upperBound);
    virtual ~IncludingExcludingInterval();
    IncludingExcludingInterval * clone() const;
		bool isCorrect(double value) const;
		string getDescription() const;
};

class ExcludingIncludingInterval: public Interval
{
	public:
		ExcludingIncludingInterval(double lowerBound, double upperBound) :
			Interval(lowerBound, upperBound);
		virtual ~ExcludingIncludingInterval();
    ExcludingIncludingInterval * clone() const;
		bool isCorrect(double value) const;
		string getDescription() const;
};
} 
