%module bpp_molscriptcolorset
%{
#include "MolscriptColorSet.h"
using namespace bpp;
%}

%include "ColorSet.i"

class MolscriptColorSet:public AbstractColorSet
{
  public:
    MolscriptColorSet();
    virtual ~MolscriptColorSet() {}
};
