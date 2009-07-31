%module bpptest
%{
#include "Date.h"
using namespace bpp;
%}
%include "Exceptions.i"

%rename(__assign__) Date::operator=;
%rename(__eq__) Date::operator==;
%rename(__lt__) Date::operator<;
%rename(__ne__) Date::operator!=;
%rename(__gt__) Date::operator>;
%rename(__lte__) Date::operator<=;
%rename(__gte__) Date::operator>=;

class Date
{
  public: 
    Date(const int day=1, const int month=1, const int year=2000) throw(BadIntegerException);
    Date(const Date & date);
    ~Date();

    Date & operator= (const Date & date);
    void setDate(const int day, const int month, const int year) throw(BadIntegerException);
    void setYear(const int year);
    void setMonth(const int month) throw(BadIntegerException);
    void setDay(const int day) throw(BadIntegerException);
    Date * getDate() const;
    string getDateStr() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    bool operator== (const Date & date) const;
    bool operator< (const Date & date) const;
    bool operator!= (const Date & date) const;
    bool operator> (const Date & date) const;
    bool operator<= (const Date & date) const;
    bool operator>= (const Date & date) const;
};
