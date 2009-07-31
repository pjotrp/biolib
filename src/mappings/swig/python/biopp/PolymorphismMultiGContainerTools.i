%module bpptest
%{
#include "PolymorphismMultiGContainerTools.h"
using namespace bpp;
%}
%include "std_vector.i"
//#include <set>
using namespace std;
%include "PolymorphismMultiGContainer.i"
%include "RandomTools.i"

%ignore PolymorphismMultiGContainerTools::PolymorphismMultiGContainerTools;
%ignore PolymorphismMultiGContainerTools::~PolymorphismMultiGContainerTools;

class PolymorphismMultiGContainerTools
{
  public:
    virtual ~PolymorphismMultiGContainerTools();

    static PolymorphismMultiGContainer permutMultiG(const PolymorphismMultiGContainer & pmgc);
    static PolymorphismMultiGContainer permutMonoG(const PolymorphismMultiGContainer & pmgc, const set<unsigned int> & groups);
    static PolymorphismMultiGContainer permutIntraGroupMonoG(const PolymorphismMultiGContainer & pmgc, const set<unsigned int> & groups); 
    static PolymorphismMultiGContainer permutAlleles(const PolymorphismMultiGContainer & pmgc, const set<unsigned int> & groups);
    static PolymorphismMultiGContainer permutIntraGroupAlleles(const PolymorphismMultiGContainer & pmgc, const set<unsigned int> & groups) ;
    static PolymorphismMultiGContainer extractGroups(const PolymorphismMultiGContainer & pmgc, const set<unsigned int> & groups) ;
};
