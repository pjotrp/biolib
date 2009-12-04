/* BioLib Affymetrix C example */

#include <stdio.h>
#include <stdlib.h>
#include <biolib_affyio.h>
#include <biolib_microarray.h>

int main(int argc, char * argv[])
{
   CELOBJECT *cel;
   char *fn;

   while(--argc) {
     fn = *++argv;   
     printf("Loading CEL file: %s\n", fn);
     cel = open_celfile(fn);
   }
   exit(EXIT_SUCCESS);
}

