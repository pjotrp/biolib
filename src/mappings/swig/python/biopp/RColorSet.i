%module bpp_rcolorset
%{
#include "RColorSet.h"
using namespace bpp;
%}

%include "ColorSet.i"

class RColorSet:public AbstractColorSet
{
  public:
    RColorSet();
    virtual ~RColorSet() {}
};
