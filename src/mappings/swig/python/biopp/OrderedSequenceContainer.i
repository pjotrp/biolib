%module bpptest
%{
#include "OrderedSequenceContainer.h"
using namespace bpp;
%}

%include "Sequence.i"
%include "SequenceContainer.i"

class OrderedSequenceContainer:public virtual SequenceContainer
{
  public:
    OrderedSequenceContainer();
    virtual ~OrderedSequenceContainer();
    
    virtual vector<int> getContent(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;
    virtual string toString(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;
    virtual const Sequence * getSequence(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;
    virtual void setSequence(unsigned int sequenceIndex, const Sequence & sequence, bool checkName) throw (Exception) = 0;
    virtual Sequence * removeSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException) = 0;
    virtual void deleteSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException) = 0;
    virtual string getName(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;
    virtual Comments getComments(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException) = 0;
    virtual void setComments(unsigned int sequenceIndex, const Comments & comments) throw (IndexOutOfBoundsException) = 0;
    virtual unsigned int getSequencePosition(const string & name) const throw (SequenceNotFoundException) = 0;
    virtual int & valueAt(unsigned int sequenceIndex, unsigned int elementIndex) throw (IndexOutOfBoundsException) = 0;
    virtual const int & valueAt(unsigned int sequenceIndex, unsigned int elementIndex) const throw (IndexOutOfBoundsException) = 0;
    virtual int & operator()(unsigned int sequenceIndex, unsigned int elementIndex) = 0;
    virtual const int & operator()(unsigned int sequenceIndex, unsigned int elementIndex) const = 0;
    virtual vector<int> getContent(const string & name) const throw (SequenceNotFoundException) = 0;  
    virtual string toString(const string & name) const throw (SequenceNotFoundException) = 0;  
    virtual const Sequence * getSequence(const string & name) const throw (SequenceNotFoundException) = 0;
    virtual void setSequence(const string & name, const Sequence & sequence, bool checkName) throw (Exception) = 0;
    virtual Sequence * removeSequence(const string & name) throw (SequenceNotFoundException) = 0;
    virtual void deleteSequence(const string & name) throw (SequenceNotFoundException) = 0;
    virtual unsigned int getNumberOfSequences() const = 0;
    virtual vector<string> getSequencesNames() const = 0;
    virtual void setSequencesNames(const vector<string> & names, bool checkNames) throw (Exception) = 0;
    virtual Comments getComments(const string & name) const throw (SequenceNotFoundException) = 0;
    virtual void setComments(const string & name, const Comments & comments) throw (SequenceNotFoundException) = 0;
    
};

