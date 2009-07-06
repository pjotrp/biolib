%module bpp_defaultcolorset
%{
#include "DefaultColorSet.h"
%}

%include "ColorSet.i"
%include "ColorTools.i"

namespace bpp
{

class DefaultColorSet:public AbstractColorSet
{
  public:
    DefaultColorSet();
    virtual ~DefaultColorSet();
};

} // end of namespace bpp;

