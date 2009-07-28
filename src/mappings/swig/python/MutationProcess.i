%module bpptest
%{
#include "MutationProcess.h"
using namespace bpp;
%}
%include "SubstitutionModel.i"
%include "VectorTools.i"

class MutationPath
{
  public:
    MutationPath(int initialState, double time);
    ~MutationPath();

    void addEvent(int state, double time);
    int getInitialState() const;
    double getTotalTime() const;
    unsigned int getNumberOfEvents() const;
    int getFinalState() const;
};

class MutationProcess
{
  public:
    MutationProcess();
    virtual ~MutationProcess();

    virtual int mutate(int state) const = 0;
    virtual int mutate(int state, unsigned int n) const = 0;
    virtual double getTimeBeforeNextMutationEvent(int state) const = 0;
    virtual int evolve(int initialState, double time) const = 0;
    virtual MutationPath detailedEvolve(int initialState, double time) const = 0;
    virtual const SubstitutionModel * getSubstitutionModel() const = 0;
};

class AbstractMutationProcess: public MutationProcess
{
  public:
    AbstractMutationProcess(const SubstitutionModel * model);
    virtual ~AbstractMutationProcess();

    int mutate(int state) const;
    int mutate(int state, unsigned int n) const;
    double getTimeBeforeNextMutationEvent(int state) const;
    int evolve(int initialState, double time) const;
    MutationPath detailedEvolve(int initialState, double time) const;
    const SubstitutionModel * getSubstitutionModel() const;
};

class SimpleMutationProcess : public AbstractMutationProcess
{
  public: 
    SimpleMutationProcess(const SubstitutionModel * model);
    virtual ~SimpleMutationProcess();
    int evolve(int initialState, double time) const;
};

class SelfMutationProcess : public AbstractMutationProcess
{
    public:
      SelfMutationProcess(int alphabetSize);
      virtual ~SelfMutationProcess();
};
