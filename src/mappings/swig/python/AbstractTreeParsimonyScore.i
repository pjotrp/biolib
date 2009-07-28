%module bpptest
%{
#include "AbstractTreeParsimonyScore.h"
using namespace bpp;
%}
%include "TreeParsimonyScore.i"
%include "Node.i"
%include "SiteContainer.i"

%rename(__assign__) AbstractTreeParsimonyScore::operator=;

class AbstractTreeParsimonyScore :public virtual TreeParsimonyScore
{
    AbstractTreeParsimonyScore(const Tree & tree, const SiteContainer & data, bool verbose) throw (Exception);
    AbstractTreeParsimonyScore(const AbstractTreeParsimonyScore & tp);
    AbstractTreeParsimonyScore & operator=(const AbstractTreeParsimonyScore & tp);
    virtual ~AbstractTreeParsimonyScore();

    virtual const Tree * getTree() const;
    virtual vector<unsigned int> getScoreForEachSite() const;
};
