#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#ifndef PREPROCESSCORE_BACKGROUND_STUBS_H
#define PREPROCESSCORE_BACKGROUND_STUBS_H 1


void rma_bg_parameters(double *PM,double *param, int rows, int cols, int column){

  static void(*fun)(double *, double *, int, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, double *, int, int, int))R_GetCCallable("preprocessCore","rma_bg_parameters");

  fun(PM, param, rows, cols, column);
  return;
}


void rma_bg_adjust(double *PM,double *param, int rows, int cols, int column){

  static void(*fun)(double *, double *, int, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, double *, int, int, int))R_GetCCallable("preprocessCore","rma_bg_adjust");

  fun(PM, param, rows, cols, column);
  return;
}


void rma_bg_correct(double *PM, int rows, int cols){

  static void(*fun)(double *, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int))R_GetCCallable("preprocessCore","rma_bg_correct");

  fun(PM, rows, cols);
  return;
}






#endif
