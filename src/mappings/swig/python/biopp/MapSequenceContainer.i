%module bpptest
%{
#include "MapSequenceContainer.h"
using namespace bpp;
%}

%include "Sequence.i"
%include "AbstractSequenceContainer.i"
%include "Alphabet.i"

%include "std_string.i"
%include "std_map.i"

using namespace std;

%rename(__assign__) MapSequenceContainer::operator=;

class MapSequenceContainer:public AbstractSequenceContainer
{
  public:
    MapSequenceContainer(const map<string, Sequence *> & ms, const Alphabet * alpha);
    MapSequenceContainer(const Alphabet * alpha);
    MapSequenceContainer(const MapSequenceContainer & msc);
    MapSequenceContainer & operator = (const MapSequenceContainer & msc);
    virtual ~MapSequenceContainer();

    const Sequence * getSequenceByKey(const string & key)  const throw (SequenceNotFoundException);
    void setSequenceByKey(const string & key , const Sequence & sequence, bool checkNames = true) throw (SequenceNotFoundException);
    Sequence * removeSequenceByKey(const string & key) throw (SequenceNotFoundException);
    void deleteSequenceByKey(const string & key) throw (SequenceNotFoundException);
    void addSequence(const string & key, const Sequence & sequence, bool checkNames = true) throw (Exception);
    vector<string> getKeys() const;
    string getKey(unsigned int pos) const throw (IndexOutOfBoundsException);
    string getKey(const string & name) const throw (SequenceNotFoundException);
    Clonable * clone() const;
    const Sequence * getSequence(const string & name) const throw (SequenceNotFoundException);
    void setSequence(const string & name, const Sequence & sequence, bool checkName = true) throw (SequenceNotFoundException);
    Sequence * removeSequence(const string & name) throw (SequenceNotFoundException);
    void deleteSequence(const string & name) throw (SequenceNotFoundException);
    unsigned int getNumberOfSequences() const;
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
    const Sequence * getSequence(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException);
    unsigned int     getSequencePosition(const string & name) const throw (SequenceNotFoundException);
    void             setSequence(unsigned int sequenceIndex, const Sequence & sequence, bool checkName = true) throw (IndexOutOfBoundsException);
    Sequence *    removeSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException);
    void          deleteSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException);
    void setComments(unsigned int sequenceIndex, const Comments & comments) throw (IndexOutOfBoundsException);
    vector<string> getSequencesNames() const;
    void setSequencesNames(const vector<string> & names, bool checkNames) throw (Exception);
    Sequence * getSequenceInner(unsigned int i)      throw (IndexOutOfBoundsException);
    Sequence * getSequenceInner(const string & name) throw (SequenceNotFoundException);
    
};
