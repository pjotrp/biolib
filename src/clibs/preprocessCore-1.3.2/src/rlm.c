/*********************************************************************
 **
 ** file: rlm.c
 **
 ** Aim: implement robust linear models.
 **
 ** Copyright (C) 2003 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bolstad@stat.berkeley.edu>
 ** 
 ** created on: Jan 11, 2003
 **
 ** Last modified: Feb 11, 2003
 **
 ** The aim will be to provide a function that allows us to fit various
 ** robust linear models to affy data. Initially we will focus 
 ** on huber regression. Code is inspired by rlm() method which is
 ** part of the MASS package bundle.
 **
 **
 ** History
 **
 ** Jan 11, 2003 - Initial version
 ** Jan 12, 2003 - Continued implementing method.
 ** Jan 13, 2003 - Continued implementing. lm_wfit tested.
 **                rlm_fit tested. Integrate into AffyExtensions.
 ** Jan 29, 2003 - Be sure to check the fit to see if full rank.
 ** Jan 31, 2003 - Clean up/Expand Code comments
 ** Feb 10, 2003 - modify psi_huber so that weight, derivative and psi itself may be returned.
 **                this will fix a bug in se routines
 ** Feb 11, 2003 - clean up rlm_fit, so that there is no longer unnecesary 
 **                memory allocation and copying of parameter/weights/se estimates.
 ** May 31, 2003 - Move psi_huber to psi_fns.c
 ** Jun 04, 2003 - Make rlm_fit accept a function pointer to allow 
 **                more general psi functions
 ** Jun 05, 2003 - move lm_wfit  to lm.c
 ** Sep 13, 2003 - rlm now has a parameter that controls the maximum number of iterations
 ** Apr 5, 2004 - all malloc/free are now Calloc/Free
 ** May 26, 2004 - rlm specialised for anova model. 
 ** June 21, 2004 - fixed up specialization for default anova model.
 ** June 23, 2004 - move specialization to its own file
 ** July 26, 2004 - rlm_wfit added
 ** Mar 1, 2006 - change all comments to ansi style
 ** May 27, 2007 - clean up code for inclusion in preprocessCore
 **
 ********************************************************************/

#include <math.h>
#include <stdlib.h>

#include "rma_common.h"

#include "rlm.h"
#include "psi_fns.h"
#include "lm.h"
#include "matrix_functions.h"


#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>



/***************************************************************
 **
 ** double irls_delta(double *old, double *new, int length)
 **
 ** double *old - previous value of a vector
 ** double *new - new value of a vector
 ** int length - length of vector
 **
 ** this function computes the sum of the difference of two vectors
 ** divides this by the sum squared of the old datavector.
 **
 ** the aim of this function is compute something to test for 
 ** convergence in the iteratively reweighted least squares (IRLS)
 ** 
 **
 **************************************************************/

double irls_delta(double *old, double *new, int length){
  int i=0;
  double sum = 0.0;
  double sum2 =0.0;
  double divisor=1e-20;

  for (i=0; i < length; i++){
    sum = sum + (old[i] - new[i])*(old[i]-new[i]);
    sum2 = sum2 + old[i]*old[i];
  }
  
  if(sum2 >= divisor){
    divisor = sum2;
  }

  return sqrt(sum/divisor); 
} 


/****************************************************************
 **
 ** This function is another method for computing convergence in the
 ** robust linear model fitting procedure. It is not currently used
 ** but is here in case it is required at a later date.
 **
 ** irls.rrxwr <- function(x, w, r) {
 **       w <- sqrt(w)
 **	  max(abs((matrix(r * w, 1, length(r)) %*% x)/sqrt(matrix(w,1, length(r))%*% (x^2))))/sqrt(sum(w * r^2))
 **	  }
 

 static double irls_rrxwr(double *x, double *w, double *r, int rows, int cols){
  int i =0,j=0;
  double *weights = Calloc(rows,double);
  double *rw = Calloc(rows,double);
  double *wr2 = Calloc(rows,double);
  double *numerator = Calloc(cols,double);
  double *denominator = Calloc(cols,double);
  double max_num,sum=0.0;

  for (i =0; i < rows; i++){
    weights[i] = sqrt(w[i]);    
    rw[i] = weights[i]*r[i];
    wr2[i] = weights[i]*r[i]*r[i];
  }
  
  for (j=0; j < cols; j++){
    for (i=0; i < rows; i++){
      numerator[j] = numerator[j] + rw[i]*x[j*rows + i];
      denominator[j] = denominator[j] + w[i]*x[j*rows + i]*x[j*rows + i];
    }
  }
  
  for (j=0; j < cols; j++){
    numerator[j] = fabs(numerator[j]/sqrt(denominator[j]));
  }
  
  max_num = numerator[0];
  for (j=1; j < cols; j++){
    if (numerator[j] > max_num){
      max_num = numerator[j];
    }
  }
  
  sum = 0.0;
  for (i=0; i < rows; i++){
    sum+=wr2[i];
  }
  
  Free(numerator);
  Free(denominator);
  Free(wr2);
  Free(rw);
  Free(weights);
  return(max_num/sum);
}  


**********************************************************************************/




/**********************************************************************************
 **
 ** double med_abs(double *x, int length)
 **
 ** double *x - a vector of data
 ** int length - length of the vector.
 ** 
 ** returns the median of the absolute values.
 **
 ** computes the median of the absolute values of a given vector.
 **
 **********************************************************************************/

double med_abs(double *x, int length){
  int i;
  double med_abs;
  double *buffer = Calloc(length,double);

  for (i = 0; i < length; i++)
    buffer[i] = fabs(x[i]);
  
  med_abs = median(buffer,length);
    
  Free(buffer);
  return(med_abs);
}


/**********************************************************************************
 **
 ** void rlm_fit(double *x, double *y, int rows, int cols, double *out_beta, double *out_resids, double *out_weights)
 **
 ** double *x - model matrix: dimension rows*cols
 ** double *y - independent variable: dimension cols
 ** int rows,cols - dimensions of matrix
 ** double *out_beta - already allocated space to store beta estimates: length cols
 ** double *out_resids - already allocated space to store residuals: length rows
 ** double *out_weights - already allocated space to store regression weights: length rows
 ** 
 ** This function fits a robust linear model using M estimation, convergence is
 ** determined by the change in residuals.
 **
 **
 **********************************************************************************/


void rlm_fit(double *x, double *y, int rows, int cols, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){

  int i; /* ,j; */
  /* double k = 1.345; */
  /* double k2 = 1.345; */
  double tol = 1e-7;
  double acc = 1e-4;
  double scale =0.0;
  double conv;
  /* int max_iter=20; */
  int iter;
  


  double *wts = out_weights; 
  double *beta = out_beta; 
  double *resids = out_resids; 
  double *old_resids = Calloc(rows,double);
  



  if (!initialized){

    /* intially use equal weights */
    for (i=0; i < rows; i++){
      wts[i] = 1.0;
    }
    
    /* get our intial beta estimates by standard linear regression */
    
    
    lm_wfit(x, y, wts, rows, cols, tol, beta, resids);
  }
  /* printf("%f %f %f\n",beta[0],beta[1],beta[2]); */

  /*
    done <- FALSE
    conv <- NULL
    n1 <- nrow(x) - ncol(x)
    if (scale.est != "MM")
    scale <- mad(resid, 0)
    theta <- 2 * pnorm(k2) - 1
    gamma <- theta + k2^2 * (1 - theta) - 2 * k2 * dnorm(k2)
  */

  for (iter = 0; iter < max_iter; iter++){
    
    scale = med_abs(resids,rows)/0.6745;

    if (fabs(scale) < 1e-10){
      /*printf("Scale too small \n"); */
      break;
    }
    
    for (i =0; i < rows; i++){
      old_resids[i] = resids[i];
    }

    for (i=0; i < rows; i++){
      wts[i] = PsiFn(resids[i]/scale,psi_k,0);  /*           psi_huber(resids[i]/scale,k,0); */
    }
   
    lm_wfit(x, y, wts, rows, cols, tol, beta, resids);


    /*check convergence  based on residuals */
    
    conv = irls_delta(old_resids,resids, rows);

    if (conv < acc){
      /*    printf("Converged \n");*/
      break; 
      
    }
  }

 
  /*  for (j=0; j < cols; j++){
    out_beta[j] = beta[j];
    } */
  
  /* for (i=0; i < rows; i++){
     out_resids[i] = resids[i];*/
    /*  out_weights[i] = wts[i]; */
  /* } */



  Free(old_resids);
}



/**********************************************************************************
 **
 ** void rlm_fit_R(double *x, double *y, int *rows, int *cols, double *out_beta, double *out_resids, double *out_weights)
 **
 ** double *x - model matrix: dimension rows*cols
 ** double *y - independent variable: dimension cols
 ** int *rows,*cols - dimensions of matrix
 ** double *out_beta - already allocated space to store beta estimates: length cols
 ** double *out_resids - already allocated space to store residuals: length rows
 ** double *out_weights - already allocated space to store regression weights: length rows
 ** 
 ** A wrapper function that allows us to use .C() in R to test robust linear model
 ** fitting function.
 **
 **********************************************************************************/

void rlm_fit_R(double *x, double *y, int *rows, int *cols, double *out_beta, double *out_resids, double *out_weights){

  rlm_fit(x, y, *rows, *cols, out_beta, out_resids,out_weights,psi_huber,1.345, 20,0);
}











/**********************************************************************************
 **
 ** void rlm_wfit(double *x, double *y, int rows, int cols, double *out_beta, double *out_resids, double *out_weights)
 **
 ** double *x - model matrix: dimension rows*cols
 ** double *y - independent variable: dimension cols
 ** int rows,cols - dimensions of matrix
 ** double *out_beta - already allocated space to store beta estimates: length cols
 ** double *out_resids - already allocated space to store residuals: length rows
 ** double *out_weights - already allocated space to store regression weights: length rows
 ** 
 ** This function fits a robust linear model using M estimation, convergence is
 ** determined by the change in residuals.
 **
 **
 **********************************************************************************/


void rlm_wfit(double *x, double *y, double *w, int rows, int cols, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){

  int i; /* ,j; */
  /* double k = 1.345; */
  /* double k2 = 1.345; */
  double tol = 1e-7;
  double acc = 1e-4;
  double scale =0.0;
  double conv;
  /* int max_iter=20; */
  int iter;
  


  double *wts = out_weights;
  double *beta = out_beta; 
  double *resids = out_resids; 
  double *old_resids = Calloc(rows,double);
  



  if (!initialized){

    /* intially use equal weights */
    for (i=0; i < rows; i++){
      wts[i] = w[i]*1.0;
    }
    
    /* get our intial beta estimates by standard linear regression */
    
    
    lm_wfit(x, y, wts, rows, cols, tol, beta, resids);
  }
  /* printf("%f %f %f\n",beta[0],beta[1],beta[2]); */

  /*
    done <- FALSE
    conv <- NULL
    n1 <- nrow(x) - ncol(x)
    if (scale.est != "MM")
    scale <- mad(resid, 0)
    theta <- 2 * pnorm(k2) - 1
    gamma <- theta + k2^2 * (1 - theta) - 2 * k2 * dnorm(k2)
  */

  for (iter = 0; iter < max_iter; iter++){
    
    scale = med_abs(resids,rows)/0.6745;

    if (fabs(scale) < 1e-10){
      /*printf("Scale too small \n"); */
      break;
    }
    
    for (i =0; i < rows; i++){
      old_resids[i] = resids[i];
    }

    for (i=0; i < rows; i++){
      wts[i] = w[i]*PsiFn(resids[i]/scale,psi_k,0);  /*           psi_huber(resids[i]/scale,k,0); */
    }
   
    lm_wfit(x, y, wts, rows, cols, tol, beta, resids);


    /*check convergence  based on residuals */
    
    conv = irls_delta(old_resids,resids, rows);

    if (conv < acc){
      /*    printf("Converged \n");*/
      break; 
      
    }
  }

 
  /*  for (j=0; j < cols; j++){
    out_beta[j] = beta[j];
    } */
  
  /* for (i=0; i < rows; i++){
     out_resids[i] = resids[i];*/
    /*  out_weights[i] = wts[i]; */
  /* } */



  Free(old_resids);
}





void rlm_wfit_R(double *x, double *y, double *w, int *rows, int *cols, double *out_beta, double *out_resids, double *out_weights){

  rlm_wfit(x, y, w, *rows, *cols, out_beta, out_resids,out_weights,psi_huber,1.345, 20,0);
}
