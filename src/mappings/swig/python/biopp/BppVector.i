%module bpp_vector
%{
#include "BppVector.h"
using namespace bpp;
%}

%include "Clonable.i"
%include "std_vector.i"
%include "swigutils.i"

template<class TYPE> class Vector: public std::vector<TYPE>, public Clonable
{
  public:
    Vector();
    Vector(typename std::vector<TYPE>::size_type num, const TYPE& val = TYPE() );
    Vector(typename std::vector<TYPE>::iterator start, typename std::vector<TYPE>::iterator end);
    virtual ~Vector();

    Vector<TYPE> * clone() const;
};

%template(intBPPVector) Vector<int>;
%template(doubleBPPVector) Vector<double>;
