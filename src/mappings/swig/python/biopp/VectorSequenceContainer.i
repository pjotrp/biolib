%module bpptest
%{
#include "VectorSequenceContainer.h"
using namespace bpp;
%}
%include "Sequence.i"
%include "AbstractSequenceContainer.i"
%include "Alphabet.i"
%include "Exceptions.i"
//#include <algorithm>
%include "std_vector.i"
using namespace std;

%rename(__assign__) VectorSequenceContainer::operator=;

class VectorSequenceContainer:public AbstractSequenceContainer
{
  public:  
    VectorSequenceContainer(const vector<const Sequence *> & vs, const Alphabet * alpha) throw (AlphabetMismatchException);
    VectorSequenceContainer(const Alphabet * alpha);
    VectorSequenceContainer(const VectorSequenceContainer & vsc);
    VectorSequenceContainer(const OrderedSequenceContainer & osc);
    VectorSequenceContainer(const SequenceContainer & osc);
    VectorSequenceContainer & operator = (const VectorSequenceContainer & vsc);
    VectorSequenceContainer & operator = (const OrderedSequenceContainer & osc);
    VectorSequenceContainer & operator = (const SequenceContainer & osc);
    virtual ~VectorSequenceContainer();

    Clonable * clone() const;
    const Sequence * getSequence(const string & name) const throw (SequenceNotFoundException);
    void setSequence(const string & name, const Sequence & sequence, bool checkName = true) throw (Exception);
    Sequence * removeSequence(const string & name) throw (SequenceNotFoundException);
    void deleteSequence(const string & name) throw (SequenceNotFoundException);
    unsigned int getNumberOfSequences() const;
    vector<string> getSequencesNames() const;
    void setSequencesNames(const vector<string> & names, bool checkNames = true) throw (Exception);
    void clear();
    SequenceContainer * createEmptyContainer() const;
    int & valueAt(const string & sequenceName, unsigned int elementIndex) throw (SequenceNotFoundException, IndexOutOfBoundsException);
    const int & valueAt(const string & sequenceName, unsigned int elementIndex) const throw (SequenceNotFoundException, IndexOutOfBoundsException);
    int & operator()(const string & sequenceName, unsigned int elementIndex);
    const int & operator()(const string & sequenceName, unsigned int elementIndex) const;
    int & valueAt(unsigned int sequenceIndex, unsigned int elementIndex) throw (IndexOutOfBoundsException);
    const int & valueAt(unsigned int sequenceIndex, unsigned int elementIndex) const throw (IndexOutOfBoundsException);
    int & operator()(unsigned int sequenceIndex, unsigned int elementIndex);
    const int & operator()(unsigned int sequenceIndex, unsigned int elementIndex) const;
    void setComments(const string & name, const Comments & comments) throw (SequenceNotFoundException);
    void setComments(unsigned int sequenceIndex, const Comments & comments) throw (IndexOutOfBoundsException);
    unsigned int getSequencePosition(const string & name) const throw (SequenceNotFoundException);
    const Sequence *getSequence(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException);
    void setSequence(unsigned int sequenceIndex, const Sequence & sequence, bool checkName = true) throw (Exception);
    Sequence * removeSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException);
    void deleteSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException);
    virtual void addSequence(const Sequence & sequence, bool checkName = true) throw (Exception);
    virtual void addSequence(const Sequence & sequence, unsigned int sequenceIndex, bool checkName = true) throw (Exception);

    // This is another (pseudo-)constructor, for vectors of Sequences that aren't const
  %extend {
    VectorSequenceContainer(const vector<Sequence *> vs, const Alphabet * alpha) throw (AlphabetMismatchException)
    {
      vector<const Sequence *> *newVs = new vector<const Sequence *>(vs.size());
      for (int i=0; i<vs.size(); i++) (*newVs)[i] = (const Sequence *)vs[i];
      return new VectorSequenceContainer(*newVs, alpha);
    }
  }
};
 
