%module bpptest
%{
#include "Locality.h"
using namespace bpp;
%}
%include "Coord.i"
%include "std_string.i"
using namespace std;

%rename(__eq__) *::operator==;
%rename(__ne__) *::operator!=;

template <class T> class Locality:public Coord<T>
{
  public: 
    Locality<T>(const string name, const T x=0, const T y=0);
    Locality<T>(const string name, const Coord<T> & coord);
    virtual ~Locality<T>();

    Locality<T> * clone() const;
    virtual bool operator== (const Locality<T> & locality) const;
    virtual bool operator!= (const Locality<T> & locality) const;
    void setName(const string & name);
    string getName() const;
};

%template(intLocality) Locality<int>;
%template(doubleLocality) Locality<double>;
