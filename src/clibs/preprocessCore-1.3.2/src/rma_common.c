/***********************************************************************
 **
 ** file: rma_common.c
 ** 
 ** aim: a location for commonly used utility functions
 **
 **
 ** written by: B. M. Bolstad <bolstad@stat.berkeley.edu>
 **
 ** created: Oct 16, 2002
 ** last modified: Oct 16, 2002
 **
 ** history:
 ** Oct 16, 2002 - a place to put common utility code, created to help
 **                the R package build.
 ** Jan 2, 2003 - Clean up code comments
 ** Nov 13, 2006 - moved median function into this file from rma2.c
 **
 ***********************************************************************/

#include "rma_common.h"
#include <stdlib.h>
#include <string.h>

#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

/**********************************************************
 **
 ** int sort_double(const void *a1,const void *a2)
 ** 
 ** a comparison function used when sorting doubles.
 **
 **********************************************************/

int sort_double(const double *a1,const double *a2){
  if (*a1 < *a2)
    return (-1);
  if (*a1 > *a2)
    return (1);
  return 0;
}



/**************************************************************************
 **
 ** double median(double *x, int length)
 **
 ** double *x - vector
 ** int length - length of *x
 **
 ** returns the median of *x
 **
 *************************************************************************/

double  median(double *x, int length){
  /*  int i; */
  int half;
  double med;
  double *buffer = Calloc(length,double);
  
  memcpy(buffer,x,length*sizeof(double));

  half = (length + 1)/2;
  /*  
      qsort(buffer,length,sizeof(double), (int(*)(const void*, const void*))sort_double);  
      
      if (length % 2 == 1){
      med = buffer[half - 1];
      } else {
      med = (buffer[half] + buffer[half-1])/2.0;
      }
  */

  rPsort(buffer, length, half-1);
  med = buffer[half-1];
  if (length % 2 == 0){
    rPsort(buffer, length, half);
    med = (med + buffer[half])/2.0;
  }
  
  Free(buffer);
  return med;
}


/**************************************************************************
 **
 ** double median_nocopy(double *x, int length)
 **
 ** double *x - vector
 ** int length - length of *x
 **
 ** returns the median of *x. note x is not order preserved when this function
 ** is called.
 **
 *************************************************************************/

double  median_nocopy(double *x, int length){
  /* int i; */
  int half;
  double med;
  double *buffer = x;  //Calloc(length,double);
  
  half = (length + 1)/2;
  /*  
      qsort(buffer,length,sizeof(double), (int(*)(const void*, const void*))sort_double);  
      
      if (length % 2 == 1){
      med = buffer[half - 1];
      } else {
      med = (buffer[half] + buffer[half-1])/2.0;
      }
  */

  rPsort(buffer, length, half-1);
  med = buffer[half-1];
  if (length % 2 == 0){
    rPsort(buffer, length, half);
    med = (med + buffer[half])/2.0;
  }
  
 
  return med;
}
