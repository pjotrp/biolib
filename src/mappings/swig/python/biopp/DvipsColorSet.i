%module bpp_dvipscolorset
%{
#include "DvipsColorSet.h"
using namespace bpp;
%}

%include "ColorSet.i"

class DvipsColorSet:public AbstractColorSet
{
  public:
    DvipsColorSet();
    virtual ~DvipsColorSet();
};
