%module bpp_vector
%{
#include "BppVector.h"
using namespace bpp;
%}

%include "Clonable.i"
%include "std_vector.i"

%template(intVector) std::vector<int>;
%template(doubleVector) std::vector<double>;

template<class TYPE>
class Vector: public std::vector<TYPE>, public Clonable
{
  public:
    Vector():std::vector<TYPE>();
    Vector(typename std::vector<TYPE>::size_type num, const TYPE& val = TYPE() ):std::vector<TYPE>(num, val);
    Vector(typename std::vector<TYPE>::iterator start, typename std::vector<TYPE>::iterator end):std::vector<TYPE>(start, end);
    virtual ~Vector() {}

    Vector<TYPE> * clone() const;
};

%template(intBPPVector) Vector<int>;
%template(doubleBPPVector) Vector<double>;
