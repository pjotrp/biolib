#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP R_subColSummarize_avg_log(SEXP RMatrix, SEXP R_rowIndexList){

  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_avg_log");
  
  return fun(RMatrix, R_rowIndexList);
}



SEXP R_subColSummarize_log_avg(SEXP RMatrix, SEXP R_rowIndexList){
  
  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_log_avg");
  
  return fun(RMatrix, R_rowIndexList);
}









SEXP R_subColSummarize_avg(SEXP RMatrix, SEXP R_rowIndexList){

  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_avg");
  
  return fun(RMatrix, R_rowIndexList);
}








SEXP R_subColSummarize_biweight_log(SEXP RMatrix, SEXP R_rowIndexList){
  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_biweight_log");
  
  return fun(RMatrix, R_rowIndexList);
}





SEXP R_subColSummarize_biweight(SEXP RMatrix, SEXP R_rowIndexList){
  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_biweight");
  
  return fun(RMatrix, R_rowIndexList);
}



SEXP R_subColSummarize_median_log(SEXP RMatrix, SEXP R_rowIndexList){
  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_median_log");
  
  return fun(RMatrix, R_rowIndexList);
}






SEXP R_subColSummarize_log_median(SEXP RMatrix, SEXP R_rowIndexList){
  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_log_median");
  
  return fun(RMatrix, R_rowIndexList);
}


SEXP R_subColSummarize_median(SEXP RMatrix, SEXP R_rowIndexList){
  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_median");
  
  return fun(RMatrix, R_rowIndexList);
}


SEXP R_subColSummarize_medianpolish_log(SEXP RMatrix, SEXP R_rowIndexList){
  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_medianpolish_log");
  
  return fun(RMatrix, R_rowIndexList);
}



SEXP R_subColSummarize_medianpolish(SEXP RMatrix, SEXP R_rowIndexList){
  static SEXP(*fun)(SEXP, SEXP) = NULL;
  
  if (fun == NULL)
    fun =  (SEXP(*)(SEXP, SEXP))R_GetCCallable("preprocessCore","R_subColSummarize_medianpolish");
  
  return fun(RMatrix, R_rowIndexList);
}

