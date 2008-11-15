#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#ifndef PREPROCESSCORE_NORMALIZATION_STUBS_H
#define PREPROCESSCORE_NORMALIZATION_STUBS_H 1

/*! \brief Quantile normalize the columns of a matrix
 *
 *  
 * @param data a matrix to be quantile normalized. On exit will be normalized
 * @param rows number of rows in the matrix
 * @param cols number of columns in the matrix
 *
 */

int qnorm_c(double *data, int *rows, int *cols){


  static int(*fun)(double*, int*, int*) = NULL;
  
  if (fun == NULL)
    fun =  (int(*)(double*, int*, int*))R_GetCCallable("preprocessCore","qnorm_c");
  
  return fun(data,rows,cols);

}



SEXP R_qnorm_robust_weights(SEXP X, SEXP remove_extreme, SEXP n_remove){

  
  static SEXP(*fun)(SEXP, SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP, SEXP))R_GetCCallable("preprocessCore","R_qnorm_robust_weights");
  
  return fun(X,remove_extreme,n_remove);
  
} 



int qnorm_robust_c(double *data,double *weights, int *rows, int *cols, int *use_median, int *use_log2, int *weight_scheme){

  
  static int(*fun)(double*, double *, int*, int*, int *, int *, int *) = NULL;
  
  if (fun == NULL)
    fun =  (int(*)(double*, double *, int*, int*, int *, int *, int *))R_GetCCallable("preprocessCore","qnorm_robust_c");
  
  return fun(data,weights,rows,cols,use_median,use_log2,weight_scheme);
  
} 



int qnorm_c_using_target(double *data, int *rows, int *cols, double *target, int *targetrows){

  static int(*fun)(double *, int *, int *, double *, int *) = NULL;

  
  if (fun == NULL)
    fun =  (int(*)(double *, int *, int *, double *, int *))R_GetCCallable("preprocessCore","qnorm_c_using_target");

  return fun(data,rows,cols,target,targetrows);

}


int qnorm_c_determine_target(double *data, int *rows, int *cols, double *target, int *targetrows){


  static int(*fun)(double *, int *, int *, double *, int *) = NULL;

  if (fun == NULL)
    fun = (int(*)(double *, int *, int *, double *, int *))R_GetCCallable("preprocessCore","qnorm_c_determine_target");

  return fun(data, rows, cols, target, targetrows);

}


int qnorm_c_within_blocks(double *x, int *rows, int *cols, int *blocks){

  
  static int(*fun)(double *, int *, int *, int *) = NULL;

  if (fun == NULL)
    fun = (int(*)(double *, int *, int *, int *))R_GetCCallable("preprocessCore","qnorm_c_within_blocks");


  return fun(x, rows, cols, blocks);
  
}






#endif
