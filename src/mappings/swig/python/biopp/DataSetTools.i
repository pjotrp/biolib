%module bpptest
%{
#include "DataSetTools.h"
using namespace bpp;
%}
//#include <set>
using namespace std;
%include "TextTools.i"
%include "Exceptions.i"
%include "OrderedSequenceContainer.i"
%include "DataSet.i"
%include "PolymorphismSequenceContainer.i"

%ignore DataSetTools::DataSetTools;
%ignore DataSetTools::~DataSetTools;

class DataSetTools
{
  public:
    static DataSet * buildDataSet(const OrderedSequenceContainer & osc) throw (Exception);
    static DataSet * buildDataSet(const PolymorphismSequenceContainer & psc) throw (Exception);
};
