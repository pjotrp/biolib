%module bpptest
%{
#include "ProteinSubstitutionModelWithFrequencies.h"
using namespace bpp;
%}
%include "ProteinSubstitutionModel.i"
%include "FrequenciesSet.i"
%include "SequenceContainerTools.i"

%rename(__assign__) ProteinSubstitutionModelWithFrequencies::operator=;

class ProteinSubstitutionModelWithFrequencies:public virtual ProteinSubstitutionModel
{
  public:
    ProteinSubstitutionModelWithFrequencies(const ProteicAlphabet * alpha, const ProteinFrequenciesSet & freqSet, const string& prefix);
    ProteinSubstitutionModelWithFrequencies(const ProteicAlphabet * alpha, const string& prefix);
    ProteinSubstitutionModelWithFrequencies(const ProteinSubstitutionModelWithFrequencies & model);
    ProteinSubstitutionModelWithFrequencies & operator=(const ProteinSubstitutionModelWithFrequencies & model);
    virtual ~ProteinSubstitutionModelWithFrequencies();
    ProteinSubstitutionModelWithFrequencies* clone() const = 0;

    void fireParameterChanged(const ParameterList & parameters);
    void setFrequenciesSet(const ProteinFrequenciesSet & freqSet);
    const ProteinFrequenciesSet & getFrequenciesSet() const;
    void setFreqFromData(const SequenceContainer & data);
};
