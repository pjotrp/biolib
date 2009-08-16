%module bpptest
%{
#include "SymbolList.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "Clonable.i"
%include "std_string.i"
%include "std_vector.i"
using namespace std;

%rename(__assign__) SymbolList::operator=;
%rename(__aref__) SymbolList::operator[];

class SymbolList:public virtual Clonable
{
    %rename(intVecSymbolList) SymbolList(const vector<int> & list, const Alphabet * alpha) throw (BadCharException);
    %rename(intVecSetContent) setContent(const vector<int> & list) throw (BadCharException);
  public: 
    SymbolList(const Alphabet * alpha);
    SymbolList(const vector<string> & list, const Alphabet * alpha) throw (BadCharException);
    SymbolList(const vector<int> & list, const Alphabet * alpha) throw (BadIntException);
    SymbolList(const SymbolList & list);
    SymbolList & operator = (const SymbolList & list);
    SymbolList* clone() const;
    virtual ~SymbolList();

    virtual const Alphabet* getAlphabet() const;
    virtual unsigned int size() const;
    virtual const vector<int>& getContent() const;
    virtual void setContent(const vector<int> & list) throw (BadIntException);
    virtual void setContent(const vector<string> & list) throw (BadCharException);
    virtual string toString() const;
    virtual void addElement(string c) throw (BadCharException);
    virtual void addElement(unsigned int pos, string c) throw (BadCharException, IndexOutOfBoundsException);
    virtual void setElement(unsigned int pos, string c) throw (BadCharException, IndexOutOfBoundsException);
    virtual void deleteElement(unsigned int pos) throw (IndexOutOfBoundsException);
    virtual string getChar(unsigned int pos) const throw (IndexOutOfBoundsException);
    virtual void addElement(int v) throw (BadIntException);
    virtual void addElement(unsigned int pos, int v) throw (BadIntException, IndexOutOfBoundsException);
    virtual void setElement(unsigned int pos, int v) throw (BadIntException, IndexOutOfBoundsException);
    virtual int getValue(unsigned int pos) const throw (IndexOutOfBoundsException);
    virtual const int & operator[](unsigned int i) const;
    virtual int & operator[](unsigned int i);
};
