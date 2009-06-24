%module bpp_rcolorset
%{
#include "ColorSet.h"
%}

%include "ColorSet.i"

namespace bpp
{

class RColorSet:
  public AbstractColorSet
{
  public:
    RColorSet();
    virtual ~RColorSet() {}
};

} // end of namespace bpp;
