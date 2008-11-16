/* BioLib Affymetrix C example */

#include <biolib_affyio.h>
#include <biolib_microarray.h>

int main()
{
   CELOBJECT *cel;
   cel = open_celfile("/tmp/test_binary.cel.gz");
   // cel = open_celfile("test46.CEL.gz.stub");
}

