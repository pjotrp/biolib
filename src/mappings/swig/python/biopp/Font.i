%module bpp_font
%{
using namespace std;
#include "TextTools.h"
#include "Font.h"
using namespace bpp;
%}

%include "Clonable.i"

%rename(__eq__) Font::operator==;

class Font:public virtual Clonable
{
  public:
    Font(const string & family, const string & type, unsigned int size);
    Font(const string & family = "default", const string & series = "default", const string & type = "", unsigned int size = 12);
    virtual ~Font();

    Font *clone() const;
    
    bool operator==(const Font & font);
    const string & getFamily() const;
    const string & getSeries() const;
    const string & getType() const;
    const unsigned int & getSize() const;
    void setFamily(const string & family);
    void setSeries(const string & series);
    void setType(const string & type);
    void setSize(unsigned int size);
    string toString() const;
};
