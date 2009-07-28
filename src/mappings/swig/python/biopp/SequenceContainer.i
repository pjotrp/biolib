%module bpptest
%{
#include "SequenceContainer.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "Sequence.i"
%include "SequenceContainerExceptions.i"
%include "Clonable.i"
//#include <cstdlib>
using namespace std;

class SequenceContainer: public virtual Clonable
{
  public:
    SequenceContainer();
    virtual ~SequenceContainer();

    virtual const Alphabet * getAlphabet() const = 0;
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
    virtual Comments getGeneralComments() const = 0;
    virtual void setGeneralComments(const Comments & comments) = 0;
    virtual void deleteGeneralComments() = 0;
    virtual void clear() = 0;
    virtual SequenceContainer * createEmptyContainer() const = 0;
    virtual int & valueAt(const string & sequenceName, unsigned int elementIndex) throw (SequenceNotFoundException, IndexOutOfBoundsException) = 0;
    virtual const int & valueAt(const string & sequenceName, unsigned int elementIndex) const throw (SequenceNotFoundException, IndexOutOfBoundsException) = 0;
    virtual int & operator()(const string & sequenceName, unsigned int elementIndex) = 0;
    virtual const int & operator()(const string & sequenceName, unsigned int elementIndex) const = 0;
};
