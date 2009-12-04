/*********************************************************************
 **
 ** file: lm.c
 **
 ** Aim: implement linear models.
 **
 ** Copyright (C) 2003 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bolstad@stat.berkeley.edu>
 ** 
 ** created on: Jun 05, 2003
 **
 ** Last modified: Jun 05, 2003
 **
 ** The aim will be to provide a functions for fitting linear models.
 **
 **
 ** History
 **
 ** Jun 05, 2003 - Moved lm_wfit from rlm.c to this file lm.c
 **                modify lm_wfit to handle cases where weight is 0.
 **                otherwise bad things will happen when using a psi_fn that 
 **                gives weights of 0.
 ** Jul 27, 2003 - better handling of cases where a parameter
 **                is not estimable (set it to NA)
 ** Sep 14, 2003 - fix a bug where k was where a j should be in a for loop
 ** Mar 1, 2006 - change all comments to ansi style
 ** May 19, 2007 - branch out of affyPLM into a new package preprocessCore, then restructure the code. Add doxygen style documentation
 **
 ********************************************************************/

#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>
#include "dqrls.h"
#include "lm.h"

/*************************************************************************
 **
 ** void lm_wfit(double *x, double *y, double *w, int rows, int cols, double tol, double *outbeta, double *outresid)
 ** 
 ** double *x - coefficient matrix: dimension rows*cols
 ** double *y - dependent variable: length rows
 ** double *w - weights for each observation: length rows
 ** int rows, cols - dimension of input
 ** double tol - machine tolerance used in qr decomp
 ** double *outbeta - place to output beta estimates: lenght cols
 ** double *outresid - place to output residuals: length rows
 **
 ** This function computes weighted linear regression estimates using QR decomposition
 ** Note that a linpack routine is used to do the actual fit.
 **
 ** For now we will assume that singularities will not exist when doing QR, but will fix later
 ** if becomes problematic.  NB a printf comment is returned when matrix is of full rank
 ** but still no proper checking.
 **
 *************************************************************************/

void lm_wfit(double *x, double *y, double *w, int rows, int cols, double tol, double *out_beta, double *out_resids){
  int i,j;
  int ny = 1;
  int k;
  int numzero_weights = 0,nrows,totnumzero=0;
  
  double fittedvalue;

  double *wts = Calloc(rows,double);
  double *x_wts_f = Calloc(rows*cols,double);
  double *y_wts_f = Calloc(rows,double);
  double *beta = Calloc(cols,double);
  double *resid = Calloc(rows,double);
  double *qraux = Calloc(cols,double);
  double *qty = Calloc(rows,double);
  double *work = Calloc(2*cols,double);
  
  int *jpvt = Calloc(cols,int);

  for (i=0; i < rows; i++){
    if (w[i] == 0.0){
      totnumzero++;
    }
  }

  if (totnumzero > 0){
    /* we need to chop up the X and Y matricies a little more then removing the 
       observations that have weight = 0. In particular fit the model removing the weight
       0 observations. then to compute the residuals for the weight 0 observations used fitted
       values and observed X to compute fitted values */
    numzero_weights = 0;
    for (i=0; i < rows; i++){
      if (w[i] > 0.0){
	wts[i - numzero_weights] = sqrt(w[i]);
	y_wts_f[i - numzero_weights] =  wts[i - numzero_weights]*y[i];
	for (j = 0; j < cols; j++){
	  x_wts_f[j*(rows-totnumzero)+(i-numzero_weights)] = wts[i - numzero_weights]*x[j*rows+i];
	}
      } else {
	numzero_weights++;
      }
    }
    
    for (j=0;j < cols; j++){
      jpvt[j] = j;
    }
    
    nrows = rows - numzero_weights;
    
    /* now fit the model */
    dqrls_(x_wts_f,&nrows,&cols,y_wts_f,&ny,&tol,beta,resid,qty,&k,jpvt,qraux,work);

    if (k != cols){
      /* the solution is not of full rank */
      /* printf("Improper fit\n"); */
       
      for (j = 0; j < k; j++){
	out_beta[j] = beta[jpvt[j]];
      }
      for(j =k; j < cols; j++){
	out_beta[jpvt[j]] =  R_NaN;
      }

    } else {
    
    /* detangle beta and residual estimates */
      
      for (j = 0; j < cols; j++){
	out_beta[j] = beta[jpvt[j]];
      }
    }
    /* now the model is fitted, lets compute residuals for the 0 weighted observations
       by first computing fitted values. */
    
    numzero_weights = 0;
    for (i=0; i < rows; i++){
      if (w[i] > 0){
	out_resids[i] = resid[i- numzero_weights]/wts[i- numzero_weights];
      } else {
	/* compute the fitted value */
	numzero_weights++;
	fittedvalue = 0.0;
	for (j=0; j <cols; j++){
	  if (out_beta[j] != R_NaN){
	    fittedvalue+=out_beta[j]*x[j*rows+i];
	  }
	}
	out_resids[i] = y[i] -  fittedvalue;
      }
    }

  } else {
    for (i=0; i < rows; i++){
      wts[i] = sqrt(w[i]);
    }
    
    /* dqrls is a linpack routine for least squares solution */
  
    for (i=0; i < rows; i++){
      for (j = 0; j < cols; j++){
	x_wts_f[j*rows+i] = wts[i]*x[j*rows+i];
      }
    }
    
    
    for (i=0; i < rows; i++){
      y_wts_f[i] =  wts[i]*y[i];
    }
    
    for (j=0;j < cols; j++){
      jpvt[j] = j;
    }
    
    /* using function from linpack to fit linear model
       dqrls_(double *x, int *n, int *p, double *y, int *ny, double *tol, double *b, double *rsd, double *qty, int *k, int *jpvt, double *qraux, double *work);

    */

    dqrls_(x_wts_f,&rows,&cols,y_wts_f,&ny,&tol,beta,resid,qty,&k,jpvt,qraux,work);
    
    if (k != cols){
      /* the solution is not of full rank */
      /* printf("Improper fit\n");*/ 
      for (j = 0; j < k; j++){
	out_beta[j] = beta[jpvt[j]];
      }
      for(j =k; j < cols; j++){
	out_beta[j] =  R_NaN; /* out_beta[jpvt[j]] =  R_NaN; */
      }
    } else {
    
      /* detangle beta and residual estimates */
      for (j = 0; j < cols; j++){
	out_beta[j] = beta[jpvt[j]];
      }
    }
    for (i=0; i < rows; i++){
      out_resids[i] = resid[i]/wts[i];
      /* resid[i] = resid[i]/wts[i]; */
    }
  }
  
  Free(wts); 
  Free(x_wts_f); 
  Free(y_wts_f);
  Free(beta);
  Free(resid);
  Free(qraux);
  Free(qty);
  Free(work);
  Free(jpvt );
}


/**********************************************************************************
 **
 ** void lm_wfit_R(double *x, double *y, double *w, int *rows, int *cols, double *tol, double *out_beta, double *out_resids)
 ** 
 ** double *x - coefficient matrix: dimension rows*cols
 ** double *y - dependent variable: length rows
 ** double *w - weights for each observation: length rows
 ** int rows, cols - dimension of input
 ** double tol - machine tolerance used in qr decomp
 ** double *outbeta - place to output beta estimates: lenght cols
 ** double *outresid - place to output residuals: length rows
 **
 ** an wrapper that allows us to use .C() calls from R to test the fitting function
 **
 **
 ********************************************************************************/

void lm_wfit_R(double *x, double *y, double *w, int *rows, int *cols, double *tol, double *out_beta, double *out_resids){

  
  lm_wfit(x, y, w, *rows, *cols, *tol, out_beta, out_resids);
    
}
