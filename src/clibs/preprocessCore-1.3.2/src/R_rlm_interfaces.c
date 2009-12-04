/*********************************************************************
 **
 ** file: R_rlm_interfaces.c
 **
 ** Aim: Code which provides .Call() interfaces to the rlm code.
 **
 ** Copyright (C) 2006-2007 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bmb@bmbolstad.com>
 ** 
 ** created on: Aug 16, 2006
 **
 ** History
 ** Aug 16, 2006 Initial version
 ** Nov 1, 2006 - add SE to output of function
 ** Sep 13, 2007 - Make the value of the constrained parameters something more sensible
 ** Sep 14, 2007 - Add medianpolish code interface (yes it is not really an rlm method, 
 **                but it is analogous enough in the format presented here)
 **
 **
 *********************************************************************/

#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>
#include "rlm.h"
#include "rlm_se.h"

#include "psi_fns.h"

#include "medianpolish.h"


#include "R_rlm_interfaces.h"



/**********************************************************************************
 **
 ** SEXP R_rlm_rma_default_model(SEXP Y, SEXP PsiCode, SEXP transform)
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





SEXP R_rlm_rma_default_model(SEXP Y, SEXP PsiCode, SEXP PsiK){


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
  
  
  

  
  rlm_fit_anova(Ymat, rows, cols, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);
  
  rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)NULL, &residSE, 4, PsiFunc(asInteger(PsiCode)),asReal(PsiK));


  

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











SEXP R_wrlm_rma_default_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Weights){


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
  

  
  rlm_wfit_anova(Ymat, rows, cols, w, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);
  rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)NULL, &residSE, 4, PsiFunc(asInteger(PsiCode)),asReal(PsiK));


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



















SEXP R_medianpolish_rma_default_model(SEXP Y){



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

  double intercept;

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
  /* PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));*/
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  /*  PROTECT(R_SE = allocVector(REALSXP,rows+cols)); */

  R_weights = R_NilValue;
  R_SE = R_NilValue;


  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(2);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  /*  weights = NUMERIC_POINTER(R_weights);
      se = NUMERIC_POINTER(R_SE);
  */

  Ymat = NUMERIC_POINTER(Y);

  for (i=0; i < rows*cols; i++){
    residuals[i] = Ymat[i];
  }

  memset(beta, 0, (rows+cols)*sizeof(double));

  
  
  median_polish_fit_no_copy(residuals, rows, cols, &beta[cols], &beta[0], &intercept);

  for (i=0; i < cols; i++)
    beta[i]+=intercept;




  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;









}
















SEXP R_rlm_rma_given_probe_effects(SEXP Y, SEXP probe_effects, SEXP PsiCode, SEXP PsiK){


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

  double *probeeffects;
  
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
  PROTECT(R_beta = allocVector(REALSXP, cols));
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_SE = allocVector(REALSXP,cols));

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(4);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  se = NUMERIC_POINTER(R_SE);

  probeeffects = NUMERIC_POINTER(probe_effects);


  Ymat = NUMERIC_POINTER(Y);
  
  
  

  
  rlm_fit_anova_given_probe_effects(Ymat, rows, cols, probeeffects, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);
  
  rlm_compute_se_anova_given_probe_effects(Ymat, rows, cols, probeeffects, beta, residuals, weights,se, (double *)NULL, &residSE, 4, PsiFunc(asInteger(PsiCode)),asReal(PsiK));


  
  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}





SEXP R_wrlm_rma_given_probe_effects(SEXP Y, SEXP probe_effects, SEXP PsiCode, SEXP PsiK, SEXP Weights){


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

  double *w;

  double *probeeffects;
  
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
  PROTECT(R_beta = allocVector(REALSXP, cols));
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_SE = allocVector(REALSXP,cols));

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,3,R_SE);

  UNPROTECT(4);

  beta = NUMERIC_POINTER(R_beta);
  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  se = NUMERIC_POINTER(R_SE);

  probeeffects = NUMERIC_POINTER(probe_effects);


  Ymat = NUMERIC_POINTER(Y);
  
   
  w = NUMERIC_POINTER(Weights);
  
  

  
  rlm_wfit_anova_given_probe_effects(Ymat, rows, cols, probeeffects, w, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20, 0);
  
  rlm_compute_se_anova_given_probe_effects(Ymat, rows, cols, probeeffects, beta, residuals, weights,se, (double *)NULL, &residSE, 4, PsiFunc(asInteger(PsiCode)),asReal(PsiK));


  
  PROTECT(R_return_value_names= allocVector(STRSXP,4));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}

