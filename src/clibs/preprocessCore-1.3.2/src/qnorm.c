/**********************************************************
 **
 ** file: qnorm.c
 **
 ** aim: A c implementation of the quantile normalization method 
 **
 ** Copyright (C) 2002-2008    Ben Bolstad
 **
 ** written by: B. M. Bolstad  <bmb@bmbolstad.com>
 **
 ** written: Feb 2, 2002
 ** last modified: Jun 4, 2006
 ** 
 ** This c code implements the quantile normalization method
 ** for normalizing high density oligonucleotide data as discussed
 ** in
 **
 ** Bolstad, B. M., Irizarry R. A., Astrand, M, and Speed, T. P. (2003)(2003) 
 ** A Comparison of Normalization Methods for High 
 ** Density Oligonucleotide Array Data Based on Bias and Variance.
 ** Bioinformatics 19,2,pp 185-193
 **
 ** History
 ** Feb 2, 2002 - Intial c code version from original R code
 ** Apr 19, 2002 - Update to deal more correctly with ties (equal rank)
 ** Jan 2, 2003 - Documentation/Commenting updates reformating
 ** Feb 17, 2003 - add in a free(datvec) to qnorm(). clean up freeing of dimat
 ** Feb 25, 2003 - try to reduce or eliminate compiler warnings (with gcc -Wall)
 ** Feb 28, 2003 - update reference to normalization paper in comments
 ** Mar 25, 2003 - ability to use median, rather than mean in so called "robust" method
 ** Aug 23, 2003 - add ability to do normalization on log scale in "robust" method.
 **                also have added .Call() interface c functions which may be called
 **                now from R as alterative to traditonal means.
 **                Fixed a bug where use_median was not being dereferenced in "robust method"
 ** Oct 7, 2003 - fix a bug with length is qnorm_robust
 ** Mar 6, 2004 - change malloc/free pairs to Calloc/Free
 ** Mar 3, 2005 - port across the low memory quantile normalization from RMAExpress (and make it the new qnorm_c (previous version made qnorm_c_old)
 ** Mar 12, 2006 - make some internal functions static
 ** Mar 13, 2006 - re-working of the "robust" quantile normalizer. The old function is
 **                still here with a _old added to the name. Also now
 **                have a .Call() interface for the robust method
 ** Apr 27-28, 2006 - Add C level functionality for determining which outliers
 **                to exclude for the "robust" quantile normalizer.
 ** Jun 2, 2006  - Add a quantile normalization function that accepts a target
 **                distribution. Improve/add a few comments
 ** Jun 4, 2006 - Add a .Call interface for target based quantile normalization.
 **               Add a function for determing target distribution.
 ** Jun 5, 2006 - Re-organize code blocks
 **               Add normalization within blocks functions
 ** Jun 9, 2006 - change nearbyint to floor(x +0.5) (to fix problems on Sparc Solaris builds)
 ** Aug 1, 2006 - fix bug in determining/applying target
 **               some changes in how quantiles are estimated in determining/applyin target
 ** Oct 26, 2006 - fix unbalanced UNPROTECT in use_target.
 ** Nov 13, 2006 - remove median code
 ** May 20, 2007 - move to preprocessCore. clean up code.
 ** May 26, 2007 - fix memory leak in qnorm_c_determine_target
 ** Jul 12, 2007 - improved ties handling (fixes off by "half" error which affects even numbers of ties)
 ** Jul 14, 2007 - add NA handling to qnorm_c_using_target and qnorm_c_determine_target
 ** Oct 6, 2007 - initial pthreads support for qnorm_c supplied by Paul Gordon <gordonp@ucalgary.ca>
 ** Oct 9, 2007 - modify how columns are partioned to threads (when less columns than threads)
 ** Mar 14, 2008 - multithreaded qnorm_c_determine_target based on pthreads
 ** Mar 15, 2008 - multithreaded qnorm_c_using_target based on pthreads
 **
 ***********************************************************/

/*****************************************************************************************************
 *****************************************************************************************************
 **
 ** GENERAL NOTE: Many of the functions take pointers for arguements that are essentially just
 **               int's. This is mostly legacy for when the functions were called via .C() in R rather
 **               than via the .Call() interface.
 **
 *****************************************************************************************************
 *****************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rma_common.h"
#include "qnorm.h"


#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>
 
#ifdef USE_PTHREADS
#include <pthread.h>
#define THREADS_ENV_VAR "R_THREADS"
pthread_mutex_t mutex_R;
struct loop_data{
  double *data;
  double *row_mean;
  int *rows;
  int *cols;
  int *row_meanlength;
  int start_col;
  int end_col;
};
#endif

/*****************************************************************************************************
 *****************************************************************************************************
 **
 ** This section defines utility functions and data types
 **
 **
 *****************************************************************************************************
 *****************************************************************************************************/


/*************************************************************
 **
 ** the dataitem record is used to keep track of data indicies 
 ** along with data value when sorting and unsorting in the 
 ** quantile algorithm.
 **
 ************************************************************/

typedef struct{
  double data;
  int rank;
} dataitem;
  


/*************************************************************
 **
 ** the dataitem_block record is used to keep track of data indicies 
 ** along with data value when sorting and unsorting in the 
 ** quantile algorithm in blocks
 **
 ************************************************************/

typedef struct{
  double data;
  int rank;
  int block;
} dataitem_block;


/***********************************************************
 **  
 ** int min(int x1, int x2)							    
 **
 ** returns the minimum of x1 and x2
 **		    
 **********************************************************/

/* static int min(int x1,int x2){
 * if (x1 > x2)
 *   return x2;
 * else
 *   return x1;
 *}
 */

/**********************************************************
 **
 ** int sort_fn(const void *a1,const void *a2)
 **
 ** a comparison function for sorting objects of the dataitem type.
 **
 **
 **********************************************************/

static int sort_fn(const void *a1,const void *a2){
  dataitem *s1, *s2;
  s1 = (dataitem *)a1;
  s2 = (dataitem *)a2;
  
  if (s1->data < s2->data)
    return (-1);
  if (s1 ->data > s2->data)
    return (1);
  return 0;
}


/**********************************************************
 **
 ** int sort_fn_blocks(const void *a1,const void *a2)
 **
 ** a comparison function for sorting objects of the dataitem_blocks type.
 **
 **
 **********************************************************/

static int sort_fn_blocks(const void *a1,const void *a2){
  dataitem_block *s1, *s2;
  s1 = (dataitem_block *)a1;
  s2 = (dataitem_block *)a2;
  
  if (s1->block < s2->block){
    return (-1);
  } else if (s1->block > s2->block){
    return (1);
  } else {
    if (s1->data < s2->data)
      return (-1);
    if (s1 ->data > s2->data)
      return (1);
    return 0;
  }
}





/************************************************************
 **
 ** dataitem **get_di_matrix(double *data, int rows, int cols)
 **
 ** given data  form a matrix of dataitems, each element of
 ** matrix holds datavalue and original index so that 
 ** normalized data values can be resorted to the original order
 **
 ***********************************************************/

static dataitem **get_di_matrix(double *data, int rows, int cols){
  int i,j;
  dataitem **dimat;
  /* dataitem *xtmp; */
  
  dimat = (dataitem **)Calloc((cols),dataitem *);
  
  if (dimat == NULL){
    printf("\nERROR - Sorry the normalization routine could not allocate adequate memory\n       You probably need more memory to work with a dataset this large\n");
  }

  /* xtmp = malloc(cols*rows*sizeof(dataitem));
     for (j=0; j < cols; j++, xtmp +=rows) dimat[j] = xtmp; */
  
  for (j=0; j < cols; j++)
    dimat[j] = Calloc(rows,dataitem);



  for (j =0; j < cols; j++)
    for (i =0; i < rows; i++){
      dimat[j][i].data = data[j*rows + i];
      dimat[j][i].rank = i;
    }

  return(dimat); 
}

/************************************************************
 **
 ** double *get_ranks(dataitem *x,int n)
 **
 ** get ranks in the same manner as R does. Assume that *x is
 ** already sorted
 **
 *************************************************************/

static void get_ranks(double *rank, dataitem *x,int n){
  int i,j,k;
   
  i = 0;

  while (i < n) {
    j = i;
    while ((j < n - 1) && (x[j].data  == x[j + 1].data))
      j++;
    if (i != j) {
      for (k = i; k <= j; k++)
	rank[k] = (i + j + 2) / 2.0;
    }
    else
      rank[i] = i + 1;
    i = j + 1;
  }
  /*return rank;*/
}


/************************************************************
 **
 ** double *get_ranks_blocks(dataitem *x,int n)
 **
 ** get ranks in the same manner as R does. Assume that *x is
 ** already sorted
 **
 *************************************************************/

static void get_ranks_blocks(double *rank, dataitem_block *x,int n){
  int i,j,k;
   
  i = 0;

  while (i < n) {
    j = i;
    while ((j < n - 1) && (x[j].data  == x[j + 1].data) && (x[j].block  == x[j + 1].block))
      j++;
    if (i != j) {
      for (k = i; k <= j; k++)
	rank[k] = (i + j + 2) / 2.0;
    }
    else
      rank[i] = i + 1;
    i = j + 1;
  }
  /*return rank;*/
}









/*************************************************************************
 **
 ** static double weights_huber(double u, double k)
 **
 ** double u - standardized residuals
 ** doubke k - tuning parameter
 **
 ** Used to get weights for M-estimation.
 **
 *************************************************************************/

static double weights_huber(double u, double k){
  
  if ( 1 < k/fabs(u)){
    return 1.0;
  } else {
    return  k/fabs(u);
  }
}


/**************************************************************************
 **
 ** static double med_abs(double *x, int length)
 **
 ** double *x - a data vector
 ** int length - length of x
 **
 ** Compute the median absolute value of a data vector
 **
 *************************************************************************/

static double med_abs(double *x, int length){
  int i;
  double med_abs;
  double *buffer = Calloc(length,double);

  for (i = 0; i < length; i++)
    buffer[i] = fabs(x[i]);

  med_abs = median_nocopy(buffer,length);

  Free(buffer);
  return(med_abs);
}


/*****************************************************************************************************
 *****************************************************************************************************
 **
 ** The following block implements the standard quantile normalization function (aka "classic")
 **
 **
 *****************************************************************************************************
 *****************************************************************************************************/

void normalize_determine_target(double *data, double *row_mean, int *rows, int *cols, int start_col, int end_col){
  int i, j;
  double *datvec = (double *)Calloc((*rows),double);
  
#ifdef USE_PTHREADS
  long double *row_submean = (long double *)Calloc((*rows), long double);
  for (i =0; i < *rows; i++){
    row_submean[i] = 0.0;
  }
#endif

  for (j = start_col; j <= end_col; j++){

    /* first find the normalizing distribution */
    for (i = 0; i < *rows; i++){
      datvec[i] = data[j*(*rows) + i];
    }
    qsort(datvec,*rows,sizeof(double),(int(*)(const void*, const void*))sort_double);
    for (i = 0; i < *rows; i++){
#ifdef USE_PTHREADS
      row_submean[i] += datvec[i];
#else
      row_mean[i] += datvec[i]/((double)*cols);
#endif
    }
  }
  Free(datvec);

#ifdef USE_PTHREADS
  /* add to the global running total, will do the division after all threads finish (for precision of the result) */
  pthread_mutex_lock (&mutex_R);
  for (i = 0; i < *rows; i++){
    row_mean[i] += (double) row_submean[i];
  }
  pthread_mutex_unlock (&mutex_R);
#endif
}
  
void normalize_distribute_target(double *data, double *row_mean, int *rows, int *cols, int start_col, int end_col){ 
  int i, j, ind;
  dataitem **dimat;
  double *ranks = (double *)Calloc((*rows),double);

  dimat = (dataitem **)Calloc(1,dataitem *);
  dimat[0] = (dataitem *)Calloc(*rows,dataitem);

  for (j = start_col; j <= end_col; j++){
    for (i = 0; i < *rows; i++){
      dimat[0][i].data = data[j*(*rows) + i];
      dimat[0][i].rank = i;
    }
    qsort(dimat[0],*rows,sizeof(dataitem),sort_fn);
    get_ranks(ranks,dimat[0],*rows);
    for (i = 0; i < *rows; i++){
      ind = dimat[0][i].rank;
      if (ranks[i] - floor(ranks[i]) > 0.4){
	data[j*(*rows) +ind] = 0.5*(row_mean[(int)floor(ranks[i])-1] + row_mean[(int)floor(ranks[i])]);
      } else { 
	data[j*(*rows) +ind] = row_mean[(int)floor(ranks[i])-1];
      }
    }
  }

  Free(ranks);
  Free(dimat[0]);
  Free(dimat);
}

#ifdef USE_PTHREADS
void *normalize_group(void *data){
  struct loop_data *args = (struct loop_data *) data;
  normalize_determine_target(args->data, args->row_mean, args->rows, args->cols, args->start_col, args->end_col);
}

void *distribute_group(void *data){
  struct loop_data *args = (struct loop_data *) data;
  normalize_distribute_target(args->data, args->row_mean, args->rows, args->cols, args->start_col, args->end_col);
}
#endif

/*********************************************************
 **
 ** void qnorm_c(double *data, int *rows, int *cols)
 **
 **  this is the function that actually implements the
 ** quantile normalization algorithm. It is called from R.
 **
 ** returns 1 if there is a problem, 0 otherwise
 **
 ** Note that this function does not handle missing data (ie NA)
 **
 ********************************************************/

int qnorm_c(double *data, int *rows, int *cols){
  int i;
  double *row_mean = (double *)Calloc((*rows),double);
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  for (i =0; i < *rows; i++){
    row_mean[i] = 0.0;
  }

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
  
  if (num_threads < *cols){
    chunk_size = *cols/num_threads;
    chunk_size_d = ((double) *cols)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((*cols < num_threads ? *cols : num_threads), struct loop_data);

  args[0].data = data;
  args[0].row_mean = row_mean;
  args[0].rows = rows;  
  args[0].cols = cols;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < *cols; i+=chunk_size){
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
     returnCode = pthread_create(&threads[i], &attr, normalize_group, (void *) &(args[i]));
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

  /* When in threaded mode, row_mean is the sum, waiting for a final division here, to maintain precision */
  for (i = 0; i < *rows; i++){
    row_mean[i] /= (double)*cols;
  }

  /* now assign back the target normalization distribution to a given set of columns */
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, distribute_group, (void *) &(args[i]));
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
  normalize_determine_target(data, row_mean, rows, cols, 0, *cols-1);
  normalize_distribute_target(data, row_mean, rows, cols, 0, *cols-1); 
#endif

  Free(row_mean);

  return 0;
}





/*********************************************************
 **
 ** SEXP R_qnorm_c(SEXP X)
 **
 ** SEXP X      - a matrix
 ** SEXP copy   - a flag if TRUE then make copy
 **               before normalizing, if FALSE work in place
 **               note that this can be dangerous since
 **               it will change the original matrix.
 **
 ** returns a quantile normalized matrix.
 **
 ** This is a .Call() interface for quantile normalization
 **
 *********************************************************/

SEXP R_qnorm_c(SEXP X, SEXP copy){

  SEXP Xcopy,dim1;
  double *Xptr;
  int rows,cols;
  
  PROTECT(dim1 = getAttrib(X,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  if (asInteger(copy)){
    PROTECT(Xcopy = allocMatrix(REALSXP,rows,cols));
    copyMatrix(Xcopy,X,0);
  } else {
    Xcopy = X;
  }
  Xptr = NUMERIC_POINTER(AS_NUMERIC(Xcopy));
  
  qnorm_c(Xptr, &rows, &cols);
  if (asInteger(copy)){
    UNPROTECT(2);
  } else {
    UNPROTECT(1);
  }
  return Xcopy;
}




/*****************************************************************************************************
 *****************************************************************************************************
 **
 ** The following block of code provides the "robust" quantile normalization. In addition it tries to 
 ** give the equivalent to the R code functionality for selecting arrays to remove before determining
 **
 **
 *****************************************************************************************************
 *****************************************************************************************************/

/*********************************************************
 **
 ** void qnorm_robust_c(double *data,double *weights, int *rows, int *cols, int *use_median,int *use_log2,int *weight_scheme)
 ** 
 ** double *data
 ** double *weights
 ** int *rows
 ** int *cols
 ** int *use_median
 ** int *use_log2
 ** int *weight_scheme
 **
 ** This function implements the "robust" quantile normalizer
 **
 ** Note that this function does not handle NA values.
 **
 ********************************************************/

int qnorm_robust_c(double *data,double *weights, int *rows, int *cols, int *use_median, int *use_log2, int *weight_scheme){
  
  int i,j,ind,rep;  
  int half,length;
  dataitem **dimat;
  double *row_mean = (double *)Calloc((*rows),double);
  double *datvec=0; /* = (double *)Calloc(*cols,double); */
  double *ranks = (double *)Calloc((*rows),double);
  
  double sum_weights = 0.0;
  double mean, scale; /* used in M-estimation routine */


  
  for (i =0; i < *rows; i++){
    row_mean[i] = 0.0;
  }


  if ((*weight_scheme == 0) && !(*use_median)){
    datvec = (double *)Calloc(*rows,double);
    
    if (!(*use_log2)){
      for (j = 0; j < *cols; j++){
	sum_weights+=weights[j];
      }


      for (j = 0; j < *cols; j++){
	for (i =0; i < *rows; i++){
	  datvec[i] = data[j*(*rows) + i];
	}
	qsort(datvec,*rows,sizeof(double),(int(*)(const void*, const void*))sort_double);
	if (weights[j] > 0.0){
	  for (i =0; i < *rows; i++){
	    row_mean[i] += weights[j]*datvec[i]/sum_weights;
	  }
	}
      } 
    } else {
      for (j = 0; j < *cols; j++){
	sum_weights+=weights[j];
      }


      for (j = 0; j < *cols; j++){
	for (i =0; i < *rows; i++){
	  datvec[i] = data[j*(*rows) + i];
	}
	qsort(datvec,*rows,sizeof(double),(int(*)(const void*, const void*))sort_double);
	if (weights[j] > 0.0){
	  for (i =0; i < *rows; i++){
	    row_mean[i] += weights[j]*(log(datvec[i])/log(2.0))/sum_weights;
	  }
	}
      } 
      for (i =0; i < *rows; i++){
	row_mean[i] = pow(2.0,row_mean[i]);
      }
    } 
  } else if ((*weight_scheme == 1) && !(*use_median)){
    /** row-wise huber weights **/
    dimat = get_di_matrix(data, *rows, *cols);
   
    datvec = Calloc(*cols,double);
    
    for (j=0; j < *cols; j++){
      qsort(dimat[j],*rows,sizeof(dataitem),sort_fn);
    }
    

    if (!(*use_log2)){
      for (i=0; i < *rows; i++){
	for (j=0; j < *cols; j++)
	  datvec[j] = dimat[j][i].data;
	
	/* five step huber estimate of location */
	mean = 0.0;
	for (j=0; j < *cols; j++){
	  mean += datvec[j]/(double)(*cols);
	}
	
	for (rep = 0; rep < 5; rep++){
	  for (j=0; j < *cols; j++){
	    datvec[j] = datvec[j] - mean;
	  }
	  scale = med_abs(datvec,*cols)/0.6745;
	  if (scale == 0.0){
	    break;
	  }
	  
	  for (j=0; j < *cols; j++){
	    datvec[j] = (datvec[j] - mean)/scale;
	  }
	  
	  mean = 0.0;
	  sum_weights=0.0;
	  for (j=0; j < *cols; j++){
	    mean+= weights_huber(datvec[j],1.345) * dimat[j][i].data;
	    sum_weights+=weights_huber(datvec[j],1.345);
	  }
	  mean/=sum_weights;
	  for (j=0; j < *cols; j++)
	    datvec[j] = dimat[j][i].data;
	  /* Rprintf("rep %d %f %f\n",rep,mean,scale); */
	}
	row_mean[i] = mean;
      }
    } else {
      for (i=0; i < *rows; i++){
	for (j=0; j < *cols; j++)
	  datvec[j] = log(dimat[j][i].data)/log(2.0);
	
	/* five step huber estimate of location */
	mean = 0.0;
	for (j=0; j < *cols; j++){
	  mean += datvec[j]/(double)(*cols);
	}
	
	for (rep = 0; rep < 5; rep++){
	  for (j=0; j < *cols; j++){
	    datvec[j] = datvec[j] - mean;
	  }
	  scale = med_abs(datvec,*cols)/0.6745;
	  if (scale == 0.0){
	    break;
	  }
	  
	  for (j=0; j < *cols; j++){
	    datvec[j] = (datvec[j] - mean)/scale;
	  }
	  
	  mean = 0.0;
	  sum_weights=0.0;
	  for (j=0; j < *cols; j++){
	    mean+= weights_huber(datvec[j],1.345) * log(dimat[j][i].data)/log(2.0);
	    sum_weights+=weights_huber(datvec[j],1.345);
	  }
	  mean/=sum_weights;
	  for (j=0; j < *cols; j++)
	    datvec[j] = log(dimat[j][i].data)/log(2.0);
	  /* Rprintf("rep %d %f %f\n",rep,mean,scale); */
	}
	row_mean[i] = pow(2.0,mean);
      }
    }
    for (j=0; j < *cols; j++){
      Free(dimat[j]);
    }
    
    Free(dimat);




  } else if ((*use_median)){
    dimat = get_di_matrix(data, *rows, *cols);
   
    datvec = Calloc(*cols,double);
    
    for (j=0; j < *cols; j++){
      qsort(dimat[j],*rows,sizeof(dataitem),sort_fn);
    }
    
    for (i=0; i < *rows; i++){
      for (j=0; j < *cols; j++)
	datvec[j] = dimat[j][i].data;
      
      
      qsort(datvec,*cols,sizeof(double),(int(*)(const void*, const void*))sort_double);
      half = (*cols + 1)/2;
      length = *cols;
      if (length % 2 == 1){
	row_mean[i] = datvec[half - 1];
      } else {
	row_mean[i] = (datvec[half] + datvec[half-1])/2.0;
      }
    }
    for (j=0; j < *cols; j++){
      Free(dimat[j]);
    }
    
    Free(dimat);
  } else {
    error("Not sure that these inputs are recognised for the robust quantile normalization routine.\n");


  }
	     




  /* now assign back distribution */
  dimat = (dataitem **)Calloc(1,dataitem *);
  dimat[0] = (dataitem *)Calloc(*rows,dataitem);
  
  for (j = 0; j < *cols; j++){
    for (i =0; i < *rows; i++){
      dimat[0][i].data = data[j*(*rows) + i];
      dimat[0][i].rank = i;
    }
    qsort(dimat[0],*rows,sizeof(dataitem),sort_fn);
    get_ranks(ranks,dimat[0],*rows);
    for (i =0; i < *rows; i++){
      ind = dimat[0][i].rank;
      if (ranks[i] - floor(ranks[i]) > 0.4){
	data[j*(*rows) +ind] = 0.5*(row_mean[(int)floor(ranks[i])-1] + row_mean[(int)floor(ranks[i])]);
      } else { 
	data[j*(*rows) +ind] = row_mean[(int)floor(ranks[i])-1];
      }
    }
  }
  
  Free(ranks);
  Free(datvec);
  Free(dimat[0]);
  
  Free(dimat);
  Free(row_mean);
  return 0;
  
}




/*********************************************************
 **
 ** SEXP R_qnorm_robust_c(SEXP X)
 **
 ** SEXP X      - a matrix
 ** SEXP copy   - a flag if TRUE then make copy
 **               before normalizing, if FALSE work in place
 **               note that this can be dangerous since
 **               it will change the original matrix.
 **
 ** returns a quantile normalized matrix.
 **
 ** This is a .Call() interface for quantile normalization (of the robust variety)
 **
 *********************************************************/


SEXP R_qnorm_robust_c(SEXP X, SEXP copy, SEXP R_weights, SEXP R_use_median, SEXP R_use_log2, SEXP R_weight_scheme){

  SEXP Xcopy,dim1;
  double *Xptr;
  int rows,cols;
  
  double *weights;
  int use_median;
  int use_log2;
  int weight_scheme;


  
  PROTECT(dim1 = getAttrib(X,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  if (asInteger(copy)){
    PROTECT(Xcopy = allocMatrix(REALSXP,rows,cols));
    copyMatrix(Xcopy,X,0);
  } else {
    Xcopy = X;
  }
  Xptr = NUMERIC_POINTER(AS_NUMERIC(Xcopy));
  
  weights =  NUMERIC_POINTER(AS_NUMERIC(R_weights));
  
  use_median = INTEGER(R_use_median)[0];
  use_log2 = INTEGER(R_use_log2)[0];
  weight_scheme = INTEGER(R_weight_scheme)[0];


  qnorm_robust_c(Xptr,weights, &rows, &cols, &use_median, &use_log2, &weight_scheme);
  if (asInteger(copy)){
    UNPROTECT(2);
  } else {
    UNPROTECT(1);
  }
  return Xcopy;
}



/*****************************************************************
 **
 ** static double compute_var(double *x, int length)
 **
 ** double *x - data vector
 ** int length - length of x
 **
 ** compute the sample variance of a data vector
 **
 *****************************************************************/

static double compute_var(double *x, int length){

  int i;
  double sum=0.0,sum2=0.0;

  for (i = 0; i < length; i++){
    sum+=x[i];
  }

  sum = sum/(double)length;
  for (i=0; i < length; i++){
    sum2+=(x[i]-sum)*(x[i] - sum);
  }

  return(sum2/(double)(length-1));
}

/*****************************************************************
 **
 ** static double compute_means(double *x, int length)
 **
 ** double *x - data vector
 ** int length - length of x
 **
 ** compute the sample mean of a data vector
 **
 **
 *****************************************************************/

static double compute_means(double *x, int length){

  int i;
  double sum=0.0; 

  for (i = 0; i < length; i++){
    sum+=x[i];
  }

  sum = sum/(double)length;
  
  return(sum);
}

/*****************************************************************
 **
 ** static void remove_order_variance(double *x, int rows, int cols, int n_remove, double *weights)
 **
 ** double *x 
 ** int rows
 ** int cols
 ** int n_remove
 ** double *weights
 **
 *****************************************************************/

static void remove_order_variance(double *x, int rows, int cols, int n_remove, double *weights){

  double *vars = Calloc(cols,double);
  double *vars_row = Calloc(cols,double);
  double *vars_col = Calloc(cols,double);

  double *results = Calloc(cols*cols,double);
  
  int i,j;


  for (j=0; j < cols; j++){
    vars[j] = compute_var(&x[j*rows],rows);
  }
  
  for (i = 0; i < cols -1; i++){
    for (j = i+1; j < cols; j++){
      results[j*cols + i] = vars[i]/vars[j];
      results[i*cols + j] = vars[j]/vars[i];
    }
  }

  for (i = 0; i < cols; i++){
    vars_row[i] = 0.0;
    for (j=0; j < cols; j++){
      vars_row[i]+=results[j*cols + i];
    }

  }


  for (j = 0; j < cols; j++){
    vars_col[j] = 0.0;
    for (i=0; i < cols; i++){
      vars_col[j]+=results[j*cols + i];
    }
  }
  

  for (j=0; j < cols; j++){
    vars_row[j] = vars[j] = vars_row[j] + vars_col[j];
  }

  qsort(vars_row,cols,sizeof(double),(int(*)(const void*, const void*))sort_double);
  
  for (i=cols-1; i >= cols - n_remove; i--){
    for (j=0; j < cols; j++){

      if (vars[j] == vars_row[i]){
	weights[j] =0.0;
	break;
      }
    }
  }
  
  Free(results);
  Free(vars);
  Free(vars_row);
  Free(vars_col);


}


/*****************************************************************
 **
 ** static void remove_order_mean(double *x, int rows, int cols, int n_remove, double *weights)
 **
 ** double *x 
 ** int rows
 ** int cols
 ** int n_remove
 ** double *weights
 **
 *****************************************************************/



static void remove_order_mean(double *x, int rows, int cols, int n_remove, double *weights){

  
  double *means = Calloc(cols,double);
  double *means_row = Calloc(cols,double);
  double *means_col = Calloc(cols,double);

  double *results = Calloc(cols*cols,double);
  
  int i,j;

  for (j=0; j < cols; j++){
    means[j] = compute_means(&x[j*rows],rows);
  }
  
  for (i = 0; i < cols -1; i++){
    for (j = i+1; j < cols; j++){
      results[j*cols + i] = means[i] - means[j];
      results[i*cols + j] = means[j]- means[i];
    }
  }


  for (j = 0; j < cols; j++){
    means_col[j] = 0.0;
    for (i=0; i < cols; i++){
      means_col[j]+=results[j*cols + i];
    }
  }
  

  for (j=0; j < cols; j++){
    means_row[j] = means[j] = fabs(means_col[j]);
  }

  qsort(means_row,cols,sizeof(double),(int(*)(const void*, const void*))sort_double);
  
  for (i=cols-1; i >= cols - n_remove; i--){
    for (j=0; j < cols; j++){
      if (means[j] == means_row[i]){
	weights[j] =0.0;
	break;
      }
    }
  }
  
  Free(results);
  Free(means);
  Free(means_row);
  Free(means_col);





}

/*****************************************************************
 **
 ** static void remove_order_both(double *x, int rows, int cols, int n_remove, double *weights)
 **
 ** double *x 
 ** int rows
 ** int cols
 ** int n_remove
 ** double *weights
 **
 *****************************************************************/


static void remove_order_both(double *x, int rows, int cols, int n_remove, double *weights){

  double *means = Calloc(cols,double);
  double *means_row = Calloc(cols,double);
  double *means_col = Calloc(cols,double);

  double *vars = Calloc(cols,double);
  double *vars_row = Calloc(cols,double);
  double *vars_col = Calloc(cols,double);



  double *results = Calloc(cols*cols,double);
  
  int i,j;

  int n_remove_mean;
  int n_remove_var;


  if (n_remove % 2 ==0){
    n_remove_var = n_remove/2;
    n_remove_mean = n_remove/2;
  } else {
    n_remove_var = n_remove/2 + 1;
    n_remove_mean = n_remove/2;
  }


  /* Work out all the stuff for excluding means */


  for (j=0; j < cols; j++){
    means[j] = compute_means(&x[j*rows],rows);
  }
  
  for (i = 0; i < cols -1; i++){
    for (j = i+1; j < cols; j++){
      results[j*cols + i] = means[i] - means[j];
      results[i*cols + j] = means[j]- means[i];
    }
  }


  for (j = 0; j < cols; j++){
    means_col[j] = 0.0;
    for (i=0; i < cols; i++){
      means_col[j]+=results[j*cols + i];
    }
  }
  

  for (j=0; j < cols; j++){
    means_row[j] = means[j] = fabs(means_col[j]);
  }

  qsort(means_row,cols,sizeof(double),(int(*)(const void*, const void*))sort_double);



  /* Work out all the stuff for excluding variances */


 for (j=0; j < cols; j++){
    vars[j] = compute_var(&x[j*rows],rows);
  }
  
  for (i = 0; i < cols -1; i++){
    for (j = i+1; j < cols; j++){
      results[j*cols + i] = vars[i]/vars[j];
      results[i*cols + j] = vars[j]/vars[i];
    }
  }

  for (i = 0; i < cols; i++){
    vars_row[i] = 0.0;
    for (j=0; j < cols; j++){
      vars_row[i]+=results[j*cols + i];
    }

  }


  for (j = 0; j < cols; j++){
    vars_col[j] = 0.0;
    for (i=0; i < cols; i++){
      vars_col[j]+=results[j*cols + i];
    }
  }
  

  for (j=0; j < cols; j++){
    vars_row[j] = vars[j] = vars_row[j] + vars_col[j];
  }

  qsort(vars_row,cols,sizeof(double),(int(*)(const void*, const void*))sort_double);
  
  for (i=cols-1; i >= cols - n_remove_var; i--){
    for (j=0; j < cols; j++){
      if (vars[j] == vars_row[i]){
	weights[j] =0.0;
	break;
      }
    }
  }

  for (i=cols-1; i >= cols - n_remove_mean; i--){
    for (j=0; j < cols; j++){
      if (means[j] == means_row[i]){
	if (weights[j] ==0.0){
	  /* means it has already been excluded by variance rule. So need to look one more along */
	  n_remove_mean+=1;
	} else {
	  weights[j] =0.0;
	  break;
	}
      }
    }
  }


}











SEXP R_qnorm_robust_weights(SEXP X, SEXP remove_extreme, SEXP n_remove){


  SEXP weights,dim1;


  int rows, cols;
  int j;

  PROTECT(dim1 = getAttrib(X,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];

  PROTECT(weights = allocVector(REALSXP,cols));

  for (j=0; j < cols; j++){
    REAL(weights)[j] = 1.0;
  }

  if (strcmp(CHAR(VECTOR_ELT(remove_extreme,0)),"variance") == 0){
    remove_order_variance(REAL(X), rows, cols, INTEGER(n_remove)[0], REAL(weights));
  }

  if (strcmp(CHAR(VECTOR_ELT(remove_extreme,0)),"mean") == 0){
    remove_order_mean(REAL(X), rows, cols, INTEGER(n_remove)[0], REAL(weights));
  }

  if (strcmp(CHAR(VECTOR_ELT(remove_extreme,0)),"both") == 0){
    remove_order_both(REAL(X), rows, cols, INTEGER(n_remove)[0], REAL(weights));
  }



  
  UNPROTECT(2);
  return weights;

}


/*****************************************************************************************************
 *****************************************************************************************************
 **
 ** The following block of code provides quantile normalization where a specified target vector is given.
 ** In addition it deals with cases of un equal length by estimating the appropriate quantiles
 **
 *****************************************************************************************************
 *****************************************************************************************************/


void using_target(double *data, int *rows, int *cols, double *target, int *targetrows, int start_col, int end_col){

  int i,j,ind,target_ind;
  
  dataitem **dimat;

  double *row_mean = target;

  double *ranks = (double *)Calloc((*rows),double);
  double samplepercentile;
  double target_ind_double,target_ind_double_floor;

  int targetnon_na = *targetrows;
  int non_na = 0;
  


  if (*rows == targetnon_na){
    /* now assign back distribution */
    /* this is basically the standard story */
    
    dimat = (dataitem **)Calloc(1,dataitem *);
    dimat[0] = (dataitem *)Calloc(*rows,dataitem);
    
    for (j = start_col; j <= end_col; j++){
      non_na = 0;
      for (i =0; i < *rows; i++){
	if (ISNA(data[j*(*rows) + i])){
	  
	} else {
	  dimat[0][non_na].data = data[j*(*rows) + i];
	  dimat[0][non_na].rank = i;
	  non_na++;
	}
      }
      if (non_na == *rows){
	qsort(dimat[0],*rows,sizeof(dataitem),sort_fn);
	get_ranks(ranks,dimat[0],*rows);
	for (i =0; i < *rows; i++){
	  ind = dimat[0][i].rank;
	  if (ranks[i] - floor(ranks[i]) > 0.4){
	    data[j*(*rows) +ind] = 0.5*(row_mean[(int)floor(ranks[i])-1] + row_mean[(int)floor(ranks[i])]);
	  } else { 
	    data[j*(*rows) +ind] = row_mean[(int)floor(ranks[i])-1];
	  }
	}
      } else {
	/* we are going to have to estimate the quantiles */ 
	qsort(dimat[0],non_na,sizeof(dataitem),sort_fn);
	get_ranks(ranks,dimat[0],non_na);
	for (i =0; i < non_na; i++){
	  
	  samplepercentile = (double)(ranks[i] - 1)/(double)(non_na-1);
	  /* target_ind_double = 1.0/3.0 + ((double)(*targetrows) + 1.0/3.0) * samplepercentile; */
	  target_ind_double = 1.0 + ((double)(targetnon_na) - 1.0) * samplepercentile;
	  target_ind_double_floor = floor(target_ind_double + 4*DOUBLE_EPS);
	  
	  target_ind_double = target_ind_double - target_ind_double_floor;
	  
	  if (fabs(target_ind_double) <=  4*DOUBLE_EPS){
	    target_ind_double = 0.0;
	  }
	  
	  
	  if (target_ind_double  == 0.0){
	    target_ind = (int)floor(target_ind_double_floor + 0.5); /* nearbyint(target_ind_double_floor); */	
	    ind = dimat[0][i].rank;
	    data[j*(*rows) +ind] = row_mean[target_ind-1];
	  } else if (target_ind_double == 1.0){
	    target_ind = (int)floor(target_ind_double_floor + 1.5); /* (int)nearbyint(target_ind_double_floor + 1.0); */ 
	    ind = dimat[0][i].rank;
	    data[j*(*rows) +ind] = row_mean[target_ind-1];
	  } else {
	    target_ind = (int)floor(target_ind_double_floor + 0.5); /* nearbyint(target_ind_double_floor); */	
	    ind = dimat[0][i].rank;
	    if ((target_ind < *targetrows) && (target_ind > 0)){
	      data[j*(*rows) +ind] = (1.0- target_ind_double)*row_mean[target_ind-1] + target_ind_double*row_mean[target_ind];
	    } else if (target_ind >= *targetrows){
	      data[j*(*rows) +ind] = row_mean[*targetrows-1];
	    } else {
	      data[j*(*rows) +ind] = row_mean[0];
	    }
	  }
	}
      }
    }
  } else {
    /** the length of the target distribution and the size of the data matrix differ **/
    /** need to estimate quantiles **/
    dimat = (dataitem **)Calloc(1,dataitem *);
    dimat[0] = (dataitem *)Calloc(*rows,dataitem);
    
    for (j = start_col; j <= end_col; j++){
      non_na = 0;
      for (i =0; i < *rows; i++){	
	if (ISNA(data[j*(*rows) + i])){

	} else {
	  dimat[0][non_na].data = data[j*(*rows) + i];
	  dimat[0][non_na].rank = i;
	  non_na++;
	}
      }
      
      qsort(dimat[0],non_na,sizeof(dataitem),sort_fn);
      get_ranks(ranks,dimat[0],non_na);
      for (i =0; i < non_na; i++){

	samplepercentile = (double)(ranks[i] - 1.0)/(double)(non_na -1);
	/* target_ind_double = 1.0/3.0 + ((double)(*targetrows) + 1.0/3.0) * samplepercentile; */
	target_ind_double = 1.0 + ((double)(targetnon_na) - 1.0) * samplepercentile;
	target_ind_double_floor = floor(target_ind_double + 4*DOUBLE_EPS);
	
	target_ind_double = target_ind_double - target_ind_double_floor;

	if (fabs(target_ind_double) <=  4*DOUBLE_EPS){
	  target_ind_double = 0.0;
	}

	
	if (target_ind_double  == 0.0){
	  target_ind = (int)floor(target_ind_double_floor + 0.5); /* nearbyint(target_ind_double_floor); */	
	  ind = dimat[0][i].rank;
	  data[j*(*rows) +ind] = row_mean[target_ind-1];
	} else if (target_ind_double == 1.0){
	  target_ind = (int)floor(target_ind_double_floor + 1.5); /* (int)nearbyint(target_ind_double_floor + 1.0); */ 
	  ind = dimat[0][i].rank;
	  data[j*(*rows) +ind] = row_mean[target_ind-1];
	} else {
	  target_ind = (int)floor(target_ind_double_floor + 0.5); /* nearbyint(target_ind_double_floor); */	
	  ind = dimat[0][i].rank;
	  if ((target_ind < *targetrows) && (target_ind > 0)){
	    data[j*(*rows) +ind] = (1.0- target_ind_double)*row_mean[target_ind-1] + target_ind_double*row_mean[target_ind];
	  } else if (target_ind >= *targetrows){
	    data[j*(*rows) +ind] = row_mean[*targetrows-1];
	  } else {
	    data[j*(*rows) +ind] = row_mean[0];
	  }
	}
	
      }
    }
  }
  Free(dimat[0]);
  Free(dimat);

}





#ifdef USE_PTHREADS
void *using_target_group(void *data){
  struct loop_data *args = (struct loop_data *) data;
  using_target(args->data,  args->rows, args->cols, args->row_mean, args->row_meanlength, args->start_col, args->end_col);  
}
#endif



/*****************************************************************
 **
 ** int qnorm_c_using_target(double *data, int *rows, int *cols, double *target, int *targetrows)
 **
 ** double *data - a matrix of data to be normalized
 ** int *rows - dimensions of data
 ** int *cols - dimensions of data
 ** double *target - vector containing target distribution (ie distribution to be
 **                  normalized to)
 ** int *targetrows - length of target distribution vector
 **
 **
 ** if targetrows == rows then the standard methodology is used.
 ** 
 ** in other cases the appropriate quantiles to be normalized to are determined in a method
 ** equivalent to what you get using "type 8" with the quantile function
 **
 ** Note sample percentiles are calculated using i/(n+1)  (ie if there is 
 ** only 2 observations, the first sample percentile is 1/3 = 0.333,
 ** the second sample percentile will be 2/3 = 0.6666
 **
 ** 
 **
 *****************************************************************/



int qnorm_c_using_target(double *data, int *rows, int *cols, double *target, int *targetrows){


  
  int i;

  double *row_mean; 
  int targetnon_na = 0;

#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif
  
  row_mean = (double *)Calloc(*targetrows,double);
  
  /* first find the normalizing distribution */
  for (i =0; i < *targetrows; i++){
    if (ISNA(target[i])){

    } else {
      row_mean[targetnon_na] = target[i];
      targetnon_na++;
    }
  }

  qsort(row_mean,targetnon_na,sizeof(double),(int(*)(const void*, const void*))sort_double);

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
  
  if (num_threads < *cols){
    chunk_size = *cols/num_threads;
    chunk_size_d = ((double) *cols)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((*cols < num_threads ? *cols : num_threads), struct loop_data);

  args[0].data = data;
  args[0].row_mean = row_mean;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].row_meanlength = &targetnon_na;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < *cols; i+=chunk_size){
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
     returnCode = pthread_create(&threads[i], &attr, using_target_group, (void *) &(args[i]));
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
  using_target(data, rows, cols, row_mean, &targetnon_na, 0, *cols -1);
#endif


  Free(row_mean);
  return 0;



}




void determine_target(double *data, double *row_mean, int *rows, int *cols, int start_col, int end_col){

  
  int i,j,row_mean_ind;
  double *datvec;
  
  double row_mean_ind_double,row_mean_ind_double_floor;
  double samplepercentile;
  
  int non_na;
#ifdef USE_PTHREADS
  long double *row_submean = (long double *)Calloc((*rows), long double);
#endif

  datvec = (double *)Calloc(*rows,double);
  
  /* first find the normalizing distribution */
  for (j = start_col; j <= end_col; j++){
    non_na = 0;
    for (i =0; i < *rows; i++){
      if (ISNA(data[j*(*rows) + i])){
	
      } else {
	datvec[non_na] = data[j*(*rows) + i];
	non_na++;
      }
    }
    if (non_na == *rows){
      /* no NA values */
      qsort(datvec,*rows,sizeof(double),(int(*)(const void*, const void*))sort_double);
      for (i =0; i < *rows; i++){
#ifdef USE_PTHREADS
	row_submean[i] += datvec[i];
#else
	row_mean[i] += datvec[i]/((double)*cols);
#endif
      }
    } else {
      /* Use the observed data (non NA) values to estimate the distribution */
      /* Note that some of the variable names here might be a little confusing. Probably because I copied the code from below */
      qsort(datvec,non_na,sizeof(double),(int(*)(const void*, const void*))sort_double);
      for (i =0; i < *rows; i++){
	samplepercentile = (double)(i)/(double)(*rows-1);
	/* Rprintf("%f\n",samplepercentile); */
	/* row_mean_ind_double = 1.0/3.0 + ((double)(*rows) + 1.0/3.0) * samplepercentile; */
	row_mean_ind_double = 1.0 + ((double)(non_na) -1.0) * samplepercentile;
	
	row_mean_ind_double_floor = floor(row_mean_ind_double + 4*DOUBLE_EPS);
	
	row_mean_ind_double = row_mean_ind_double - row_mean_ind_double_floor;
	
	if (fabs(row_mean_ind_double) <=  4*DOUBLE_EPS){
	  row_mean_ind_double = 0.0;
	}
	
	
	if (row_mean_ind_double  == 0.0){
	  row_mean_ind = (int)floor(row_mean_ind_double_floor + 0.5);  /* (int)nearbyint(row_mean_ind_double_floor); */	
#ifdef USE_PTHREADS
	  row_submean[i]+= datvec[row_mean_ind-1];
#else
	  row_mean[i]+= datvec[row_mean_ind-1]/((double)*cols);
#endif
	} else if (row_mean_ind_double == 1.0){
	  row_mean_ind = (int)floor(row_mean_ind_double_floor + 1.5);  /* (int)nearbyint(row_mean_ind_double_floor + 1.0); */ 
#ifdef USE_PTHREADS
	  row_submean[i]+= datvec[row_mean_ind-1];
#else  
	  row_mean[i]+= datvec[row_mean_ind-1]/((double)*cols);
#endif
	} else {
	  row_mean_ind =  (int)floor(row_mean_ind_double_floor + 0.5); /* (int)nearbyint(row_mean_ind_double_floor); */
	  
	  if ((row_mean_ind < *rows) && (row_mean_ind > 0)){
#ifdef USE_PTHREADS
	    row_submean[i]+= ((1.0- row_mean_ind_double)*datvec[row_mean_ind-1] + row_mean_ind_double*datvec[row_mean_ind]);
#else
	    row_mean[i]+= ((1.0- row_mean_ind_double)*datvec[row_mean_ind-1] + row_mean_ind_double*datvec[row_mean_ind])/((double)*cols);
#endif
	  } else if (row_mean_ind >= *rows){
#ifdef USE_PTHREADS
	    row_submean[i]+= datvec[non_na-1];
#else
	    row_mean[i]+= datvec[non_na-1]/((double)*cols);
#endif
	  } else {
#ifdef USE_PTHREADS
	    row_submean[i]+=  datvec[0];
#else
	    row_mean[i]+=  datvec[0]/((double)*cols);
#endif
	  }
	}
      } 
    }
  }
#ifdef USE_PTHREADS
  /* add to the global running total, will do the division after all threads finish (for precision of the result) */
  pthread_mutex_lock (&mutex_R);
  for (i = 0; i < *rows; i++){
    row_mean[i] += (double) row_submean[i];
  }
  pthread_mutex_unlock (&mutex_R);
#endif  
  Free(datvec);
}



#ifdef USE_PTHREADS
void *determine_target_group(void *data){
  struct loop_data *args = (struct loop_data *) data;
  determine_target(args->data, args->row_mean, args->rows, args->cols, args->start_col, args->end_col);
}
#endif




int qnorm_c_determine_target(double *data, int *rows, int *cols, double *target, int *targetrows){


  int i,j,row_mean_ind;
  double *row_mean = (double *)Calloc((*rows),double);
  double row_mean_ind_double,row_mean_ind_double_floor;
  double samplepercentile;
  
  int non_na;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

#if defined(USE_PTHREADS)
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
  
  if (num_threads < *cols){
    chunk_size = *cols/num_threads;
    chunk_size_d = ((double) *cols)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((*cols < num_threads ? *cols : num_threads), struct loop_data);

  args[0].data = data;
  args[0].row_mean = row_mean;
  args[0].rows = rows;  
  args[0].cols = cols;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < *cols; i+=chunk_size){
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
    returnCode = pthread_create(&threads[i], &attr, determine_target_group, (void *) &(args[i]));
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

  /* When in threaded mode, row_mean is the sum, waiting for a final division here, to maintain precision */
  for (i = 0; i < *rows; i++){
    row_mean[i] /= (double)*cols;
  }
  pthread_attr_destroy(&attr);  
  pthread_mutex_destroy(&mutex_R);
  Free(threads);
  Free(args);  

#else
  normalize_determine_target(data,row_mean,rows,cols,0,*cols-1);
#endif
  
  if (*rows == *targetrows){
    for (i =0; i < *rows; i++){
      target[i] = row_mean[i];
    }
  } else {
    /* need to estimate quantiles */
    for (i =0; i < *targetrows; i++){
      samplepercentile = (double)(i)/(double)(*targetrows -1);
      
      /* row_mean_ind_double = 1.0/3.0 + ((double)(*rows) + 1.0/3.0) * samplepercentile; */
      row_mean_ind_double = 1.0 + ((double)(*rows) -1.0) * samplepercentile;

      row_mean_ind_double_floor = floor(row_mean_ind_double + 4*DOUBLE_EPS);
	
      row_mean_ind_double = row_mean_ind_double - row_mean_ind_double_floor;

      if (fabs(row_mean_ind_double) <=  4*DOUBLE_EPS){
	row_mean_ind_double = 0.0;
      }


      if (row_mean_ind_double  == 0.0){
	row_mean_ind = (int)floor(row_mean_ind_double_floor + 0.5);  /* (int)nearbyint(row_mean_ind_double_floor); */	
	target[i] = row_mean[row_mean_ind-1];
      } else if (row_mean_ind_double == 1.0){
	row_mean_ind = (int)floor(row_mean_ind_double_floor + 1.5);  /* (int)nearbyint(row_mean_ind_double_floor + 1.0); */ 
	target[i] = row_mean[row_mean_ind-1];
      } else {
	row_mean_ind =  (int)floor(row_mean_ind_double_floor + 0.5); /* (int)nearbyint(row_mean_ind_double_floor); */

	if ((row_mean_ind < *rows) && (row_mean_ind > 0)){
	  target[i] = (1.0- row_mean_ind_double)*row_mean[row_mean_ind-1] + row_mean_ind_double*row_mean[row_mean_ind];
	} else if (row_mean_ind >= *rows){
	  target[i] = row_mean[*rows-1];
	} else {
	  target[i] = row_mean[0];
	}
      }
    } 


  }

  Free(row_mean);
  return 0;
}




SEXP R_qnorm_using_target(SEXP X, SEXP target,SEXP copy){


  SEXP Xcopy,dim1; /*,dim2; */
  int rows, cols;
  int target_rows, target_cols;
  double *Xptr;
  double *targetptr;


  PROTECT(dim1 = getAttrib(X,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);
  if (asInteger(copy)){
    PROTECT(Xcopy = allocMatrix(REALSXP,rows,cols));
    copyMatrix(Xcopy,X,0);
  } else {
    Xcopy = X;
  }
  Xptr = NUMERIC_POINTER(AS_NUMERIC(Xcopy));

  if (isVector(target)){
    target_rows = length(target);
  } else if (isMatrix(target)){
    PROTECT(dim1 = getAttrib(X,R_DimSymbol));
    target_rows = INTEGER(dim1)[0];
    target_cols = INTEGER(dim1)[1];
    UNPROTECT(1);

    target_rows = target_rows*target_cols;
  } 

  
  targetptr = NUMERIC_POINTER(AS_NUMERIC(target));


  qnorm_c_using_target(Xptr, &rows, &cols,targetptr,&target_rows);

  if (asInteger(copy)){
    UNPROTECT(1);
  }
  return Xcopy;
}





SEXP R_qnorm_determine_target(SEXP X, SEXP targetlength){


  SEXP dim1,target;
  int rows, cols;
  int length;
  double *Xptr;
  double *targetptr;


  PROTECT(dim1 = getAttrib(X,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  length = asInteger(targetlength);

  /*  Rprintf("%d\n",length);*/

  PROTECT(target=allocVector(REALSXP,length));


  Xptr = NUMERIC_POINTER(AS_NUMERIC(X));
  targetptr = NUMERIC_POINTER(target);
    
  qnorm_c_determine_target(Xptr,&rows,&cols,targetptr, &length);


  UNPROTECT(1);
  return target;

}





/*********************************************************
 **
 ** void qnorm_c_handleNA(double *data, int *rows, int *cols)
 **
 **  this is the function that actually implements the
 ** quantile normalization algorithm. It is called from R.
 **
 ** returns 1 if there is a problem, 0 otherwise
 **
 ** Note that this function does not handle missing data (ie NA)
 **
 ********************************************************/


void qnorm_c_handleNA(double *data, int *rows, int *cols){

  double *target = Calloc(*rows,double);
    
  qnorm_c_determine_target(data, rows, cols, target, rows);
  qnorm_c_using_target(data, rows, cols, target, rows);

  Free(target);

}


/*********************************************************
 **
 ** SEXP R_qnorm_c_handleNA(SEXP X)
 **
 ** SEXP X      - a matrix
 ** SEXP copy   - a flag if TRUE then make copy
 **               before normalizing, if FALSE work in place
 **               note that this can be dangerous since
 **               it will change the original matrix.
 **
 ** returns a quantile normalized matrix.
 **
 ** This is a .Call() interface for quantile normalization
 **
 *********************************************************/

SEXP R_qnorm_c_handleNA(SEXP X, SEXP copy){

  SEXP Xcopy,dim1;
  double *Xptr;
  int rows,cols;
  
  PROTECT(dim1 = getAttrib(X,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  if (asInteger(copy)){
    PROTECT(Xcopy = allocMatrix(REALSXP,rows,cols));
    copyMatrix(Xcopy,X,0);
  } else {
    Xcopy = X;
  }
  Xptr = NUMERIC_POINTER(AS_NUMERIC(Xcopy));
  
  qnorm_c_handleNA(Xptr, &rows, &cols);
  if (asInteger(copy)){
    UNPROTECT(2);
  } else {
    UNPROTECT(1);
  }
  return Xcopy;
}



/*****************************************************************************************************
 *****************************************************************************************************
 **
 ** The following block of code implements quantile normalization within blocks.
 ** What this means is that the normalization is still carried out across arrrays (or columns)
 ** but separate subsets of rows (these are blocks) each get there own normalization
 **
 *****************************************************************************************************
 *****************************************************************************************************/


/*****************************************************************
 **
 ** int qnorm_c_within_blocks(double *x, int *rows, int *cols, int *blocks)
 ** 
 ** double *x - matrix to be normalized
 ** int *rows - dimensions of the matrix
 ** int *cols -
 ** int *blocks - labeling telling which block each row belongs to.
 **
 *****************************************************************/


int qnorm_c_within_blocks(double *x, int *rows, int *cols, int *blocks){


  int i,j,ind;
  dataitem_block **dimat_block;
  /*  double sum; */
  double *row_mean = (double *)Calloc((*rows),double);
  double *ranks = (double *)Calloc((*rows),double);
  

  dimat_block = (dataitem_block **)Calloc(1,dataitem_block *);
  dimat_block[0] = (dataitem_block *)Calloc(*rows,dataitem_block);
  
  for (i =0; i < *rows; i++){
    row_mean[i] = 0.0;
  }
  
  /* first find the normalizing distribution */
  for (j = 0; j < *cols; j++){
    for (i =0; i < *rows; i++){
      dimat_block[0][i].data = x[j*(*rows) + i];
      dimat_block[0][i].block = blocks[i];
    }
    qsort(dimat_block[0],*rows,sizeof(dataitem_block),sort_fn_blocks);
    /*   for (i=0; i < *rows; i++){
      Rprintf("%f %d\n",dimat_block[0][i].data,dimat_block[0][i].block);
      } */
    

    for (i =0; i < *rows; i++){
      row_mean[i] += dimat_block[0][i].data/((double)*cols);
    }
  }
  
  /* now assign back distribution */

  
  for (j = 0; j < *cols; j++){
    for (i =0; i < *rows; i++){
      dimat_block[0][i].data = x[j*(*rows) + i];
      dimat_block[0][i].block = blocks[i];
      dimat_block[0][i].rank = i;
    }
    qsort(dimat_block[0],*rows,sizeof(dataitem_block),sort_fn_blocks);
    get_ranks_blocks(ranks,dimat_block[0],*rows);
    for (i =0; i < *rows; i++){
      ind = dimat_block[0][i].rank;
      if (ranks[i] - floor(ranks[i]) > 0.4){
	x[j*(*rows) +ind] = 0.5*(row_mean[(int)floor(ranks[i])-1] + row_mean[(int)floor(ranks[i])]);
      } else { 
	x[j*(*rows) +ind] = row_mean[(int)floor(ranks[i])-1];
      }
    }
  }
  
  Free(ranks);
  
  Free(dimat_block[0]);
  
  Free(dimat_block);
  Free(row_mean);
  return 0;
  


}



SEXP R_qnorm_within_blocks(SEXP X,SEXP blocks,SEXP copy){

  SEXP Xcopy,dim1,blocksint;
  double *Xptr;
  int *blocksptr;
  int rows,cols;
  
  PROTECT(dim1 = getAttrib(X,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  if (asInteger(copy)){
    PROTECT(Xcopy = allocMatrix(REALSXP,rows,cols));
    copyMatrix(Xcopy,X,0);
  } else {
    Xcopy = X;
  }

  PROTECT(blocksint = coerceVector(blocks,INTSXP));
    

  Xptr = NUMERIC_POINTER(AS_NUMERIC(Xcopy));
  blocksptr  = INTEGER_POINTER(blocksint);


  
  qnorm_c_within_blocks(Xptr, &rows, &cols,blocksptr);
  if (asInteger(copy)){
    UNPROTECT(2);
  } else {
    UNPROTECT(1);
  }
  return Xcopy;



}


