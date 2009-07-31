%module bpptest
%{
#include "SubstitutionModelSetTools.h"
using namespace bpp;
%}
%include "SubstitutionModelSet.i"
%include "Tree.i"

%ignore SubstitutionModelSetTools::SubstitutionModelSetTools;
%ignore SubstitutionModelSetTools::~SubstitutionModelSetTools;

class SubstitutionModelSetTools
{
  public:
    static SubstitutionModelSet* createHomogeneousModelSet(SubstitutionModel* model, FrequenciesSet* rootFreqs, const Tree* tree) throw (AlphabetException, Exception);
    static SubstitutionModelSet* createNonHomogeneousModelSet(SubstitutionModel* model, FrequenciesSet* rootFreqs, const Tree* tree, const vector<string>& globalParameterNames) throw (AlphabetException, Exception);
};
