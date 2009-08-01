%module bpptest
%{
#include "SequenceContainerTools.h"
using namespace bpp;
%}
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"

using namespace std;
%include "SequenceContainer.i"
%include "OrderedSequenceContainer.i"

typedef vector<unsigned int> SequenceSelection;

%ignore SequenceContainerTools::SequenceContainerTools;
%ignore SequenceContainerTools::~SequenceContainerTools;

class SequenceContainerTools
{
  public:
    SequenceContainerTools();
    virtual ~SequenceContainerTools();

    static SequenceContainer * createContainerOfSpecifiedSize(const Alphabet * alphabet, int size);
    static SequenceContainer * createContainerWithSequenceNames(const Alphabet * alphabet, const vector<string> & seqNames) throw (Exception);
    static SequenceContainer * getSelectedSequences(const OrderedSequenceContainer & sequences, const SequenceSelection & selection);
    static void keepOnlySelectedSequences(OrderedSequenceContainer & sequences, const SequenceSelection & selection);
    static bool sequencesHaveTheSameLength(const SequenceContainer & sequences);
    static map<int, double> getFrequencies(const SequenceContainer & sequences);
    template<class T>static void append(T & seqCont1, const SequenceContainer & seqCont2) throw (Exception);
    template<class T>static void merge(const SequenceContainer& seqCont1, const SequenceContainer& seqCont2, T& seqCont) throw (Exception);
    template<class T> static T* convertAlphabet(const T & seqCont, const Alphabet *alphabet) throw (Exception);
};
