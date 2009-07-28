%module bpptest
%{
#include "Sequence.h"
using namespace bpp;
%}
%include "SymbolList.i"
%include "SequenceExceptions.i"
%include "std_string.i"
%include "std_vector.i"
using namespace std;

%rename(__assign__) Sequence::operator=;

typedef vector<string> Comments;
class Sequence:public SymbolList
{
  public: 
    Sequence(const string & name, const string & sequence, const Alphabet * alpha) throw (BadCharException);
    Sequence(const string & name, const string & sequence, const Comments comments, const Alphabet * alpha) throw (BadCharException);
    Sequence(const string & name, const vector<string> & sequence, const Alphabet * alpha) throw (BadCharException);
    Sequence(const string & name, const vector<string> & sequence, const Comments comments, const Alphabet * alpha) throw (BadCharException);
    Sequence(const string & name, const vector<int> & sequence, const Alphabet * alpha) throw (BadIntException);
    Sequence(const string & name, const vector<int> & sequence, const Comments comments, const Alphabet * alpha) throw (BadIntException);
    Sequence(const Sequence & s);
    Sequence & operator = (const Sequence & s);
    virtual ~Sequence();
    
    Sequence* clone() const;
    const string getName() const;
    void setName(const string & name);
    const Comments getComments() const;
    void setComments(const Comments & comments);
    bool getSense() const;
    void setSense(bool sense);
    void setContent(const string & sequence) throw (BadCharException);
    void setContent(const vector<int>    & list) throw (BadIntException);
    void setContent(const vector<string> & list) throw (BadCharException);
    void setToSizeR(unsigned int size);
    void setToSizeL(unsigned int size);
    void append(const vector<int> & content) throw (BadIntException);
    void append(const vector<string> & content) throw (BadCharException);
    void append(const string & content) throw (BadCharException);
};

