/************************************************************************
 **
 ** file: biweight.c
 **
 ** Copyright (C) 2002-2007 Ben Bolstad
 ** 
 ** aim: implement the tukey biweight - one step method of summarizing a probeset 
 **
 ** created by: B. M. Bolstad   <bolstad@stat.berkeley.edu>
 ** created on: Jan 7, 2003 (But based on a file mas5.c created in Nov 2002)
 **
 ** last modified: Jan 7, 2003
 **
 ** License: GPL V2 or later (same as the rest of the Affy package)
 **
 ** General discussion
 **
 ** Implement Tukey Biweight Summarization method.
 **
 **
 ** Nov, 2002 - Initial versions
 ** Jan 2, 2003 - Clean up commenting, prepare for integration into AffyExtensions version 0.4
 ** Jan 7, 2003 - make the code a standalone file, data structure manipulation will be handled 
 **               elsewhere.
 ** Jul 23, 2003 - SE parameter added and implemented
 ** Oct 10, 2003 - added in PLM version
 ** Apr 5, 2004 - Change mallocs to Callocs
 ** May 19, 2007 - branch out of affyPLM into a new package preprocessCore, then restructure the code. Add doxygen style documentation
 ** Sep 16, 2007 - fix bug in tukeybiweight
 ** Sep 19, 2007 - add TukeyBiweight_noSE
 **
 ************************************************************************/

/*#include "threestep_common.h" */
#include "biweight.h"
#include "rma_common.h"
#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/******************************************************************************
 **
 ** double weight_bisquare(double x)
 **
 ** computes bisquare weights
 **
 ** double x - data
 **
 ** returns bisquare weight
 **
 *******************************************************************************/

static double weight_bisquare(double x){

  if (fabs(x) <= 1.0){
    return (1-x*x)*(1-x*x);
  } else {
    return 0;
  }
}

/****************************************************************************
 **
 ** double Tukey_Biweight(double *x, int length)
 **
 ** implements one step Tukey's Biweight as documented in the Affymetrix 
 ** Statistical Algorithms Description Document. 
 **
 ** double *x - vector of data
 ** int length - length of *x
 **
 ****************************************************************************/

double Tukey_Biweight(double *x, int length){
  
  double median;
  int i;
  double *buffer = (double *)Calloc(length,double);
  double c = 5.0;
  double epsilon = 0.0001;
  double S;
  double sum = 0.0;
  double sumw = 0.0;

  for (i=0; i < length; i++){
    buffer[i] = x[i];
  }

  qsort(buffer,length,sizeof(double),(int(*)(const void*, const void*))sort_double);

  if (length%2 == 0){
    median = (buffer[length/2 -1] + buffer[length/2])/2.0;
  } else {
    median = buffer[length/2];
  }
  /* printf("%f \n",median); */
  for (i=0; i < length; i++){
    buffer[i] = fabs(x[i] - median);
  }
  qsort(buffer,length,sizeof(double),(int(*)(const void*, const void*))sort_double);

  if (length%2 == 0){
    S = (buffer[length/2 -1] + buffer[length/2])/2.0;
  } else {
    S = buffer[length/2];
  }
  
  /*  printf("%f \n",S); */

  for (i=0; i < length; i++){
    buffer[i] = (x[i] - median)/(c*S + epsilon);
  }
  
  for (i =0; i < length; i++){
    sum+= weight_bisquare(buffer[i])*x[i];
    sumw += weight_bisquare(buffer[i]);
  }
  Free(buffer);
  return(sum/sumw);
}



/****************************************************************************
 **
 ** double Tukey_Biweight_SE(double *x, double BW, int length)
 **
 ** implements one step Tukey's Biweight SE as documented in the Affymetrix 
 ** Statistical Algorithms Description Document. 
 **
 ** double *x - vector of data
 ** int length - length of *x
 **
 ****************************************************************************/

static double Tukey_Biweight_SE(double *x,double BW, int length){
  
  double median;
  int i;
  double *buffer = (double *)Calloc(length,double);
  double c = 5.0;
  double epsilon = 0.0001;
  double S;
  double sum = 0.0;
  double sumw = 0.0;

  for (i=0; i < length; i++){
    buffer[i] = x[i];
  }

  qsort(buffer,length,sizeof(double),(int(*)(const void*, const void*))sort_double);

  if (length%2 == 0){
    median = (buffer[length/2 -1] + buffer[length/2])/2.0;
  } else {
    median = buffer[length/2];
  }
  /* printf("%f \n",median); */
  for (i=0; i < length; i++){
    buffer[i] = fabs(x[i] - median);
  }
  qsort(buffer,length,sizeof(double),(int(*)(const void*, const void*))sort_double);

  if (length%2 == 0){
    S = (buffer[length/2 -1] + buffer[length/2])/2.0;
  } else {
    S = buffer[length/2];
  }
  
  /*  printf("%f \n",S); */

  for (i=0; i < length; i++){
    buffer[i] = (x[i] - median)/(c*S + epsilon);
  }
  
  for (i =0; i < length; i++){
    sum+= weight_bisquare(buffer[i])*weight_bisquare(buffer[i])*(x[i]- BW)*(x[i] - BW);
    if (buffer[i] < 1.0){
      sumw += (1.0-buffer[i]*buffer[i])*(1.0 - 5.0*buffer[i]*buffer[i]);
    }
  }
  Free(buffer);
  return(sqrt(sum)/fabs(sumw));
}


void tukeybiweight(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;
  double *z = Calloc(rows,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < rows; i++){
      z[i] = log(data[j*rows + i])/log(2.0);  
    }
    results[j] = Tukey_Biweight(z,rows);
    resultsSE[j] = Tukey_Biweight_SE(z,results[j],rows);
  }
  Free(z);




}




void tukeybiweight_no_log(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;
  double *z = Calloc(rows,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < rows; i++){
      z[i] = data[j*rows + i];  
    }
    results[j] = Tukey_Biweight(z,rows);
    resultsSE[j] = Tukey_Biweight_SE(z,results[j],rows);
  }
  Free(z);




}














/**********************************************************************************
 **
 ** void tukeybiweight(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes)
 **
 ** aim: given a data matrix of probe intensities, and a list of rows in the matrix 
 **      corresponding to a single probeset, compute tukey biweight expression measure. 
 **      Note that data is a probes by chips matrix, apply tukeys biweight to columns
 **
 ** double *data - Probe intensity matrix
 ** int rows - number of rows in matrix *data (probes)
 ** int cols - number of cols in matrix *data (chips)
 ** int *cur_rows - indicies of rows corresponding to current probeset
 ** double *results - already allocated location to store expression measures (cols length)
 ** int nprobes - number of probes in current probeset.
 **
 ***********************************************************************************/ 

/*! \brief Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute  tukey biweight expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols
 *
 *  
 */

void TukeyBiweight(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){
  int i,j;
  double *z = Calloc(nprobes,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[i] = log(data[j*rows + cur_rows[i]])/log(2.0);  
    }
    results[j] = Tukey_Biweight(z,nprobes);
    resultsSE[j] = Tukey_Biweight_SE(z,results[j],nprobes);
  }
  Free(z);
}



void TukeyBiweight_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){
  int i,j;
  double *z = Calloc(nprobes,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[i] = log(data[j*rows + cur_rows[i]])/log(2.0);  
    }
    results[j] = Tukey_Biweight(z,nprobes);
  }
  Free(z);
}


void TukeyBiweight_no_log_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){
  int i,j;
  double *z = Calloc(nprobes,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[i] = data[j*rows + cur_rows[i]];  
    }
    results[j] = Tukey_Biweight(z,nprobes);
  }
  Free(z);
}

