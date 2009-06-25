%module bpp_vector
%{
#include "Clonable.h"
#include <vector>
%}

%include "Clonable.i"
%include "std_vector.i"

using std::vector;

namespace bpp
{


template<class TYPE>
class Vector: public vector<TYPE>, public Clonable
{
  public:

    Vector():vector<TYPE>() {}
    Vector(typename vector<TYPE>::size_type num, const TYPE& val = TYPE() ):vector<TYPE>(num, val) {}
    Vector(typename vector<TYPE>::iterator start, typename vector<TYPE>::iterator end):vector<TYPE>(start, end) {}
    virtual ~Vector() {}
  
  public:
    Vector<TYPE> * clone() const;
};

} //end of namespace bpp.
