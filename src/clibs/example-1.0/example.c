#include <stdlib.h>
#include <time.h>
#include <biolib_example.h>

/* Basic example for SWIG mappings to Python, Ruby, Perl, R etc.*/

int fact(int n) {
 if (n == 0)
   return 1;
 return (n * fact(n-1));
}

int my_mod(int x, int y) {
    return (x%y);
}
	
char *get_time()
{
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}

/* Test returning an array of floats */
float *list(int size) 
{
  float *p = malloc(size*8);
	int i;
	for (i=0; i<size-1; i++)
	{
    p[i] = (float)i;
	}
}
