%module bpptest
%{
#include "CoordsTools.h"
using namespace bpp;
%}
%include "Coord.i"

template <class T> class CoordsTools
{
  public:
    CoordsTools();
    virtual ~CoordsTools();
    static double getDistanceBetween(const Coord<T> co1, const Coord<T> co2);
};

%template(intCoordsTools) CoordsTools<int>;
%template(doubleCoordsTools) CoordsTools<double>;
