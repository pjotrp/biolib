/*********************************************************************
 **
 ** file: R_colSummarize.c
 **
 ** Aim: Code which provides .Call() interfaces to the column 
 ** summarization code.
 **
 ** Copyright (C) 2007 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bmb@bmbolstad.com>
 ** 
 ** created on: Sep 15, 2007
 **
 ** History
 ** Sep 15, 2007 - Initial version
 **
 **
 *********************************************************************/



#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include "R_colSummarize.h"

#include "avg_log.h"
#include "log_avg.h"
#include "avg.h"

#include "log_median.h"
#include "median_log.h"
#include "median.h"

#include "biweight.h"
#include "medianpolish.h"

SEXP R_colSummarize_avg_log(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  averagelog(matrix, rows, cols, results, resultsSE);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}





SEXP R_colSummarize_log_avg(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  logaverage(matrix, rows, cols, results, resultsSE);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}




SEXP R_colSummarize_avg(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  colaverage(matrix, rows, cols, results, resultsSE);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}



















SEXP R_colSummarize_log_median(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  logmedian(matrix, rows, cols, results, resultsSE);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}



SEXP R_colSummarize_median_log(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  medianlog(matrix, rows, cols, results, resultsSE);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}




SEXP R_colSummarize_median(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  colmedian(matrix, rows, cols, results, resultsSE);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}




SEXP R_colSummarize_biweight_log(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  tukeybiweight(matrix, rows, cols, results, resultsSE);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}


SEXP R_colSummarize_biweight(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  tukeybiweight_no_log(matrix, rows, cols, results, resultsSE);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}










SEXP R_colSummarize_medianpolish_log(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  double *resids;

  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  resids = Calloc(rows*cols, double);
  
  memcpy(resids, matrix, rows*cols*sizeof(double));
  
  median_polish_log2_no_copy(resids, rows, cols, results, resultsSE);
  
  Free(resids);
  

  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}




SEXP R_colSummarize_medianpolish(SEXP RMatrix){


  SEXP R_return_value;
  SEXP R_return_value_names;

  SEXP R_summaries;
  SEXP R_summaries_se;

  
  SEXP dim1;

  double *matrix=NUMERIC_POINTER(RMatrix);
  double *results, *resultsSE;
  
  double *resids;

  
  int rows, cols;

  PROTECT(dim1 = getAttrib(RMatrix,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);


  PROTECT(R_return_value = allocVector(VECSXP,2));
  PROTECT(R_summaries = allocVector(REALSXP,cols));
  PROTECT(R_summaries_se = allocVector(REALSXP,cols));
  SET_VECTOR_ELT(R_return_value,0,R_summaries);
  SET_VECTOR_ELT(R_return_value,1,R_summaries_se);
  

  results = NUMERIC_POINTER(R_summaries);
  resultsSE = NUMERIC_POINTER(R_summaries_se);

  resids = Calloc(rows*cols, double);
  
  memcpy(resids, matrix, rows*cols*sizeof(double));
  
  median_polish_no_copy(resids, rows, cols, results, resultsSE);
  
  Free(resids);
  

  PROTECT(R_return_value_names= allocVector(STRSXP,2));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(1);

  UNPROTECT(3);
  return R_return_value;
}
