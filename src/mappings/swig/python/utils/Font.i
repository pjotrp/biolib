%module bpp_font
%{
#include "Clonable.h"
%}

%include "Clonable.i"

namespace bpp
{

%rename(__eq__) RGBColor::operator==;

class Font:
  public virtual Clonable
{
  protected:
    string _family;
    string _series;
    string _type;
    unsigned int _size;

  public:
    Font(const string & family, const string & type, unsigned int size):
      _family(family), _series(), _type(type), _size(size) {}

    Font(const string & family = "default", const string & series = "default", const string & type = "", unsigned int size = 12):
      _family(family), _series(series), _type(type), _size(size) {}

    virtual ~Font() {}

#ifdef NO_VIRTUAL_COV
    Clonable *
#else
    Font *
#endif
    clone() const { return new Font(*this); }
    
  public:
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

} // end of namespace bpp.
