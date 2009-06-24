%module bpp_colorset
%{
#include "RGBColor.h"
#include "MapTools.h"
#include <vector>
%}

%include "RGBColor.i"
%include "MapTools.i"
%include "std_vector.i"

using namespace std;

namespace bpp
{

class ColorSet
{
  public:
    ColorSet() {}
    virtual ~ColorSet() {}

  public:
    virtual const RGBColor& getColor(const string & name) const throw (Exception) = 0;
    virtual const RGBColor& getColor(unsigned int index) const throw (IndexOutOfBoundsException) = 0;
    virtual vector<string> getColorNames() const = 0;
    virtual unsigned int getNumberOfColors() const = 0;
};


class AbstractColorSet:
  public ColorSet
{
  protected:
    map<string, RGBColor> _colors;

  public:
    const RGBColor& getColor(const string & name) const throw (Exception)
    {
      map<string, RGBColor>::const_iterator it = _colors.find(name);
      if(it != _colors.end()) return it->second;
      else throw Exception("AbstractColorSet::getColor(name): no color with name " + name);
    }

    const RGBColor& getColor(unsigned int index) const throw (IndexOutOfBoundsException)
    {
      if(index >= _colors.size()) throw IndexOutOfBoundsException("AbstractColorSet::getColor(index): invalid index.", index, 0, _colors.size() - 1);
      map<string, RGBColor>::const_iterator it = _colors.begin();
      for(unsigned int i = 0; i < index; i++) it++;
      return it->second;
    }
    
    vector<string> getColorNames() const { return MapTools::getKeys(_colors); }
    unsigned int getNumberOfColors() const { return _colors.size(); }
};

} // end of namespace bpp;
