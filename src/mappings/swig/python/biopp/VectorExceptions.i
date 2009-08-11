%module bpp_
%{
#include "VectorExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"
%include "TextTools.i"
%include "std_vector.i"
using namespace std;

template<class T>
class VectorException : public Exception
{
  public:
    VectorException(const char *   text, const vector<T> * vect = NULL);
    VectorException(const string & text, const vector<T> * vect = NULL);
    virtual ~VectorException() throw ();
    virtual const vector<T> * getVector() const;
};

%template(intVectorException) VectorException<int>;
%template(doubleVectorException) VectorException<double>;

template<class T>
class EmptyVectorException : public VectorException<T>
{
  public:
    EmptyVectorException(const char *   text, const vector<T> * vect = NULL);
    EmptyVectorException(const string & text, const vector<T> * vect = NULL);
    virtual ~EmptyVectorException() throw ();
};

%template(intEmptyVectorException) EmptyVectorException<int>;
%template(doubleEmptyVectorException) EmptyVectorException<double>;

class DimensionException : public Exception
{
  public:
    DimensionException(const char *   text, unsigned int dimension, unsigned int correctDimension);
    DimensionException(const string & text, unsigned int dimension, unsigned int correctDimension);
    virtual ~DimensionException() throw ();

    virtual unsigned int getDimension() const;
    virtual unsigned int getCorrectDimension() const;
};

template<class T> class ElementNotFoundException : public VectorException<T>
{
  public:
    ElementNotFoundException(const char *   text, const vector<T> * vect = NULL, const T * element = NULL);
    ElementNotFoundException(const string & text, const vector<T> * vect = NULL, const T * element = NULL);
    virtual ~ElementNotFoundException() throw ();

    virtual const T * getElement() const;
};

%template(intElementNotFoundException) ElementNotFoundException<int>;
%template(doubleElementNotFoundException) ElementNotFoundException<double>;
