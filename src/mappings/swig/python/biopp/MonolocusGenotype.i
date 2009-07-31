%module bpptest
%{
#include "MonolocusGenotype.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "Clonable.i"

%ignore MonolocusGenotype::MonolocusGenotype;
%ignore MonolocusGenotype::~MonolocusGenotype;

class MonolocusGenotype:public Clonable
{
  public: 
    virtual ~MonolocusGenotype();

    virtual vector<unsigned int> getAlleleIndex() const = 0;
};
