%module bpptest
%{
#include "NodeTemplate.h"
using namespace bpp;
%}

%include "Node.i"

%rename(__assign__) *::operator=;
%rename(__aref__) *::operator[];

template<class NodeInfos>
class NodeTemplate : public Node
{
  public:
    NodeTemplate() : Node();
    NodeTemplate(int id) : Node(id);
    NodeTemplate(const string & name) : Node(name);
    NodeTemplate(int id, const string & name) : Node(id, name);
    NodeTemplate(const Node & node) : Node(node);
    NodeTemplate(const NodeTemplate<NodeInfos> & node);
    NodeTemplate<NodeInfos> & operator=(const NodeTemplate<NodeInfos> & node);
    virtual ~NodeTemplate();
    NodeTemplate<NodeInfos> * clone() const;

    const NodeTemplate<NodeInfos> * getFather() const;
    NodeTemplate<NodeInfos> * getFather();
    NodeTemplate<NodeInfos> * removeFather();
    const NodeTemplate<NodeInfos> * getSon(unsigned int i) const throw (IndexOutOfBoundsException);
    NodeTemplate<NodeInfos> * getSon(unsigned int i) throw (IndexOutOfBoundsException);
    vector<const NodeTemplate<NodeInfos> *> getNeighbors() const;
    vector<NodeTemplate<NodeInfos> *> getNeighbors();
    NodeTemplate<NodeInfos> * operator[](int i);
    const NodeTemplate<NodeInfos> * operator[](int i) const;
    virtual const NodeInfos & getInfos() const;
    virtual NodeInfos & getInfos();
    virtual void setInfos(const NodeInfos & infos);
};

%template(intNodeTemplate) NodeTemplate<int>;
%template(doubleNodeTemplate) NodeTemplate<double>;
