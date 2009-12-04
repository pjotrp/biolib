/*********************************************************************
 **
 ** file: R_plmr_interfaces.c
 **
 ** Aim: Code which provides .Call() interfaces to the PLM-r code.
 **
 ** Copyright (C) 2008 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bmb@bmbolstad.com>
 ** 
 ** created on: Jan 28, 2008
 **
 ** History
 ** Jan 28, 2008 - Initial version
 **
 **
 *********************************************************************/
#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include "plmr.h"
#include "rlm_se.h"

#include "psi_fns.h"
#include "R_plmr_interfaces.h"


/**********************************************************************************
 **
 ** SEXP R_plmr_model(SEXP Y, SEXP PsiCode, SEXP transform)
 **
 ** 
 ** SEXP Y - A matrix with probes in rows and arrays in columns
 ** SEXP PsiCode - An integer code corresponding to the function that should be used to determine
 **                how outliers are down weighted.
 ** SEXP PsiK - a parameter for weighting algorithm.
 **
 ** Returns 
 ** parameter estimates. weights, residuals, Standard error estimates
 **
 *********************************************************************/

SEXP R_plmr_model(SEXP Y, SEXP PsiCode, SEXP PsiK){


  SEXP R_return_value;
  SEXP R_weights;
  SEXP R_residuals;
  SEXP R_beta;
  SEXP R_SE;
  
  SEXP R_return_value_names;

  SEXP dim1;

  double *beta;
  double *residuals;
  double *weights;
  double *se;

  double residSE;

  double *Ymat;

  int rows;
  int cols;

  int i;
  
  PROTECT(dim1 = getAttrib(Y,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_return_value = allocVector(VECSXP,4));
  PROTECT(R_beta = allocVector(REALSXP, rows + cols));
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_SE = allocVector(REALSXP,rows+cols));

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(4);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  se = NUMERIC_POINTER(R_SE);

  Ymat = NUMERIC_POINTER(Y);
  
  
  

  plmr_fit(Ymat, rows, cols, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);
  
  /* Note use 2 rather than 4  for SE method */
  rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)NULL, &residSE, 2, PsiFunc(asInteger(PsiCode)),asReal(PsiK));

  beta[rows+cols -1] = 0.0;
  se[rows+cols -1] = 0.0;


  for (i = cols; i < rows + cols -1; i++)
    beta[rows+cols -1]-=beta[i];


  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}



/**********************************************************************************
 **
 ** SEXP R_plmrr_model(SEXP Y, SEXP PsiCode, SEXP transform)
 **
 ** 
 ** SEXP Y - A matrix with probes in rows and arrays in columns
 ** SEXP PsiCode - An integer code corresponding to the function that should be used to determine
 **                how outliers are down weighted.
 ** SEXP PsiK - a parameter for weighting algorithm.
 **
 ** Returns 
 ** parameter estimates. weights, residuals, Standard error estimates
 **
 *********************************************************************/

SEXP R_plmrr_model(SEXP Y, SEXP PsiCode, SEXP PsiK){


  SEXP R_return_value;
  SEXP R_weights;
  SEXP R_residuals;
  SEXP R_beta;
  SEXP R_SE;
  
  SEXP R_return_value_names;

  SEXP dim1;

  double *beta;
  double *residuals;
  double *weights;
  double *se;

  double residSE;

  double *Ymat;

  int rows;
  int cols;

  int i;
  
  PROTECT(dim1 = getAttrib(Y,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_return_value = allocVector(VECSXP,4));
  PROTECT(R_beta = allocVector(REALSXP, rows + cols));
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_SE = allocVector(REALSXP,rows+cols));

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(4);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  se = NUMERIC_POINTER(R_SE);

  Ymat = NUMERIC_POINTER(Y);
  
  
  

  plmrr_fit(Ymat, rows, cols, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);
  
  /* Note use 2 rather than 4  for SE method */
  rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)NULL, &residSE, 2, PsiFunc(asInteger(PsiCode)),asReal(PsiK));

  beta[rows+cols -1] = 0.0;
  se[rows+cols -1] = 0.0;


  for (i = cols; i < rows + cols -1; i++)
    beta[rows+cols -1]-=beta[i];


  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}

/**********************************************************************************
 **
 ** SEXP R_plmrc_model(SEXP Y, SEXP PsiCode, SEXP transform)
 **
 ** 
 ** SEXP Y - A matrix with probes in rows and arrays in columns
 ** SEXP PsiCode - An integer code corresponding to the function that should be used to determine
 **                how outliers are down weighted.
 ** SEXP PsiK - a parameter for weighting algorithm.
 **
 ** Returns 
 ** parameter estimates. weights, residuals, Standard error estimates
 **
 *********************************************************************/

SEXP R_plmrc_model(SEXP Y, SEXP PsiCode, SEXP PsiK){


  SEXP R_return_value;
  SEXP R_weights;
  SEXP R_residuals;
  SEXP R_beta;
  SEXP R_SE;
  
  SEXP R_return_value_names;

  SEXP dim1;

  double *beta;
  double *residuals;
  double *weights;
  double *se;

  double residSE;

  double *Ymat;

  int rows;
  int cols;

  int i;
  
  PROTECT(dim1 = getAttrib(Y,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_return_value = allocVector(VECSXP,4));
  PROTECT(R_beta = allocVector(REALSXP, rows + cols));
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_SE = allocVector(REALSXP,rows+cols));

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(4);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  se = NUMERIC_POINTER(R_SE);

  Ymat = NUMERIC_POINTER(Y);
  
  
  

  plmrc_fit(Ymat, rows, cols, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);
  
  /* Note use 2 rather than 4  for SE method */
  rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)NULL, &residSE, 2, PsiFunc(asInteger(PsiCode)),asReal(PsiK));

  beta[rows+cols -1] = 0.0;
  se[rows+cols -1] = 0.0;


  for (i = cols; i < rows + cols -1; i++)
    beta[rows+cols -1]-=beta[i];


  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}


SEXP R_wplmr_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Weights){


  SEXP R_return_value;
  SEXP R_weights;
  SEXP R_residuals;
  SEXP R_beta;
  SEXP R_SE;
  
  SEXP R_return_value_names;

  SEXP dim1;

  double *beta;
  double *residuals;
  double *weights;
  double *se;

  double residSE;

  double *Ymat;
  double *w;

  int rows;
  int cols;

  int i;
  
  PROTECT(dim1 = getAttrib(Y,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_return_value = allocVector(VECSXP,4));
  PROTECT(R_beta = allocVector(REALSXP, rows + cols));
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_SE = allocVector(REALSXP,rows+cols));

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(4);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  se = NUMERIC_POINTER(R_SE);

  Ymat = NUMERIC_POINTER(Y);
  
  w = NUMERIC_POINTER(Weights);
  

  
  plmr_wfit(Ymat, rows, cols, w, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);


  /* Note use 2 is 4 for std PLM */
  rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)NULL, &residSE, 2, PsiFunc(asInteger(PsiCode)),asReal(PsiK));


  beta[rows+cols -1] = 0.0;
  se[rows+cols -1] = 0.0;

  for (i = cols; i < rows + cols -1; i++)
    beta[rows+cols -1]-=beta[i];


  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}




SEXP R_wplmrr_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Weights){


  SEXP R_return_value;
  SEXP R_weights;
  SEXP R_residuals;
  SEXP R_beta;
  SEXP R_SE;
  
  SEXP R_return_value_names;

  SEXP dim1;

  double *beta;
  double *residuals;
  double *weights;
  double *se;

  double residSE;

  double *Ymat;
  double *w;

  int rows;
  int cols;

  int i;
  
  PROTECT(dim1 = getAttrib(Y,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_return_value = allocVector(VECSXP,4));
  PROTECT(R_beta = allocVector(REALSXP, rows + cols));
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_SE = allocVector(REALSXP,rows+cols));

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(4);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  se = NUMERIC_POINTER(R_SE);

  Ymat = NUMERIC_POINTER(Y);
  
  w = NUMERIC_POINTER(Weights);
  

  
  plmrr_wfit(Ymat, rows, cols, w, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);


  /* Note use 2 is 4 for std PLM */
  rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)NULL, &residSE, 2, PsiFunc(asInteger(PsiCode)),asReal(PsiK));


  beta[rows+cols -1] = 0.0;
  se[rows+cols -1] = 0.0;

  for (i = cols; i < rows + cols -1; i++)
    beta[rows+cols -1]-=beta[i];


  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}





SEXP R_wplmrc_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Weights){


  SEXP R_return_value;
  SEXP R_weights;
  SEXP R_residuals;
  SEXP R_beta;
  SEXP R_SE;
  
  SEXP R_return_value_names;

  SEXP dim1;

  double *beta;
  double *residuals;
  double *weights;
  double *se;

  double residSE;

  double *Ymat;
  double *w;

  int rows;
  int cols;

  int i;
  
  PROTECT(dim1 = getAttrib(Y,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_return_value = allocVector(VECSXP,4));
  PROTECT(R_beta = allocVector(REALSXP, rows + cols));
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_SE = allocVector(REALSXP,rows+cols));

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(4);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  se = NUMERIC_POINTER(R_SE);

  Ymat = NUMERIC_POINTER(Y);
  
  w = NUMERIC_POINTER(Weights);
  

  
  plmrc_wfit(Ymat, rows, cols, w, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);


  /* Note use 2 is 4 for std PLM */
  rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)NULL, &residSE, 2, PsiFunc(asInteger(PsiCode)),asReal(PsiK));


  beta[rows+cols -1] = 0.0;
  se[rows+cols -1] = 0.0;

  for (i = cols; i < rows + cols -1; i++)
    beta[rows+cols -1]-=beta[i];


  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}
