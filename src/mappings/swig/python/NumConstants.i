%module bpp_
%{
#include "NumConstants.h"
%}
namespace bpp {
class NumConstants
{
  public:
    static const double GOLDEN_RATIO_PHI;
    static const double GOLDEN_RATIO_R;
    static const double GOLDEN_RATIO_C;
    static const double TINY;
    static const double VERY_TINY;
    static const double VERY_BIG;
    static const double PI;
};
}
