/************************************************************************
 **
 ** log_median.c (was previously medianPM.c)
 **
 ** Copyright (C) 2002-2003 Ben Bolstad
 **
 ** created by: B. M. Bolstad   <bolstad@stat.berkeley.edu>
 ** created on: Feb 6, 2003  (but based on earlier work from Nov 2002)
 **
 ** last modified: Feb 6, 2003
 **
 ** License: GPL V2 or later (same as the rest of the Affy package)
 **
 ** General discussion
 **
 ** Implement log2 median pm summarization.
 **
 ** Feb 6, 2003 - Initial version of this summarization method
 ** Feb 24, 2003 - remove unused int i from LogMedian()
 ** Jul 23, 2003 - add a parameter for storing SE (not yet implemented)
 ** Oct 10, 2003 - PLM version of threestep
 ** Sep 10, 2007 - move functionality out of affyPLM (and into preprocessCore)
 ** Sep 19, 2007 - add LogMedian_noSE
 **
 ************************************************************************/


#include "log_median.h"
#include "rma_common.h"

#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/***************************************************************************
 **
 ** double LogMedian(double *x, int length)
 **
 ** double *x - a vector of PM intensities 
 ** int length - length of *x
 **
 ** take the log2 of the median of PM intensities.
 **
 ***************************************************************************/

static double log_median(double *x, int length){

  double med = 0.0;
  
  med = median(x,length);
  med = log(med)/log(2.0);

  return (med);    
}

/***************************************************************************
 **
 ** double LogMedianPM(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes)
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

void LogMedian(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){
  int i,j;
  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = data[j*rows + cur_rows[i]];  
    }
  } 
  
  for (j=0; j < cols; j++){
    results[j] = log_median(&z[j*nprobes],nprobes);
    resultsSE[j] = R_NaReal;
  }
  Free(z);
}



void LogMedian_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){
  int i,j;
  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = data[j*rows + cur_rows[i]];  
    }
  } 
  
  for (j=0; j < cols; j++){
    results[j] = log_median(&z[j*nprobes],nprobes);
  }
  Free(z);
}







void logmedian(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;
  double *buffer = Calloc(rows, double);
  
  for (j=0; j < cols; j++){
    for (i = 0; i < rows; i++){
      buffer[i] = data[j*rows + i];
    }
    results[j] = log_median(buffer,rows); 
    resultsSE[j] = R_NaReal;
  }

  Free(buffer);

}


void logmedian_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;
  
  for (j=0; j < cols; j++){
    results[j] = log_median(&data[j*rows],rows); 
    resultsSE[j] = R_NaReal;
  }

  //  Free(buffer);

}
