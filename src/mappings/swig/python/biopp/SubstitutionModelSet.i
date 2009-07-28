%module bpptest
%{
#include "SubstitutionModelSet.h"
using namespace bpp;
%}
%include "Tree.i"
%include "SubstitutionModel.i"
%include "AbstractSubstitutionModel.i"
%include "FrequenciesSet.i"
%include "RandomTools.i"
%include "VectorTools.i"
%include "Exceptions.i"
%include "Alphabet.i"
%include "NucleicAlphabet.i"
%include "std_vector.i"
%include "std_map.i"
//#include <algorithm>
using namespace std;

%rename(__assign__) SubstitutionModelSet::operator=;

class SubstitutionModelSet: public AbstractParametrizable
{
  public:
    SubstitutionModelSet(const Alphabet *alpha);
    SubstitutionModelSet(const Alphabet* alpha, FrequenciesSet* rootFreqs);
    SubstitutionModelSet(const SubstitutionModelSet & set);
    SubstitutionModelSet & operator=(const SubstitutionModelSet & set);
    virtual ~SubstitutionModelSet();
    SubstitutionModelSet* clone() const;

    unsigned int getNumberOfStates() const throw (Exception);
    unsigned int getParameterIndex(const string & name) const throw (ParameterNotFoundException);
    string getParameterModelName(const string & name) const throw (ParameterNotFoundException, Exception);
    void fireParameterChanged(const ParameterList & parameters);
    unsigned int getNumberOfModels() const;
    const SubstitutionModel * getModel(unsigned int i) const throw (IndexOutOfBoundsException);
    unsigned int getModelIndexForNode(int nodeId) const throw (Exception);
    const SubstitutionModel * getModelForNode(int nodeId) const throw (Exception);
    SubstitutionModel * getModelForNode(int nodeId) throw (Exception);
    const vector<int> & getNodesWithModel(unsigned int i) const throw (IndexOutOfBoundsException);
    vector<int> getNodesWithParameter(const string & name) const throw (ParameterNotFoundException);
    vector<unsigned int> getModelsWithParameter(const string & name) const throw (ParameterNotFoundException);
    void addModel(SubstitutionModel * model, const vector<int> & nodesId, const vector<string> & newParams) throw (Exception);
    void setModel(SubstitutionModel * model, unsigned int modelIndex) throw (Exception, IndexOutOfBoundsException);
    void setModelToNode(unsigned int modelIndex, int nodeNumber) throw (IndexOutOfBoundsException);
    void setParameterToModel(unsigned int parameterIndex, unsigned int modelIndex) throw (IndexOutOfBoundsException);
    void unsetParameterToModel(unsigned int parameterIndex, unsigned int modelIndex) throw (IndexOutOfBoundsException, Exception);
    void addParameter(const Parameter & parameter, const vector<int> & nodesId) throw (Exception);
    void addParameters(const ParameterList & parameters, const vector<int> & nodesId) throw (Exception);
    void removeParameter(const string & name) throw (ParameterNotFoundException);
    void removeModel(unsigned int modelIndex) throw (Exception);
    void listModelNames(ostream & out = cout) const;
    const FrequenciesSet* getRootFrequenciesSet() const;
    vector<double> getRootFrequencies() const;
    ParameterList getRootFrequenciesParameters() const;
    ParameterList getNodeParameters() const;
    const Alphabet * getAlphabet() const;
    bool isFullySetUpFor(const Tree& tree, bool throwEx = true) const throw (Exception);
};
