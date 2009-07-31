%module bpptest
%{
#include "GeneralExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"

class BadIdentifierException:public Exception
{
  public:
    BadIdentifierException(const char *text, const unsigned int id);
    BadIdentifierException(const string &text, const unsigned int id);
    BadIdentifierException(const char *text, const string &id);
    BadIdentifierException(const string &text, const string &id);
    ~BadIdentifierException() throw();

    virtual const string getIdentifier() const;
};

class LocusNotFoundException:public BadIdentifierException
{
  public:
    LocusNotFoundException(const char *text, const unsigned int id);
    LocusNotFoundException(const string &text, const unsigned int id);
    LocusNotFoundException(const char *text, const string &id);
    LocusNotFoundException(const string &text, const string &id);
    ~LocusNotFoundException() throw();

    virtual const string getIdentifier() const;
};

class AlleleNotFoundException:public BadIdentifierException
{
  public:
    AlleleNotFoundException(const char *text, const unsigned int id);
    AlleleNotFoundException(const string &text, const unsigned int id);
    AlleleNotFoundException(const char *text, const string &id);
    AlleleNotFoundException(const string &text, const string &id);
    ~AlleleNotFoundException() throw();

    virtual const string getIdentifier() const;
};

class LocalityNotFoundException:public BadIdentifierException
{
  public:
    LocalityNotFoundException(const char *text, const unsigned int id);
    LocalityNotFoundException(const string &text, const unsigned int id);
    LocalityNotFoundException(const char *text, const string &id);
    LocalityNotFoundException(const string &text, const string &id);
    ~LocalityNotFoundException() throw();

    virtual const string getIdentifier() const;
};

class IndividualNotFoundException:public BadIdentifierException
{
  public:
    IndividualNotFoundException(const char *text, const unsigned int id);
    IndividualNotFoundException(const string &text, const unsigned int id);
    IndividualNotFoundException(const char *text, const string &id);
    IndividualNotFoundException(const string &text, const string &id);
    ~IndividualNotFoundException() throw();

    virtual const string getIdentifier() const;
};

class GroupNotFoundException:public BadIdentifierException
{
  public:
    GroupNotFoundException(const char *text, const unsigned int id);
    GroupNotFoundException(const string &text, const unsigned int id);
    GroupNotFoundException(const char *text, const string &id);
    GroupNotFoundException(const string &text, const string &id);
    ~GroupNotFoundException() throw();

    virtual const string getIdentifier() const;
};
