/************************************************************************
 **
 ** median_logPM.c
 **
 ** created by: B. M. Bolstad   <bmb@bmbolstad.com>
 ** created on: Feb 6, 2003  (but based on earlier work from Nov 2002)
 **
 ** Copyright (C) 2003-2007   Ben Bolstad
 **
 ** last modified: Feb 6, 2003
 **
 ** License: GPL V2 or later (same as the rest of the Affy package)
 **
 ** General discussion
 **
 ** Implement median log2 pm summarization.
 **
 ** Feb 6, 2003 - Initial version of this summarization method
 ** Feb 24, 2003 - Remove unused variable in i from MedianLog
 ** Jul 23, 2003 - add SE parameter (but not yet implemented)
 ** Oct 10, 2003 - added PLM version
 ** Sept 9, 2007 - branch out of affyPLM into a new package preprocessCore
 **
 ************************************************************************/

#include "rma_common.h"
#include "median_log.h"

#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/***************************************************************************
 **
 ** double MedianLog(double *x, int length)
 **
 ** double *x - a vector of PM intensities 
 ** int length - length of *x
 **
 ** take the log2 of the median of PM intensities.
 **
 ***************************************************************************/

static double median_log(double *x, int length){

  double med = 0.0;
  
  med = median_nocopy(x,length);
 
  return (med);    
}

/***************************************************************************
 **
 ** double MedianLogPM(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes)
 **
 ** aim: given a data matrix of probe intensities, and a list of rows in the matrix 
 **      corresponding to a single probeset, compute log2 Median expression measure. 
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

void MedianLog(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){
  int i,j;
  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = log(data[j*rows + cur_rows[i]])/log(2.0);  
    }
  } 
  
  for (j=0; j < cols; j++){
    results[j] = median_log(&z[j*nprobes],nprobes); 
    resultsSE[j] = R_NaReal;
  }
  Free(z);
}



/***************************************************************************
 **
 ** double MedianLogPM_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes)
 **
 ** aim: given a data matrix of probe intensities, and a list of rows in the matrix 
 **      corresponding to a single probeset, compute log2 Median expression measure. 
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

void MedianLog_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){
  int i,j;
  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = log(data[j*rows + cur_rows[i]])/log(2.0);  
    }
  } 
  
  for (j=0; j < cols; j++){
    results[j] = median_log(&z[j*nprobes],nprobes);

  }
  Free(z);
}



void medianlog(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;
  double *buffer = Calloc(rows, double);
  
  for (j=0; j < cols; j++){
    for (i = 0; i < rows; i++){
      buffer[i] = log2(data[j*rows + i]);
    }
    results[j] = median_log(buffer,rows); 
    resultsSE[j] = R_NaReal;
  }

  Free(buffer);
}




void medianlog_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;
    
  for (j=0; j < cols; j++){
    for (i = 0; i < rows; i++){
      data[j*rows + i]= log2(data[j*rows + i]);
    }
    results[j] = median_log(&data[j*rows],rows); 
    resultsSE[j] = R_NaReal;
  }

}
