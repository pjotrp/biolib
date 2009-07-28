%module bpptest
%{
#include "Newick.h"
using namespace bpp;
%}
%include "IOTree.i"
%include "TreeTemplate.i"

class Newick:public virtual AbstractITree,public virtual AbstractOTree,public virtual AbstractIMultiTree,public virtual AbstractOMultiTree
{
  public:
    Newick(bool allowComments = false, bool writeId = false);
    virtual ~Newick();

    void enableExtendedBootstrapProperty(const string & propertyName);
    void disableExtendedBootstrapProperty();
    const string getFormatName() const;
    const string getFormatDescription() const;
    TreeTemplate<Node> * read(const string & path) const throw (Exception);
    TreeTemplate<Node> * read(istream & in) const throw (Exception);
    void write(const Tree & tree, const string & path, bool overwrite = true) const throw (Exception);
    void write(const Tree & tree, ostream & out) const throw (Exception);
    void read(const string & path, vector<Tree *> & trees) const throw (Exception);
    void read(istream & in, vector<Tree *> & trees) const throw (Exception);
    void write(const vector<Tree *> & trees, const string & path, bool overwrite = true) const throw (Exception);
    void write(const vector<Tree *> & trees, ostream & out) const throw (Exception);
};
