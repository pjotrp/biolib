%module bpp_dvipscolorset
%{
#include "ColorSet.h"
%}

%include "ColorSet.i"

namespace bpp
{

class DvipsColorSet:
  public AbstractColorSet
{
  public:
    DvipsColorSet();
    virtual ~DvipsColorSet();
};

} // end of namespace bpp;
