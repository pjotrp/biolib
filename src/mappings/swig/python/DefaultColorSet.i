%module bpp_defaultcolorset
%{
#include "DefaultColorSet.h"
using namespace bpp;
%}

%include "ColorSet.i"
%include "ColorTools.i"

class DefaultColorSet:public AbstractColorSet
{
  public:
    DefaultColorSet();
    virtual ~DefaultColorSet();
};
