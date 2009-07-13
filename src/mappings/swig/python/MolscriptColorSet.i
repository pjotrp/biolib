%module bpp_molscriptcolorset
%{
#include "MolscriptColorSet.h"
%}

%include "ColorSet.i"

namespace bpp
{

class MolscriptColorSet:public AbstractColorSet
{
  public:
    MolscriptColorSet();
    virtual ~MolscriptColorSet() {}
};

} // end of namespace bpp;
