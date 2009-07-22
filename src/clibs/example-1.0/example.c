#include <stdlib.h>
#include <time.h>
#include <biolib_example.h>

/* Basic example for SWIG mappings to Python, Ruby, Perl, R etc.*/

// ==== Standard parameter passing for SWIG

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

/* Test returning an array of floats -- notice the memory leak */
float *list(int size) 
{
  float *p = malloc(size*8);
	int i;
	for (i=0; i<size-1; i++)
	{
    p[i] = (float)i;
	}
}

// ==== Advanced parameter passing for SWIG

/* Passing in a double ** value (pointer of pointers to double), often
 * used to pass in a matrix. Here we pass matrix in, from the high-level
 * language, as an array of values. The matrix is modified.
 */

void matrix_as_array_change(int cols, int rows, double **matrix_as_array)
{
  int i, j;
  double **matrix = matrix_as_array;
  for (i=0; i<rows; i++)
    for (j=0; j<cols; j++)
      matrix[i][j] = i*rows+j;
}

/* Here we transform an array of doubles and give it as a 
 * parameter return value (result). This needs a SWIG typemap
 * as SWIG defaults to having result a double by reference,
 * rather than an array.
 */

void array_transform_to_result(int num, double *data, double *result)
{
  int i;
  for (i=0; i<num; i++)
    result[i] = data[i]+1.0;
}

/* 
 * Transform an input array (version one using build-in sizes)
 */

void array_transform_to_result1(int num, double *data1, double *result)
{
  int i;
  for (i=0; i<num; i++)
    result[i] = data1[i]+1.5;
}

/* 
 * Transform an input array (version two using an argsize dimension)
 */

void array_transform_to_result2(int num, double *data2, double *result)
{
  int i;
  for (i=0; i<num; i++)
    result[i] = data2[i]+2.0;
}


/* 
 * Transform an input array (version three using an argsize dimension 
 * for the result only)
 */

void array_transform_to_result3(int num, double *data, double *result)
{
  int i;
  for (i=0; i<num; i++)
    result[i] = data[i]+2.5;
}

/*
 * Fake scanone_mr
 */

void scanone_mr(int n_ind, int n_pos, int n_gen, int **Geno,
                double **Addcov, int n_addcov, double **Intcov,
                int n_intcov, double *pheno, double *weights,
                double *result)
{
  int i,j;
  printf("\nEntering scanone_mr!");
  for (i=0; i<n_ind; i++)
    for (j=0; j<n_pos; j++)
      printf("%d,",Geno[j][i]);
  for (i=0; i<n_pos; i++)
    result[i] = (double)i;
  printf(" result1<%f>\n",result[1]);
  result[0] = Geno[2][1]; // marker3, ind1 = 6
}

