%module bpptest
%{
#include "SubstitutionModelFactory.h"
using namespace bpp;
%}
%include "models"
%include "Tree.i"
%include "Alphabet.i"
%include "AlphabetExceptions.i"
%include "std_string.i"
using namespace std;

class SubstitutionModelFactory
{
  public:
    static const string JUKES_CANTOR;
    static const string KIMURA_2P;
    static const string HASEGAWA_KISHINO_YANO;
    static const string TAMURA_NEI;
    static const string GENERAL_TIME_REVERSIBLE;
    static const string TAMURA;
    static const string FELSENSTEIN84;
    static const string JOHN_TAYLOR_THORNTON;
    static const string DAYHOFF_SCHWARTZ_ORCUTT;

    SubstitutionModelFactory(const Alphabet * alphabet);
    virtual ~SubstitutionModelFactory();

    virtual SubstitutionModel * createModel(const string& modelName) const throw (AlphabetException, Exception);
};
