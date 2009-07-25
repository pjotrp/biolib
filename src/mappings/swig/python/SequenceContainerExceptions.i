%module bpptest
%{
#include "SequenceContainerExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"

class SequenceContainer;
class SequenceNotFoundException : public Exception
{
  public:
    SequenceNotFoundException(const char * text, const char * seqId = "") : Exception("SequenceNotFoundException: " + string(text) + "(" + seqId + ")"), id(seqId);
    SequenceNotFoundException(const string & text, const string & seqId = "") : Exception("SequenceNotFoundException: " + text + "(" + seqId + ")"), id(seqId);
    virtual ~SequenceNotFoundException() throw();

    virtual const string getSequenceId() const;
};

class EmptyContainerException : public Exception
{
  public:
    EmptyContainerException(const char * text, const SequenceContainer * container) : Exception("EmptyContainerException: " + string(text)), _container(container);
    EmptyContainerException(const string & text, const SequenceContainer * container) : Exception("EmptyContainerException: " + text), _container(container);
    virtual ~EmptyContainerException() throw();

    virtual const SequenceContainer * getContainer() const;
};
