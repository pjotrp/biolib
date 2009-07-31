%module bpptest
%{
#include "Coord.h"
using namespace bpp;
%}
%include <Clonable.i>

template <class T> class Coord:public virtual Clonable
{
  public: 
    Coord<T>(const T x=0, const T y=0): _x(x), _y(y);
    virtual ~Coord();

    Coord<T> * clone() const;
    void setCoord(const T x, const T y);
    void setX(const T x);
    void setY(const T y);
    T getX() const;
    T getY() const;
    bool hasSameCoordsAs(const Coord<T> & coord) const;
    virtual bool operator== (const Coord<T> & coord) const;
    virtual bool operator!= (const Coord<T> & coord) const;
};

%template(intCoord) Coord<int>;
%template(doubleCoord) Coord<double>;
