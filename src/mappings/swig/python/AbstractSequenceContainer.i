%module bpptest
%{
#include "AbstractSequenceContainer.h"
using namespace bpp;
%}

%include "Sequence.i"
%include "SequenceContainer.i"
%include "OrderedSequenceContainer.i"
%include "Alphabet.i"

%include "Exceptions.i"

class AbstractSequenceContainer : public virtual OrderedSequenceContainer
{
  public:
    AbstractSequenceContainer(const Alphabet * alpha);
    virtual ~AbstractSequenceContainer();

    const Alphabet * getAlphabet() const;
    vector<int> getContent(const string & name) const throw (SequenceNotFoundException);
    string toString(const string & name) const throw (SequenceNotFoundException);
    Comments getComments(const string & name) const throw (SequenceNotFoundException);
    void setComments(const string & name, const Comments & comments) throw (SequenceNotFoundException);
    Comments getGeneralComments() const;
    void setGeneralComments(const Comments & comments);
    void deleteGeneralComments();
    virtual string getName(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException);
    virtual vector<int> getContent(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException);
    virtual string toString(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException);
    virtual Comments getComments(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException);
    virtual void     setComments(unsigned int sequenceIndex, const Comments & comments) throw (IndexOutOfBoundsException) = 0;
};
