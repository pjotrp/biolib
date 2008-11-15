/******************************************************************************
 **
 ** file: rma_background4.c
 **
 ** Copyright (C) 2002 - 2008 B. M. Bolstad
 ** 
 ** Written by: B. M. Bolstad  <bmb@bmbolstad.com>
 ** Implementation dates: 2002-2008
 **
 ** Background: this file is named rma_background4.c reflecting its history
 ** but named distinctly, since it's history is somewhat muddled, and it no longer
 ** provides the full functionality of earlier versions. Instead it stabilizes 
 ** on the most recent implementations. 
 **
 ** A brief history:
 ** rma_background.c was originally in AffyExtensions and had a method that used both PM and MM
 ** probes. It used the R function density() to compute the density estimator
 ** Eventually this morphed into rma_background2.c which was in the affy package. It added an additonal
 ** background implementation which used PM probes only. This became the default implementation and it used
 ** the R density() function. 
 ** Later rma_background3.c was created for RMAExpress. It did not use the R density() function. Instead, it
 ** used code from weightedkerneldensity.c
 ** This file (rma_background4.c) aims to implement the standard RMA background correction method
 ** using code from weightedkerneldensity.c (ie removing the dependence on R density() function)
 **
 ** History
 ** Mar 15, 2008 - Initial version of rma_background4.c
 ** Mar 16, 2008 - 
 ** Jun 4, 2008 - fix bug with R interface, was not correctly returning value when copy ==TRUE
 **
 **
 *****************************************************************************/


#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>
#include <math.h>
#include <stdlib.h> 
#include <R_ext/Applic.h>


#include "weightedkerneldensity.h"
#include "rma_background4.h"

#ifdef USE_PTHREADS
#include <pthread.h>
#define THREADS_ENV_VAR "R_THREADS"
pthread_mutex_t mutex_R;
struct loop_data{
  double *data;
  int rows;
  int cols;
  int start_col;
  int end_col;
};
#endif


/***********************************************************
 **
 ** double find_max(double *x, int length)
 **
 ** this function returns the max of x
 **
 ************************************************************/

static double find_max(double *x,int length){
  int i;
  double max;

  max = x[0];
  for (i=1; i < length; i++){
    if (x[i] > max){
      max = x[i];
    }
  }
  
  return max;
}


/**************************************************************************************
 **
 ** double max_density(double *z,int rows,int cols,int column)
 **
 ** double *z - matrix of dimension rows*cols
 ** int cols - matrix dimension
 ** int rows - matrix dimension
 ** int column - column of interest
 **
 *************************************************************************************/

static double max_density(double *z,int rows,int cols,int column){

  int i;

  double *x;
  double *dens_x;
  double *dens_y;
  double max_y,max_x;
   
  int npts = 16384;

  dens_x = Calloc(npts,double);
  dens_y = Calloc(npts,double);


  //  KernelDensity(double *x, int *nxxx, double *weights, double *output, double *xords, int *nout)
    
  x = Calloc(rows,double);

  for (i=0; i< rows; i++){
    x[i] = z[column*rows +i];
  }
  
  
  KernelDensity_lowmem(x,&rows,dens_y,dens_x,&npts);

  max_y = find_max(dens_y,16384);
   
  i = 0;
  do {
    if (dens_y[i] == max_y)
      break;
    i++;
 
  } while(1);
   
  max_x = dens_x[i];

  Free(dens_x);
  Free(dens_y);
  Free(x);

  return max_x;
 
}

/***************************************************************
 **
 ** double get_sd(double *MM, double MMmax, int rows, int cols, int column)
 ** 
 ** double *PM - pm matrix
 ** double PMmax - value of mode of PMs for column
 ** int rows,cols - dimensions of matrix
 ** int column - column (chip) of interest
 **
 ** estimate the sigma parameter given vector MM value of maximum of density
 ** of MM, dimensions of MM matrix and column of interest
 **
 **
 ***************************************************************/

static double get_sd(double *PM, double PMmax, int rows, int cols, int column){
  double sigma;
  double tmpsum = 0.0;
  int numtop=0;
  int i;

  for (i=0; i < rows; i++){
    if (PM[column*rows + i] < PMmax){
      tmpsum = tmpsum + (PM[column*rows + i] - PMmax)*(PM[column*rows + i] - PMmax);
      numtop++;
    }
  }
  sigma = sqrt(tmpsum/(numtop -1))*sqrt(2.0)/0.85;
  return sigma;
}


/***************************************************************
 **
 ** double  get_alpha(double *PM,double PMmax, int rows,int cols,int column)
 **
 ** estimate the alpha parameter given vector PM value of maximum of density
 ** of PM, dimensions of MM matrix and column of interest using method proposed
 ** in affy2
 **
 **
 ***************************************************************/

static double get_alpha(double *PM, double PMmax, int length){
  double alpha;
  
  int i;

  for (i=0; i < length; i++){
    PM[i] = PM[i] - PMmax;
  }

  alpha = max_density(PM,length, 1,0);

  alpha = 1.0/alpha;
  return alpha ;  
}



/********************************************************************************
 **
 ** void rma_bg_parameters(double *PM,double *MM, double *param, int rows, int cols, int column,SEXP fn,SEXP rho)
 **
 ** estimate the parameters for the background, they will be returned in *param
 ** param[0] is alpha, param[1] is mu, param[2] is sigma.
 **
 ** parameter estimates are same as those given by affy in bg.correct.rma (Version 1.1 release of affy)
 **
 *******************************************************************************/


void rma_bg_parameters(double *PM,double *param, int rows, int cols, int column){
  int i = 0;
  double PMmax;

  double sd,alpha;
  int n_less=0,n_more=0;
  double *tmp_less = (double *)Calloc(rows,double);
  double *tmp_more = (double *)Calloc(rows,double);
  
  
  PMmax = max_density(PM,rows, cols, column);
  
  for (i=0; i < rows; i++){
    if (PM[column*rows +i] < PMmax){
      tmp_less[n_less] = PM[column*rows +i];
      n_less++;
    }

  }  

  PMmax = max_density(tmp_less,n_less,1,0);
  sd = get_sd(PM,PMmax,rows,cols,column)*0.85; 

  for (i=0; i < rows; i++){
    if (PM[column*rows +i] > PMmax) {
      tmp_more[n_more] = PM[column*rows +i];
      n_more++;
    }
  }

  /* the 0.85 is to fix up constant in above */
  alpha = get_alpha(tmp_more,PMmax,n_more);

  param[0] = alpha;
  param[1] = PMmax;
  param[2] = sd;


  Free(tmp_less);
  Free(tmp_more);
}




/**********************************************************************************
 **
 ** double Phi(double x)
 **
 ** Compute the standard normal distribution function
 **
 *********************************************************************************/

static double Phi(double x){
   return pnorm5(x,0.0,1.0,1,0);
}

/***********************************************************************************
 **
 ** double phi(double x)
 **
 ** compute the standard normal density.
 **
 **
 **********************************************************************************/

static double phi(double x){
  return dnorm4(x,0.0,1.0,0);
}

/************************************************************************************
 **
 ** void bg_adjust(double *PM,double *MM, double *param, int rows, int cols, int column)
 **
 ** double *PM - PM matrix of dimension rows by cols
 ** double *param - background model parameters
 ** int rows, cols - dimension of matrix
 ** int column - which column to adjust
 **
 ** note we will assume that param[0] is alpha, param[1] is mu, param[2] is sigma
 **
 ***********************************************************************************/

void rma_bg_adjust(double *PM, double *param, int rows, int cols, int column){
  int i;
  double a;
    
  for (i=0; i < rows; i++){
    a = PM[column*rows + i] - param[1] - param[0]*param[2]*param[2]; 
    PM[column*rows + i] = a + param[2] * phi(a/param[2])/Phi(a/param[2]);
  } 
  
}


#ifdef USE_PTHREADS
void *rma_bg_correct_group(void *data){

  int j;
  double param[3];
  struct loop_data *args = (struct loop_data *) data;
  
  for (j=args->start_col; j <= args->end_col; j++){
    rma_bg_parameters(args->data, param, args->rows, args->cols, j);
    rma_bg_adjust(args->data, param, args->rows, args->cols, j);
  }
}
#endif

/************************************************************************************
 **
 ** void rma_bg_correct(double *PM,double *MM, double *param, int rows, int cols, int column)
 **
 ** double *PM - PM matrix of dimension rows by cols
 ** int rows - dimensions of the matrix
 ** int cols -  dimensions of the matrix
 **
 ** rma background correct the columns of a supplied matrix
 **
 **
 ************************************************************************************/

void rma_bg_correct(double *PM, int rows, int cols){

  int j;
  double param[3];
#ifdef USE_PTHREADS
  int i;
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif



#ifdef USE_PTHREADS
  nthreads = getenv(THREADS_ENV_VAR);
  if(nthreads != NULL){
    num_threads = atoi(nthreads);
    if(num_threads <= 0){
      error("The number of threads (enviroment variable %s) must be a positive integer, but the specified value was %s", THREADS_ENV_VAR, nthreads);
    }
  }
  threads = (pthread_t *) Calloc(num_threads, pthread_t);

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /* this code works out how many threads to use and allocates ranges of columns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
    1) Number of columns is less than the number of threads
  */
  
  if (num_threads < cols){
    chunk_size = cols/num_threads;
    chunk_size_d = ((double) cols)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((cols < num_threads ? cols : num_threads), struct loop_data);

  args[0].data = PM;
  args[0].rows = rows;  
  args[0].cols = cols;
  

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < cols; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_col = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_col = i+chunk_size;
       i++;
     }
     else{
       args[t].end_col = i+chunk_size-1;
     }
     t++;
  }

  /* Determining the quantile normalization target distribution */
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, rma_bg_correct_group, (void *) &(args[i]));
     if (returnCode){
         error("ERROR; return code from pthread_create() is %d\n", returnCode);
     }
  }
  /* Wait for the other threads */
  for(i = 0; i < t; i++){
      returnCode = pthread_join(threads[i], &status);
      if (returnCode){
         error("ERROR; return code from pthread_join(thread #%d) is %d, exit status for thread was %d\n", 
               i, returnCode, *((int *) status));
      }
  }

  pthread_attr_destroy(&attr);  
  pthread_mutex_destroy(&mutex_R);
  Free(threads);
  Free(args);  
#else
  for (j=0; j < cols; j++){
    rma_bg_parameters(PM, param,rows,cols,j);
    rma_bg_adjust(PM,param,rows,cols,j);
  }
#endif
}

/************************************************************************************
 **
 ** SEXP R_rma_bg_correct(SEXP PMmat, SEXP MMmat, SEXP densfunc, SEXP rho)
 ** 
 ** given R matricies PMmat and MMmat background correct the columns of PMmat
 **
 ** SEXP PMmat - matrix of PM's
 **
 ** this function can be dangerous since it changes PM values on the input matrix (ie it makes no copies)
 **
 ***********************************************************************************/

SEXP R_rma_bg_correct(SEXP PMmat,SEXP copy){
  
  SEXP dim1,PMcopy;
  int j;
  int rows;
  int cols;
  double *PM;

  PROTECT(dim1 = getAttrib(PMmat,R_DimSymbol));

  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];

  if (asInteger(copy)){
    PROTECT(PMcopy = allocMatrix(REALSXP,rows,cols));
    copyMatrix(PMcopy,PMmat,0);
    PM = NUMERIC_POINTER(AS_NUMERIC(PMcopy));
  } else {
    PM = NUMERIC_POINTER(AS_NUMERIC(PMmat));
  }
  
  rma_bg_correct(PM, rows, cols);
  
  if (asInteger(copy)){
    UNPROTECT(2);
  } else {
    UNPROTECT(1);
  }
  if (asInteger(copy)){
    return PMcopy;
  } else {
    return PMmat;
  }
}


