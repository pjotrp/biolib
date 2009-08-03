%module bpp_
%{
#include "TestUnit.h"
using namespace bpp;
using namespace test_numcalc;
%}

class TestUnit
{
  public:
    static bool testEigen();
};
