/*********************************************************************
 **
 ** file: R_subColSummarize.c
 **
 ** Aim: Code which provides .Call() interfaces to the subcolumn 
 ** summarization code.
 **
 ** Copyright (C) 2007 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bmb@bmbolstad.com>
 ** 
 ** created on: Sep 15, 2007
 **
 ** History
 ** Sep 18, 2007 - Initial version
 ** Mar 24, 2008 - Add multi-threaded implementation based on pthreads
 **                for each R_subColSummarize_*
 **
 **
 *********************************************************************/

#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>


#include "avg_log.h"
#include "log_avg.h"
#include "avg.h"

#include "biweight.h"

#include "median_log.h"
#include "log_median.h"
#include "median.h"

#include "medianpolish.h"

#ifdef USE_PTHREADS
#include <pthread.h>
#define THREADS_ENV_VAR "R_THREADS"
pthread_mutex_t mutex_R;
struct loop_data{
  double *matrix;
  double *results;
  SEXP *R_rowIndexList;
  int rows;
  int cols;
  int length_rowIndexList;
  int start_row;
  int end_row;
};
#endif


#ifdef USE_PTHREADS

static void *subColSummarize_avg_log_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);

  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    AverageLog_noSE(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);

}

#endif




SEXP R_subColSummarize_avg_log(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
  results = NUMERIC_POINTER(R_summaries);
 
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_avg_log_group, (void *) &(args[i]));
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
 
  buffer = Calloc(cols,double);
  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    AverageLog_noSE(matrix, rows, cols, cur_rows, buffer, ncur_rows);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}


#ifdef USE_PTHREADS

static void *subColSummarize_log_avg_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);

  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    LogAverage_noSE(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);

}
#endif


SEXP R_subColSummarize_log_avg(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_log_avg_group, (void *) &(args[i]));
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
 
  buffer = Calloc(cols,double);

  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    LogAverage_noSE(matrix, rows, cols, cur_rows, buffer, ncur_rows);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}


#ifdef USE_PTHREADS

static void *subColSummarize_avg_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);

  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    ColAverage_noSE(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);

}
#endif


SEXP R_subColSummarize_avg(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_avg_group, (void *) &(args[i]));
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
  buffer = Calloc(cols,double);

  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    ColAverage_noSE(matrix, rows, cols, cur_rows, buffer, ncur_rows);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}


#ifdef USE_PTHREADS

static void *subColSummarize_biweight_log_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);

  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    TukeyBiweight_noSE(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);

}
#endif




SEXP R_subColSummarize_biweight_log(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif


  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_biweight_log_group, (void *) &(args[i]));
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
  buffer = Calloc(cols,double);

  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    TukeyBiweight_noSE(matrix, rows, cols, cur_rows, buffer, ncur_rows);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}


#ifdef USE_PTHREADS

static void *subColSummarize_biweight_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);

  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    TukeyBiweight_no_log_noSE(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);

}
#endif



SEXP R_subColSummarize_biweight(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_biweight_group, (void *) &(args[i]));
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
 
  buffer = Calloc(cols,double);

  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    TukeyBiweight_no_log_noSE(matrix, rows, cols, cur_rows, buffer, ncur_rows);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}


#ifdef  USE_PTHREADS
static void *subColSummarize_median_log_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);

  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    MedianLog_noSE(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);

}
#endif




SEXP R_subColSummarize_median_log(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_median_log_group, (void *) &(args[i]));
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
  buffer = Calloc(cols,double);

  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    MedianLog_noSE(matrix, rows, cols, cur_rows, buffer, ncur_rows);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}


#ifdef  USE_PTHREADS
static void *subColSummarize_log_median_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);

  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    LogMedian_noSE(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);

}
#endif



SEXP R_subColSummarize_log_median(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_log_median_group, (void *) &(args[i]));
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
  buffer = Calloc(cols,double);

  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    LogMedian_noSE(matrix, rows, cols, cur_rows, buffer, ncur_rows);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}


#ifdef  USE_PTHREADS
static void *subColSummarize_median_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);

  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    ColMedian_noSE(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);

}
#endif


SEXP R_subColSummarize_median(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_median_group, (void *) &(args[i]));
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
  buffer = Calloc(cols,double);

  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    ColMedian_noSE(matrix, rows, cols, cur_rows, buffer, ncur_rows);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}



#ifdef  USE_PTHREADS
static void *subColSummarize_medianpolish_log_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer, *buffer2;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);
  buffer2 = Calloc(args->cols,double);

 
  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    MedianPolish(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows, buffer2);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);
  Free(buffer2);
}
#endif



SEXP R_subColSummarize_medianpolish_log(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer, *buffer2;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif


  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
 
  buffer = Calloc(cols,double);
  buffer2 = Calloc(cols,double);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_medianpolish_log_group, (void *) &(args[i]));
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
  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    MedianPolish(matrix, rows, cols, cur_rows, buffer, ncur_rows, buffer2);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  Free(buffer2);
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}


#ifdef  USE_PTHREADS
static void *subColSummarize_medianpolish_group(void *data){
  
  struct loop_data *args = (struct loop_data *) data;
  int *cur_rows;
  double *buffer, *buffer2;
  int i, j;
  int ncur_rows;
  
  buffer = Calloc(args->cols,double);
  buffer2 = Calloc(args->cols,double);

 
  for (j = args->start_row; j <= args->end_row;  j++){    
    ncur_rows = LENGTH(VECTOR_ELT(*(args->R_rowIndexList),j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(*(args->R_rowIndexList),j));
    MedianPolish_no_log(args->matrix, args->rows, args->cols, cur_rows, buffer, ncur_rows, buffer2);
    pthread_mutex_lock (&mutex_R);
    for (i = 0; i < args->cols; i++){
      args->results[i*args->length_rowIndexList + j] = buffer[i];
    }
    pthread_mutex_unlock (&mutex_R);
  }
  Free(buffer);
  Free(buffer2);
}
#endif



SEXP R_subColSummarize_medianpolish(SEXP RMatrix, SEXP R_rowIndexList){

  SEXP R_summaries;  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *buffer, *buffer2;
  
  int *cur_rows;

  int rows, cols;
  int length_rowIndexList = LENGTH(R_rowIndexList);
  int ncur_rows;

  int i,j;
#ifdef USE_PTHREADS
  int t, returnCode, chunk_size, num_threads = 1;
  double chunk_size_d, chunk_tot_d;
  char *nthreads;
  pthread_attr_t attr;
  pthread_t *threads;
  struct loop_data *args;
  void *status;
#endif

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_summaries = allocMatrix(REALSXP,length_rowIndexList,cols));
 
  results = NUMERIC_POINTER(R_summaries);
#ifdef  USE_PTHREADS
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

  /* this code works out how many threads to use and allocates ranges of subColumns to each thread */
  /* The aim is to try to be as fair as possible in dividing up the matrix */
  /* A special cases to be aware of: 
     1) Number of subColumns is less than the number of threads
  */
  
  if (num_threads < length_rowIndexList){
    chunk_size = length_rowIndexList/num_threads;
    chunk_size_d = ((double) length_rowIndexList)/((double) num_threads);
  } else {
    chunk_size = 1;
    chunk_size_d = 1;
  }

  if(chunk_size == 0){
    chunk_size = 1;
  }
  args = (struct loop_data *) Calloc((length_rowIndexList < num_threads ? length_rowIndexList : num_threads), struct loop_data);

  args[0].matrix = matrix;
  args[0].results = results;
  args[0].R_rowIndexList = &R_rowIndexList;
  args[0].rows = rows;  
  args[0].cols = cols;
  args[0].length_rowIndexList = length_rowIndexList;

  pthread_mutex_init(&mutex_R, NULL);

  t = 0; /* t = number of actual threads doing work */
  chunk_tot_d = 0;
  for (i=0; floor(chunk_tot_d+0.00001) < length_rowIndexList; i+=chunk_size){
     if(t != 0){
       memcpy(&(args[t]), &(args[0]), sizeof(struct loop_data));
     }

     args[t].start_row = i;     
     /* take care of distribution of the remainder (when #chips%#threads != 0) */
     chunk_tot_d += chunk_size_d;
     // Add 0.00001 in case there was a rounding issue with the division
     if(i+chunk_size < floor(chunk_tot_d+0.00001)){
       args[t].end_row = i+chunk_size;
       i++;
     }
     else{
       args[t].end_row = i+chunk_size-1;
     }
     t++;
  }

  
  for (i =0; i < t; i++){
     returnCode = pthread_create(&threads[i], &attr, subColSummarize_median_group, (void *) &(args[i]));
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
  buffer = Calloc(cols,double);
  buffer2 = Calloc(cols,double);

  for (j =0; j < length_rowIndexList; j++){    
    ncur_rows = LENGTH(VECTOR_ELT(R_rowIndexList,j)); 
    cur_rows = INTEGER_POINTER(VECTOR_ELT(R_rowIndexList,j));
    MedianPolish_no_log(matrix, rows, cols, cur_rows, buffer, ncur_rows, buffer2);
    
    for (i = 0; i < cols; i++){
      results[i*length_rowIndexList + j] = buffer[i];
    }
  }
  Free(buffer2);
  Free(buffer);
#endif
  UNPROTECT(1);
  return R_summaries;
}
