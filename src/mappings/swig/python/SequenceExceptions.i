%module bpptest
%{
#include "SequenceExceptions.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "Exceptions.i"

class Sequence;
class SequenceException:public Exception
{
  public:
    SequenceException(const char * text, const Sequence * seq = NULL);
    SequenceException(const string & text, const Sequence * seq = NULL);
    virtual ~SequenceException() throw();

    virtual const Sequence * getSequence() const;
};

class EmptySequenceException : public SequenceException {
  public:
    EmptySequenceException(const char * text, const Sequence * seq = NULL);
    EmptySequenceException(const string & text, const Sequence * seq = NULL);
    virtual ~EmptySequenceException() throw();
};

class SequenceWithGapException : public SequenceException {
  public:
    SequenceWithGapException(const char *   text, const Sequence * seq = NULL);
    SequenceWithGapException(const string & text, const Sequence * seq = NULL);
    virtual ~SequenceWithGapException() throw();
};

class SequenceNotAlignedException : public SequenceException {
  public:
    SequenceNotAlignedException(const char * text, const Sequence * seq);
    SequenceNotAlignedException(const string & text, const Sequence * seq);
    virtual ~SequenceNotAlignedException() throw();
};
