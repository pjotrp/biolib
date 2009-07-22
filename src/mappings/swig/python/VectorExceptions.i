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
		VectorException(const char *   text, const vector<T> * vect = NULL) :
			Exception("VectorException: " + string(text)),
			_vect(vect);
		VectorException(const string & text, const vector<T> * vect = NULL) :
			Exception("VectorException: " + text),
			_vect(vect);
		virtual ~VectorException() throw ();

		virtual const vector<T> * getVector() const;
};
template<class T>
class EmptyVectorException : public VectorException<T>
{
	public:
		EmptyVectorException(const char *   text, const vector<T> * vect = NULL) :
			VectorException<T>("EmptyVectorException: " + string(text), vect);
		EmptyVectorException(const string & text, const vector<T> * vect = NULL) :
			VectorException<T>("EmptyVectorException: " + text, vect);
		virtual ~EmptyVectorException() throw ();
};
class DimensionException : public Exception
{
	public:
		DimensionException(const char *   text, unsigned int dimension, unsigned int correctDimension) :
			  Exception("DimensionException (found " + TextTools::toString(dimension) +", should be " + TextTools::toString(correctDimension) + string(text)),
        _dimension(dimension),
        _correctDimension(correctDimension);
		DimensionException(const string & text, unsigned int dimension, unsigned int correctDimension) :
		    Exception("DimensionException (found " + TextTools::toString(dimension) + ", should be " + TextTools::toString(correctDimension) + text),
        _dimension(dimension),
        _correctDimension(correctDimension);
		virtual ~DimensionException() throw ();

		virtual unsigned int getDimension() const;
		virtual unsigned int getCorrectDimension() const;
};
template<class T> class ElementNotFoundException : public VectorException<T>
{
	public:
		ElementNotFoundException(const char *   text, const vector<T> * vect = NULL, const T * element = NULL) :
			VectorException<T>("ElementNotFoundException: " + string(text), vect),
			_element(element);
		ElementNotFoundException(const string & text, const vector<T> * vect = NULL, const T * element = NULL) :
			VectorException<T>("ElementNotFoundException: " + text, vect),
			_element(element);
		virtual ~ElementNotFoundException() throw ();

		virtual const T * getElement() const;
};

