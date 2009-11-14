/*********************************************************************
 **
 ** file: R_plmr_interfaces.c
 **
 ** Aim: Code which provides .Call() interfaces to the PLM-d code.
 **
 ** Copyright (C) 2008 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bmb@bmbolstad.com>
 ** 
 ** created on: Jan 30, 2008
 **
 ** History
 ** Jan 30, 2008 - Initial version
 **
 **
 *********************************************************************/
 
#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include "plmd.h"
#include "rlm_se.h"

#include "psi_fns.h"

/*******************************************************************************
***
 **
 ** SEXP R_plmd_model(SEXP Y, SEXP PsiCode, SEXP transform)
 **
 ** 
 ** SEXP Y - A matrix with probes in rows and arrays in columns
 ** SEXP PsiCode - An integer code corresponding to the function that should be 
used to determine
 **                how outliers are down weighted.
 ** SEXP PsiK - a parameter for weighting algorithm.
 **
 ** Returns 
 ** parameter estimates. weights, residuals, Standard error estimates, whether split
 **
 *********************************************************************/



SEXP R_plmd_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Groups, SEXP Ngroups){


  SEXP R_return_value;
  SEXP R_weights;
  SEXP R_residuals;
  SEXP R_beta;
  SEXP R_SE;
  SEXP R_was_split;
  
  SEXP R_return_value_names;

  SEXP dim1;

  double *beta;
  double *residuals;
  double *weights;
  double *se;
  
  int *was_split;
  int *groups;

  double residSE;

  double *Ymat;

  double *X; /* Needed for SE */
  int X_cols, X_rows;


  int rows;
  int cols;

  int ngroups;
  
  int howmany_split =0;

  int i;
  
  PROTECT(dim1 = getAttrib(Y,R_DimSymbol));
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1];
  UNPROTECT(1);

  PROTECT(R_return_value = allocVector(VECSXP,5));
  
  /*
    Don't allocate R_beta/R_SE straight away, we won't know how much space
    these will actually need until finishing the PLM-d fitting procedure. 
    Instead we will just allocate those for which we currently know the size
  */
  
  
  PROTECT(R_weights = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_residuals = allocMatrix(REALSXP,rows,cols));
  PROTECT(R_was_split = allocVector(INTSXP,rows));

  
  /* 0 - beta   (added below)
     1 - weights
     2 - residuals
     3 - standard errors  (added below)
     4 - R_was_split
  */
  SET_VECTOR_ELT(R_return_value,1,R_weights);
  SET_VECTOR_ELT(R_return_value,2,R_residuals);
  SET_VECTOR_ELT(R_return_value,4,R_was_split);



  UNPROTECT(3);

  residuals = NUMERIC_POINTER(R_residuals);
  weights = NUMERIC_POINTER(R_weights);
  was_split = INTEGER_POINTER(R_was_split);
  
  groups = INTEGER_POINTER(Groups);

  ngroups = INTEGER(Ngroups)[0];

  Ymat = NUMERIC_POINTER(Y);
  
  beta = Calloc(cols + rows*ngroups -1, double);   
  se = Calloc(cols + rows*ngroups -1, double);

  plmd_fit(Ymat, rows, cols, ngroups, groups, was_split, beta, residuals, weights, PsiFunc(asInteger(PsiCode)),asReal(PsiK), 20);


  for (i = 0; i < rows; i++){
    howmany_split+=was_split[i];
  }
  
  if (howmany_split > 0){
    PROTECT(R_beta = allocVector(REALSXP,rows + cols + howmany_split*(ngroups-1)));
    PROTECT(R_SE = allocVector(REALSXP,rows + cols + howmany_split*(ngroups-1)));
    
    X = plmd_get_design_matrix(rows, cols, ngroups, groups,was_split,&X_rows,&X_cols);


    rlm_compute_se(X,Ymat, X_rows, X_cols, beta, residuals, weights, se,(double *)NULL, &residSE, 2, PsiFunc(asInteger(PsiCode)),asReal(PsiK));
    Free(X);


    for (i = cols; i <  rows + cols + howmany_split*(ngroups-1) - 1; i++)
      beta[rows + cols + howmany_split*(ngroups-1) -1]-=beta[i];
    
    for (i = 0; i < rows + cols + howmany_split*(ngroups-1) ; i++){
      NUMERIC_POINTER(R_beta)[i] = beta[i];
      NUMERIC_POINTER(R_SE)[i] = se[i];
    }


  } else {
    /* Note use 2 rather than 4  for SE method */
    rlm_compute_se_anova(Ymat, rows, cols, beta, residuals, weights,se, (double *)
			 NULL, &residSE, 2, PsiFunc(asInteger(PsiCode)),asReal(PsiK));

    beta[rows+cols -1] = 0.0;
    se[rows+cols -1] = 0.0;


    for (i = cols; i < rows + cols -1; i++)
      beta[rows+cols -1]-=beta[i];
    
    PROTECT(R_beta = allocVector(REALSXP,rows+cols));
    PROTECT(R_SE = allocVector(REALSXP,rows+cols));
    
    for (i = 0; i < rows + cols; i++){
      NUMERIC_POINTER(R_beta)[i] = beta[i];
      NUMERIC_POINTER(R_SE)[i] = se[i];
    }


  }

  Free(beta);
  Free(se);

  SET_VECTOR_ELT(R_return_value,0,R_beta);
  SET_VECTOR_ELT(R_return_value,3,R_SE);
  UNPROTECT(2);
  
  PROTECT(R_return_value_names= allocVector(STRSXP,5));
  SET_VECTOR_ELT(R_return_value_names,0,mkChar("Estimates"));
  SET_VECTOR_ELT(R_return_value_names,1,mkChar("Weights"));
  SET_VECTOR_ELT(R_return_value_names,2,mkChar("Residuals"));
  SET_VECTOR_ELT(R_return_value_names,3,mkChar("StdErrors"));
  SET_VECTOR_ELT(R_return_value_names,4,mkChar("WasSplit"));
  setAttrib(R_return_value, R_NamesSymbol,R_return_value_names);
  UNPROTECT(2);
  return R_return_value;

}



