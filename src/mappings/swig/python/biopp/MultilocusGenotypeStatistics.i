%module bpptest
%{
#include "MultilocusGenotypeStatistics.h"
using namespace bpp;
%}
//#include <cmath>
%include "std_vector.i"
%include "std_map.i"
//#include <set>
//#include <algorithm>
using namespace std;
%include "Exceptions.i"
%include "MapTools.i"
%include "DistanceMatrix.i"
%include "PolymorphismMultiGContainer.i"
%include "MultilocusGenotype.i"
%include "GeneralExceptions.i"

class MultilocusGenotypeStatistics
{
  public:
    /*struct VarComp
    {
      double a;
      double b;
      double c;
    };
    struct Fstats
    {
      double Fit;
      double Fst;
      double Fis;
    };
    struct PermResults{
      double Statistic;
      double Percent_sup;
      double Percent_inf;
    };*/
    static vector<unsigned int> getAllelesIdsForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (IndexOutOfBoundsException);
    static unsigned int countGametesForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (IndexOutOfBoundsException);
    static map<unsigned int, unsigned int> getAllelesMapForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (IndexOutOfBoundsException);
    static map<unsigned int, double> getAllelesFrqForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    static unsigned int countNonMissingForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (IndexOutOfBoundsException);
    static unsigned int countBiAllelicForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (IndexOutOfBoundsException);
    static map<unsigned int, unsigned int> countHeterozygousForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (IndexOutOfBoundsException);
    static map<unsigned int, double> getHeterozygousFrqForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    static double getHobsForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    static double getHexpForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    static double getHnbForGroups(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    static double getDnei72(const PolymorphismMultiGContainer & pmgc, vector<unsigned int> locus_positions, unsigned int grp1, unsigned int grp2) throw (Exception);
    static double getDnei78(const PolymorphismMultiGContainer & pmgc, vector<unsigned int> locus_positions, unsigned int grp1, unsigned int grp2) throw (Exception);
    //static map<unsigned int, Fstats>  getAllelesFstats(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    static map<unsigned int, double> getAllelesFit(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    static map<unsigned int, double> getAllelesFst(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    static map<unsigned int, double> getAllelesFis(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (Exception);
    //static map<unsigned int, VarComp> getVarianceComponents(const PolymorphismMultiGContainer & pmgc, unsigned int locus_position, const set<unsigned int> & groups) throw (ZeroDivisionException);
    static double getWCMultilocusFst(const PolymorphismMultiGContainer & pmgc, vector<unsigned int> locus_positions, const set<unsigned int> & groups) throw (Exception);
    static double getWCMultilocusFis(const PolymorphismMultiGContainer & pmgc, vector<unsigned int> locus_positions, const set<unsigned int> & groups) throw (Exception);
    //static PermResults getWCMultilocusFstAndPerm(const PolymorphismMultiGContainer & pmgc, vector<unsigned int> locus_positions,set<unsigned int> groups, int nb_perm) throw (Exception);
    //static PermResults getWCMultilocusFisAndPerm(const PolymorphismMultiGContainer & pmgc, vector<unsigned int> locus_positions,set<unsigned int> groups, int nb_perm) throw (Exception);
    static double getRHMultilocusFst(const PolymorphismMultiGContainer & pmgc, vector<unsigned int> locus_positions, const set<unsigned int> & groups) throw (Exception);
    static DistanceMatrix * getDistanceMatrix(const PolymorphismMultiGContainer & pmgc, vector<unsigned int> locus_positions, const set<unsigned int> & groups, string distance_methode) throw (Exception);
};
