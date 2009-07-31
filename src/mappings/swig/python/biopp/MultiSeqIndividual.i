%module bpptest
%{
#include "MultiSeqIndividual.h"
using namespace bpp;
%}
%include "std_map.i"
%include "std_vector.i"
using namespace std;
%include "Clonable.i"
%include "Exceptions.i"
%include "Sequence.i"
%include "VectorSequenceContainer.i"
%include "SequenceExceptions.i"
%include "Locality.i"
%include "Coord.i"
%include "Date.i"
%include "MultilocusGenotype.i"
%include "GeneralExceptions.i"

%rename(__assign__) MultiSeqIndividual::operator=;

class MultiSeqIndividual
{
  public: 
    MultiSeqIndividual();
    MultiSeqIndividual(const string & id);
    MultiSeqIndividual(const string & id, const Date & date, const Coord<double> & coord, Locality<double> * locality, const unsigned short sex);
    MultiSeqIndividual(const MultiSeqIndividual &ind);
    virtual ~MultiSeqIndividual();

    MultiSeqIndividual & operator= (const MultiSeqIndividual & ind);
    void setId(const string id);
    string getId() const;
    void setSex(const unsigned short sex);
    unsigned short getSex() const;
    void setDate(const Date & date);
    const Date * getDate() const throw (NullPointerException);
    bool hasDate() const;
    void setCoord(const Coord<double> & coord);
    void setCoord(const double x, const double y);
    const Coord<double> * getCoord() const throw(NullPointerException);
    bool hasCoord() const;
    void setX(const double x) throw(NullPointerException);
    void setY(const double y) throw(NullPointerException);
    double getX() const throw(NullPointerException);
    double getY() const throw(NullPointerException);
    void setLocality(const Locality<double> * locality);
    const Locality<double> * getLocality() const throw (NullPointerException);
    bool hasLocality() const;
    const VectorSequenceContainer * getVectorSequenceContainer(const string & id) const throw (Exception);
    void addSequence(const string & id, const Sequence & sequence) throw (Exception);
    const Sequence * getSequence(const string & id, const string & name) const throw(Exception);
    const Sequence * getSequence(const string & id, const unsigned int i) const throw(Exception);
    vector<string> getSequencesKeys() const;
    Sequence * removeSequence(const string & id, const string & name);
    void deleteSequence(const string & id, const string & name);
    bool hasSequences() const;
    unsigned int getNumberOfSequenceSet() const;
    unsigned int getNumberOfSequences(const string & id) const throw (Exception);
    void addGenotype(const MultilocusGenotype & genotype);
    const MultilocusGenotype * getGenotype() const throw (NullPointerException);
    bool hasGenotype() const;
};
