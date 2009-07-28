%module bpptest
%{
#include "TreeParsimonyScore.h"
using namespace bpp;
%}
%include "TreeTemplate.i"
%include "Clonable.i"
%include "std_vector.i"
using namespace std;

class TreeParsimonyScore:public virtual Clonable
{
  public:
    TreeParsimonyScore();
    virtual ~TreeParsimonyScore();
    TreeParsimonyScore * clone() const = 0;
    virtual unsigned int getScore() const = 0;
    virtual unsigned int getScoreForSite(unsigned int site) const = 0;
    virtual vector<unsigned int> getScoreForEachSite() const = 0;
    virtual const Tree * getTree() const = 0;
};
