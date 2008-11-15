/************************************************************************
 **
 ** file: medianpolish.c
 **
 ** Copyright (C) 2002-2007 Ben Bolstad
 **
 ** created by: B. M. Bolstad   <bmb@bmbolstad.com>
 ** created on: Jan 7, 2003 (but based on code dating back as far as June 2002)
 **
 ** last modified: Jan 7, 2003
 **
 ** License: GPL V2 or later (same as the rest of the Affy package)
 **
 ** Median polish summary measure (used in the RMA expression measure)
 ** and just general medianpolish model fitting
 **
 **
 ** History
 **
 ** Jan 7, 2003 - Initial version to fit into the three-step framework.
 ** Jan 13, 2003 - move median() into threestep_common.c
 ** Feb 24, 2003 - make maxiter get used.
 ** Jul 23, 2003 - add ability to accept SE parameter
 ** Sept 13, 2003 - introduced medianpolishPLM which returns 
 **                 most of what is required by the fitting
 **                 algorithm
 ** Oct 05, 2003 - added in summary_param
 ** Apr 5, 2004 - change malloc/free to Calloc/Free
 ** Nov 13, 2006 - make median calls to median_nocopy
 ** May 19, 2007 - branch out of affyPLM into a new package preprocessCore, then restructure the code. Add doxygen style documentation
 ** May 24, 2007 - break median polish functionality down into even smaller component parts.
 **
 ************************************************************************/


#include "medianpolish.h"
#include "rma_common.h"

#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*******************************************************************************
 **
 ** double sum_abs(double *z, int rows, int cols)
 **
 ** double *z - matrix of doubles
 ** int rows - dimension of matrix
 ** int cols - dimension of matrix
 **
 ** returns the sum of the absolute values of elements of the matrix *z
 **
 ******************************************************************************/

static double sum_abs(double *z, int rows, int cols){
 
  int i, j;
  double sum = 0.0;

  for (i=0; i < rows; i++)
    for (j=0; j < cols; j++)
      sum+=fabs(z[j*rows+i]);

  return sum;
}

/********************************************************************************
 **
 ** void get_row_median(double *z, double *rdelta, int rows, int cols)
 **
 ** double *z - matrix of dimension  rows*cols
 ** double *rdelta - on output will contain row medians (vector of length rows)
 ** int rows, cols - dimesion of matrix
 **
 ** get the row medians of a matrix 
 **
 ********************************************************************************/

static void get_row_median(double *z, double *rdelta, int rows, int cols){
  int i,j;
  double *buffer = (double *)Calloc(cols,double);

  for (i = 0; i < rows; i++){ 
    for (j = 0; j < cols; j++){
      buffer[j] = z[j*rows + i];
    }
    rdelta[i] = median_nocopy(buffer,cols);
  }
  
  Free(buffer);
}

/********************************************************************************
 **
 ** void get_col_median(double *z, double *cdelta, int rows, int cols)
 **
 ** double *z - matrix of dimension  rows*cols
 ** double *cdelta - on output will contain col medians (vector of length cols)
 ** int rows, cols - dimesion of matrix
 **
 ** get the col medians of a matrix 
 **
 ********************************************************************************/

static void get_col_median(double *z, double *cdelta, int rows, int cols){
  
  int i, j;
  
  double *buffer = (double *)Calloc(rows,double);
  for (j = 0; j < cols; j++){
    for (i = 0; i < rows; i++){  
      buffer[i] = z[j*rows + i];
    }
    cdelta[j] = median_nocopy(buffer,rows);
  }
  
  Free(buffer);

}

/***********************************************************************************
 **
 ** void subtract_by_row(double *z, double *rdelta, int rows, int cols)
 ** 
 ** double *z - matrix of dimension rows by cols
 ** double *rdelta - vector of length rows
 ** int rows, cols dimensions of matrix
 **
 ** subtract the elements of *rdelta off each row of *z
 **
 ***********************************************************************************/

static void subtract_by_row(double *z, double *rdelta, int rows, int cols){
  
  int i,j;

  for (i = 0; i < rows; i++){
    for (j = 0; j < cols; j++){
      z[j*rows +i]-= rdelta[i];
    }
  }
}


/***********************************************************************************
 **
 ** void subtract_by_col(double *z, double *cdelta, int rows, int cols)
 ** 
 ** double *z - matrix of dimension rows by cols
 ** double *cdelta - vector of length rows
 ** int rows, cols dimensions of matrix
 **
 ** subtract the elements of *cdelta off each col of *z
 **
 ***********************************************************************************/

static void subtract_by_col(double *z, double *cdelta, int rows, int cols){
  
  int i,j;
  for (j = 0; j < cols; j++){
    for (i = 0; i < rows; i++){
      z[j*rows +i]-= cdelta[j];
    }
  }

}

/***********************************************************************************
 **
 ** void rmod(double *r, double *rdelta, int rows)
 ** 
 ** double *r - vector of length rows
 ** double *rdelta - vector of length rows
 ** int rows, cols dimensions of matrix
 **
 ** add elementwise *rdelta to *r
 **
 ***********************************************************************************/


static void rmod(double *r, double *rdelta, int rows){
  int i;

  for (i = 0; i < rows; i++){
    r[i]= r[i] + rdelta[i];
  }
}

/***********************************************************************************
 **
 ** void cmod(double *c, double *cdelta, int cols)
 ** 
 ** double *c - vector of length rows
 ** double *cdelta - vector of length rows
 ** int cols length of vector
 **
 ** add elementwise *cdelta to *c
 **
 ***********************************************************************************/

static void cmod(double *c, double *cdelta, int cols){
  int j;

  for (j = 0; j < cols; j++){
    c[j]= c[j] + cdelta[j];
  }
}


void median_polish_fit_no_copy(double *data, int rows, int cols, double *r, double *c, double *t){
 

  int i,j,iter;
  int maxiter = 10;
  double eps=0.01;
  double oldsum = 0.0,newsum = 0.0;
  double delta;
  double *rdelta = Calloc(rows,double);
  double *cdelta = Calloc(cols,double);

  double *z = data; /* This is just to keep consistent with other code here. No actual copying of the data is done here */

  *t = 0.0;

  for (iter = 1; iter <= maxiter; iter++){
    get_row_median(z,rdelta,rows,cols);
    subtract_by_row(z,rdelta,rows,cols);
    rmod(r,rdelta,rows);
    delta = median(c,cols);
    for (j = 0; j < cols; j++){
      c[j] = c[j] - delta;
    }
    *t = *t + delta;
    get_col_median(z,cdelta,rows,cols);
    subtract_by_col(z,cdelta,rows,cols);
    cmod(c,cdelta,cols);
    delta = median(r,rows);
    for (i =0; i < rows; i ++){
      r[i] = r[i] - delta;
    }
    *t = *t+delta;
    newsum = sum_abs(z,rows,cols);
    if (newsum == 0.0 || fabs(1.0 - oldsum/newsum) < eps)
      break;
    oldsum = newsum;
  }
  
  Free(rdelta);
  Free(cdelta);

}




void median_polish_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){

  int j;
  
  double *r = Calloc(rows,double);
  double *c = Calloc(cols,double);
  double t;

  double *z = data;  /* This is just to keep consistent with other code here. No actual copying of the data is done here */
  
  median_polish_fit_no_copy(z, rows, cols, r, c, &t);
  
  for (j=0; j < cols; j++){
    results[j] =  t + c[j]; 
    resultsSE[j] = R_NaReal;
  }
  
  Free(r);
  Free(c);
}


void median_polish_log2_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){

  
  int i, j;

  for (j = 0; j < cols; j++){
    for (i =0; i < rows; i++){
      data[j*rows + i] = log(data[j*rows + i])/log(2.0);  
    }
  } 

  median_polish_no_copy(data,rows,cols,results,resultsSE);

}


void median_polish_log2(double *data, int rows, int cols, double *results, double *resultsSE, double *residuals){
  int i, j;

  for (j = 0; j < cols; j++){
    for (i =0; i < rows; i++){
      residuals[j*rows + i] = log(data[j*rows + i])/log(2.0);  
    }
  } 
  median_polish_no_copy(residuals,rows,cols,results,resultsSE);

}


void median_polish(double *data, int rows, int cols, double *results, double *resultsSE, double *residuals){

  int i, j;

  for (j = 0; j < cols; j++){
    for (i =0; i < rows; i++){
      residuals[j*rows + i] = data[j*rows + i];  
    }
  } 
  median_polish_no_copy(residuals,rows,cols,results,resultsSE);
}





/*************************************************************************************
 **
 ** void MedianPolish(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes)
 **
 ** double *data - a data matrix of dimension rows by cols (the entire PM matrix)
 ** int rows, cols - rows and columns dimensions of matrix
 ** int cur_rows - vector of length nprobes containg row indicies of *data matrix which apply for a 
 **                particular probeset
 ** double *results - a vector of length cols already allocated. on output contains expression values
 ** int nprobes - number of probes in current probeset.
 **
 ** a function to do median polish expression summary.
 **
 *************************************************************************************/

/*! \brief Compute medianpolish  
 *
 *
 *      Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute median polish expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols. Note that this is just NA values
 *
 *  
 */

void MedianPolish(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){

  int i,j;

  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = log(data[j*rows + cur_rows[i]])/log(2.0);  
    }
  } 
  

  median_polish_no_copy(z,nprobes,cols,results,resultsSE);
  
  Free(z);

}



void MedianPolish_no_log(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){

  int i,j;

  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = data[j*rows + cur_rows[i]];  
    }
  } 
  

  median_polish_no_copy(z,nprobes,cols,results,resultsSE);
  
  Free(z);

}


