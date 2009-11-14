/************************************************************************
 **
 ** avg.c
 **
 ** created by: B. M. Bolstad   <bmb@bmbolstad.com>
 ** created on: Sep 16, 2007  (but based on earlier work from Nov avg_log.c)
 **
 ** Copyright (C) 2007 Ben Bolstad
 **
 ** last modified: Sept 16, 2007
 **
 ** License: GPL V2 or later (same as the rest of the Affy package)
 **
 ** General discussion
 **
 ** Implement average summarization
 **
 ** History
 ** Sep 16, 2007 - Initial version
 **
 ** 
 **
 ************************************************************************/

#include "avg.h"

#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***************************************************************************
 **
 ** double AvgLog(double *x, int length)
 **
 ** double *x - a vector of PM intensities  (previously log2 transformed)
 ** int length - length of *x
 **
 ** take the average of log2 PM intensities.
 **
 ***************************************************************************/

static double Avg(double *x, int length){
  int i;
  double sum = 0.0;
  double mean = 0.0;

  for (i=0; i < length; i++){
    sum = sum + x[i];
  }
  
  mean = sum/(double)length;

  return (mean);    
}

/***************************************************************************
 **
 ** static double AvgLogSE(double *x, int length)
 **
 ** double *x - a vector of PM intensities (previously log2 transformed)
 ** double mean - the mean of x computed using AvgLog above
 ** int length - length of *x
 **
 ** compute the standard error of the average of log2 PM intensities.
 ** 
 **
 ***************************************************************************/

static double AvgSE(double *x, double mean, int length){
  int i;
  double sum = 0.0;

  for (i=0; i < length; i++){
    sum = sum + (x[i]- mean)*(x[i] - mean);
  }
  
  sum = sqrt(sum/(double)(length -1));
  sum = sum/sqrt((double)length);

  return (sum);    
}


void colaverage_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;

  for (j = 0; j < cols; j++){
    results[j] = Avg(&data[j*rows],rows);
    resultsSE[j] = AvgSE(&data[j*rows],results[j],rows);
  } 
}


/***************************************************************************
 ** 
 ** void average(double *data, int rows, int cols, double *results, double *resultsSE)
 **
 ** aim: given a data matrix of probe intensities, compute averages in column wise manner 
 **      
 **
 ** double *data - Probe intensity matrix
 ** int rows - number of rows in matrix *data (probes)
 ** int cols - number of cols in matrix *data (chips)
 ** int *cur_rows - indicies of rows corresponding to current probeset
 ** double *results - already allocated location to store expression measures (cols length)
 ** int nprobes - number of probes in current probeset.
 **
 ***************************************************************************/


void colaverage(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;
  double *z = Calloc(rows,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < rows; i++){
      z[i] = data[j*rows + i];  
    }
    results[j] = Avg(z,rows);
    resultsSE[j] = AvgSE(z,results[j],rows);
  } 
  Free(z);

}




/***************************************************************************
 **
 ** double Average(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes)
 **
 ** aim: given a data matrix of probe intensities, and a list of rows in the matrix 
 **      corresponding to a single probeset, compute average log2 expression measure. 
 **      Note that data is a probes by chips matrix.
 **
 ** double *data - Probe intensity matrix
 ** int rows - number of rows in matrix *data (probes)
 ** int cols - number of cols in matrix *data (chips)
 ** int *cur_rows - indicies of rows corresponding to current probeset
 ** double *results - already allocated location to store expression measures (cols length)
 ** int nprobes - number of probes in current probeset.
 **
 ***************************************************************************/

/*! \brief Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute average log2 expression measure. 
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

void ColAverage(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){
  int i,j;
  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = data[j*rows + cur_rows[i]];  
    }
  } 
  
  for (j=0; j < cols; j++){
    results[j] = Avg(&z[j*nprobes],nprobes);
    resultsSE[j] = AvgSE(&z[j*nprobes],results[j],nprobes);
  }

  Free(z);
}


/***************************************************************************
 **
 ** double AverageLog(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes)
 **
 ** aim: given a data matrix of probe intensities, and a list of rows in the matrix 
 **      corresponding to a single probeset, compute average log2 expression measure. 
 **      Note that data is a probes by chips matrix.
 **
 ** double *data - Probe intensity matrix
 ** int rows - number of rows in matrix *data (probes)
 ** int cols - number of cols in matrix *data (chips)
 ** int *cur_rows - indicies of rows corresponding to current probeset
 ** double *results - already allocated location to store expression measures (cols length)
 ** int nprobes - number of probes in current probeset.
 **
 ***************************************************************************/

/*! \brief Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute average log2 expression measure. 
 *      Note that data is a probes by chips matrix. 
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 *
 *  
 */

void ColAverage_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){
  int i,j;
  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = data[j*rows + cur_rows[i]];  
    }
  } 
  
  for (j=0; j < cols; j++){
    results[j] = Avg(&z[j*nprobes],nprobes);
  }
  Free(z);
}



