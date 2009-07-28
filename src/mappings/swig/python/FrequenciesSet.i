%module bpptest
%{
#include "FrequenciesSet.h"
using namespace bpp;
%}
%include "Parametrizable.i"
%include "VectorTools.i"
%include "AbstractParametrizable.i"
%include "Alphabet.i"
%include "NucleicAlphabet.i"
%include "ProteicAlphabet.i"
using namespace std;

class FrequenciesSet:public virtual Parametrizable
{
  public:
    FrequenciesSet * clone() const = 0;

    virtual const Alphabet * getAlphabet() const = 0;
    virtual const vector<double>& getFrequencies() const = 0;
    virtual void setFrequencies(const vector<double> & frequencies) throw (DimensionException, Exception) = 0;
};

class NucleotideFrequenciesSet:public virtual FrequenciesSet
{
  public:
    NucleotideFrequenciesSet * clone() const = 0;
};

class ProteinFrequenciesSet:public virtual FrequenciesSet
{
  public:
    ProteinFrequenciesSet * clone() const = 0;
};

class AbstractFrequenciesSet:public virtual FrequenciesSet, public AbstractParametrizable
{
  public:
    AbstractFrequenciesSet(unsigned int n, const Alphabet * alphabet, const string& prefix);

    const Alphabet * getAlphabet() const;
    const vector<double>& getFrequencies() const;
};

class FullFrequenciesSet:public AbstractFrequenciesSet
{
  public:
    FullFrequenciesSet(const Alphabet * alphabet, const string& name, const string& prefix = "");
    FullFrequenciesSet(const Alphabet * alphabet, const vector<double> & initFreqs, const string& name, const string& prefix = "") throw (Exception);
    FullFrequenciesSet * clone() const;

    void fireParameterChanged(const ParameterList & pl);
    void setFrequencies(const vector<double> & frequencies) throw (DimensionException, Exception);
};

class GCFrequenciesSet:public NucleotideFrequenciesSet, public AbstractFrequenciesSet
{
  public:
    GCFrequenciesSet(const NucleicAlphabet * alphabet, const string & prefix = "");
    GCFrequenciesSet(const NucleicAlphabet * alphabet, double theta, const string & prefix = "");
    GCFrequenciesSet * clone() const;

    void fireParameterChanged(const ParameterList & pl);
    void setFrequencies(const vector<double> & frequencies) throw (DimensionException);
};

class FullNAFrequenciesSet:public NucleotideFrequenciesSet, public AbstractFrequenciesSet
{
  public:
    FullNAFrequenciesSet(const NucleicAlphabet * alphabet, const string & prefix = "");
    FullNAFrequenciesSet(const NucleicAlphabet * alphabet, double theta, double theta1, double theta2, const string & prefix = "");
    FullNAFrequenciesSet * clone() const;

    void setFrequencies(const vector<double> & frequencies) throw (DimensionException, Exception);
    void fireParameterChanged(const ParameterList & pl);
};

class FullProteinFrequenciesSet:public ProteinFrequenciesSet, public AbstractFrequenciesSet
{
  public:
    FullProteinFrequenciesSet(const ProteicAlphabet * alphabet, const string & prefix = "");
    FullProteinFrequenciesSet(const ProteicAlphabet * alphabet, const vector<double> & initFreqs, const string & prefix = "") throw (Exception);
    FullProteinFrequenciesSet * clone() const;

    void setFrequencies(const vector<double> & frequencies) throw (DimensionException, Exception);
    void fireParameterChanged(const ParameterList & pl);
};

%rename(__assign__) MarkovModulatedFrequenciesSet::operator=;

class MarkovModulatedFrequenciesSet:public AbstractFrequenciesSet
{
  public:
    MarkovModulatedFrequenciesSet(const MarkovModulatedFrequenciesSet & mmfs);
    MarkovModulatedFrequenciesSet & operator=(const MarkovModulatedFrequenciesSet & mmfs);
    MarkovModulatedFrequenciesSet(FrequenciesSet * freqSet, const vector<double> & rateFreqs);
    MarkovModulatedFrequenciesSet * clone() const;
    virtual ~MarkovModulatedFrequenciesSet();

    void setFrequencies(const vector<double> & frequencies) throw (DimensionException);
    void fireParameterChanged(const ParameterList & pl);
    const FrequenciesSet* getStatesFrequenciesSet() const;
};

class FixedFrequenciesSet:public AbstractFrequenciesSet
{
  public:
    FixedFrequenciesSet(const Alphabet * alphabet, const vector<double>& initFreqs, const string & prefix = "");
    FixedFrequenciesSet * clone() const;
    void setFrequencies(const vector<double> & frequencies) throw (DimensionException);
   void fireParameterChanged(const ParameterList & pl);
};
