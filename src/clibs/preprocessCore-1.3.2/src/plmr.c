/*********************************************************************
 **
 ** file: plmr.c
 **
 ** Aim: implement robust linear models specialized to samples + probes model.using
 **      the PLM-r technique
 **
 ** Copyright (C) 2007-2008 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bmb@bmbolstad.com>
 ** 
 ** created on: Nov 22, 2007
 **
 **
 ** History:
 ** Nov 22, 2007 - Initial version. (Based on rlm_anova.c which dates back several years and some notes about PLMR was to be implemented made about 18 months ago, actually early Sept 2006, which in turn was based about ideas in Bolstad (2004) Dissertation, UCB)
 ** Feb 14, 2008 - Add PLM-rr and PLM-rc (only row or column robustified but not both)               
 **
 **
 **
 **
 *********************************************************************/


#include "psi_fns.h"
#include "matrix_functions.h"
#include "rlm.h"
#include "rlm_se.h"
#include "rma_common.h"
#include "plmr.h"

#include <R_ext/Rdynload.h>
#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



static void XTWY(int y_rows, int y_cols, double *wts,double *y, double *xtwy){

  int i,j;
  /* sweep columns (ie chip effects) */
   
  for (j=0; j < y_cols; j++){
    xtwy[j] = 0.0;
    for (i=0; i < y_rows; i++){
      xtwy[j] += wts[j*y_rows + i]* y[j*y_rows + i];
    }
  }
  
  /* sweep rows  (ie probe effects) */
 
  for (i=0; i < y_rows; i++){
    xtwy[i+y_cols] = 0.0;
    for (j=0; j < y_cols; j++){
      xtwy[i+y_cols] += wts[j*y_rows + i]* y[j*y_rows + i]; 
    }
  }

  for (i=0; i < y_rows-1; i++){
    xtwy[i+y_cols] = xtwy[i+y_cols] - xtwy[y_cols+y_rows-1];
  }
  
}




/**********************************************************************************
 **
 ** This is for testing the XTWY() function from R using .C()
 **
 *********************************************************************************/



static void XTWY_R(int *rows, int *cols, double *out_weights, double *y,double *xtwy){
  XTWY(*rows, *cols, out_weights,y,xtwy);
}


/***************

This is R testing code for my own purposes


library(AffyExtensions)
data(Dilution)
  
y <- pm(Dilution)[1:16,]

.C("XTWY_R",as.integer(16),as.integer(4),as.double(rep(1,64)),as.double(as.vector(log2(y))),double(100))

probes <- rep(1:16,4)
samples <- rep(1:4,c(rep(16,4)))
X <- model.matrix(~-1 + as.factor(samples) + C(as.factor(probes),"contr.sum"))
t(X)%*%as.vector(log2(y))

****************/


static void XTWX(int y_rows, int y_cols, double *wts, double *xtwx){

  int Msize = y_cols +y_rows-1;
  int i,j,k;

  /* diagonal elements of first part of matrix ie upper partition */
  for (j =0; j < y_cols;j++){
    for (i=0; i < y_rows; i++){
      xtwx[j*Msize + j]+=wts[j*y_rows + i];
    }
  }


  /* diagonal portion of lower partition matrix: diagonal elements*/ 
  for (j =0; j < y_cols;j++){
    for (i = 0; i < y_rows-1;i++){
      xtwx[(y_cols +i)*Msize + (y_cols +i)]+= wts[j*y_rows + i];
    }
  }
  /* diagonal portion of lower partition matrix: off diagonal elements*/ 
  for (j =0; j < y_cols;j++){
    for (i = 0; i < y_rows-1;i++){
      for (k=i ; k <  y_rows-1;k++){
	xtwx[(y_cols +k)*Msize + (y_cols +i)] = xtwx[(y_cols +i)*Msize + (y_cols +k)]+= wts[j*y_rows + (y_rows-1)];
      }
    }
  }

  /* the two other portions of the matrix */
  for (j =0; j < y_cols;j++){
    for (i= 0; i < y_rows-1;i++){
       xtwx[j*Msize + (y_cols + i)] = xtwx[(y_cols + i)*Msize + j] = wts[j*y_rows + i] - wts[j*y_rows + (y_rows-1)];
    }
  }

}



/**********************************************************************************
 **
 ** This is for testing the XTWX from R using .C()
 **
 *********************************************************************************/

static void XTWX_R(int *rows, int *cols, double *out_weights, double *xtwx){

  XTWX(*rows, *cols, out_weights,xtwx);
}

/***************

This is R test code

.C("XTWX_R",as.integer(16),as.integer(4),rep(1,64))



*************/

static void XTWXinv(int y_rows, int y_cols,double *xtwx){
  int i,j,k;
  int Msize = y_cols +y_rows-1;
  double *P= Calloc(y_cols,double);
  double *RP = Calloc(y_cols*(y_rows-1),double);
  double *RPQ = Calloc((y_rows-1)*(y_rows-1),double);
  double *S = Calloc((y_rows-1)*(y_rows-1),double);
  double *work = Calloc((y_rows-1)*(y_rows-1),double);
  
  for (j=0;j < y_cols;j++){
    for (i=0; i < y_rows -1; i++){
      RP[j*(y_rows-1) + i] = xtwx[j*Msize + (y_cols + i)]*(1.0/xtwx[j*Msize+j]);
    }
  } 
  
  for (i=0; i < y_rows -1; i++){
    for (j=i;j <  y_rows -1; j++){
      for (k=0; k < y_cols;k++){
	RPQ[j*(y_rows-1) + i] +=  RP[k*(y_rows-1) + j]*xtwx[k*Msize + (y_cols + i)];
      }
      RPQ[i*(y_rows-1) + j] = RPQ[j*(y_rows-1) + i];
    }
  }
  
  for (j=0; j < y_rows-1;j++){
    for (i=j; i < y_rows-1;i++){
      RPQ[i*(y_rows-1) + j] = RPQ[j*(y_rows-1)+i] =  xtwx[(y_cols + j)*Msize + (y_cols + i)] - RPQ[j*(y_rows-1) + i]; 
    }
  } 
  
  
  /*for (i =0; i<  y_rows-1; i++){
    for (j=0; j <  y_cols; j++){ 
      printf("%4.4f ",RP[j*(y_rows-1) + i]);
    }
    printf("\n");
    }
  
    for (j=0;j <  y_rows -1; j++){
    for (i=0; i < y_rows -1; i++){
    printf("%4.4f ",RPQ[j*(y_rows-1) + i]);
    }
    printf("\n");
    }
  

    for (i=0; i < y_rows -1; i++){
    for (j=0;j <  y_rows -1; j++){
    printf("%4.4f ",S[j*(y_rows-1) + i]);
    }
    printf("\n");
    }
  */
  



  /* Lets start making the inverse */

  Choleski_inverse(RPQ, S, work, y_rows-1, 0);

  for (j=0; j< y_cols;j++){
    for (i=0; i < y_rows -1; i++){
      xtwx[j*Msize + (y_cols + i)] = 0.0;
      for (k=0; k < y_rows -1; k++){
	xtwx[j*Msize + (y_cols + i)]+= -1.0*(S[i*(y_rows-1) + k])*RP[j*(y_rows-1) + k];
      }
      xtwx[(y_cols + i)*Msize + j]=xtwx[j*Msize + (y_cols + i)];
    }
  }


  for (j=0;j < y_cols;j++){
      P[j] = 1.0/xtwx[j*Msize+j];
  } 


  for (j=0; j < y_cols; j++){
    for (i=j; i < y_cols;i++){
      xtwx[i*Msize + j]=0.0;
      for (k=0;k < y_rows-1; k++){
	xtwx[i*Msize + j]+= RP[i*(y_rows-1) + k]*xtwx[j*Msize + (y_cols + k)];
      }
      xtwx[i*Msize + j]*=-1.0;
      xtwx[j*Msize + i] =  xtwx[i*Msize + j];
    }
    xtwx[j*Msize + j]+=P[j];
  }


  for (j=0; j < y_rows-1;j++){
    for (i=0; i < y_rows-1;i++){
      xtwx[(y_cols + j)*Msize + (y_cols + i)] = S[j*(y_rows-1)+i];
    }
  }


  Free(P);
  Free(work);
  Free(RP);
  Free(RPQ);
  Free(S);

}


/**********************************************************************************
 **
 ** This is for testing the XTWXinv from R
 **
 *********************************************************************************/

static void XTWX_R_inv(int *rows, int *cols, double *xtwx){

  XTWXinv(*rows, *cols, xtwx);
}


/***************

This is R testing code for my own purposes

library(AffyExtensions)

probes <- rep(1:16,4)
 samples <- rep(1:4,c(rep(16,4)))


X <- model.matrix(~ -1 + as.factor(samples) + C(as.factor(probes),"contr.sum"))

W <- diag(seq(0.05,1,length=64))




solve(t(X)%*%W%*%X) - matrix(.C("XTWX_R_inv",as.integer(16),as.integer(4),as.double(t(X)%*%W%*%X))[[3]],19,19)

matrix(.C("XTWX_R_inv",as.integer(16),as.integer(4),as.double(t(X)%*%W%*%X))[[3]],19,19)[1:4,5:19]

XTWX <- t(X)%*%W%*%X

R <- XTWX[5:19,1:4]
P <- XTWX[1:4,1:4]
Q <- t(R)
S <- XTWX [5:19,5:19]


R%*%solve(P)

 probes <- rep(1:16,100)
  samples <- rep(1:100,c(rep(16,100)))


 X <- model.matrix(~ -1 + as.factor(samples) + C(as.factor(probes),"contr.sum"))

  W <- diag(seq(0.05,1,length=1600))

 system.time(matrix(.C("XTWX_R_inv",as.integer(16),as.integer(100),as.double(t(X)%*%W%*%X))[[3]],115,115))

*************/


/****************************************************************************************
 ****************************************************************************************
 **
 ** The following functions are the core part the PLM-r
 **
 ** these add an additional level of robustness to the standard PLM approach.
 **
 ****************************************************************************************
 ****************************************************************************************/


/* the following assumptions are used here

   - assume that the residuals have normal distribution (really we are just hoping that this is approximately true)
   - the residuals are all independent
   - standardizing and squaring the residuals results in chi-sq (v=df=1) random variables
   - we define the median as the (n+1)/2 element if n is odd and the n/2th element if n is even (ie no averaging of the middle elements) when there are less than 30 elements
   - when n is greater than 30 we use a normal distribution approximation

   the CDF for chi-square distribution is 

   F(x) = gam(v/2,x/2)/GAMMA(v/2) where gam() is the lower incomplete Gamma function and GAMMA() is the Gamma funciton

   GAMMA(1/2) = sqrt(PI)
   gamma(1/2,x) = sqrt(PI)*erf(sqrt(x))

   the PDF for chi-square distribution is

   f(x) = 1/(2^(v/2) * GAMMA(v/2)) * x^(v/2 -1) *exp(-x/2)  for x > 0

   
   pnorm(x) = 1/2*(1+ erf(x/sqrt(2)))

   so  erf(x) = 2*pnorm(x*sqrt(2)) - 1


   The CDF for the k'th order statistic is given by

   G(y) = sum_{j=k}^{n} nCj [F(y)]^j [1-F(y)]^(n-j)

   Where nCj = n!/j!(n-j)!

   When n is large we use the normal approximation
  
   for the K'th order statistic with k/n ->p

   the distribution is asymptotically normal with mean at x_p (the percentile)
   and  variance 1/n*(p(1-p)/(f(x_p)^2))
   
   x_p is the solution of

   p = F(x_p)

   when p = 0.5

   x_p = 0.4549364

   and f(0.4549364) = 0.4711363


*/


double estimate_median_percentile(double median, int n){

  int k;
  int j;
  double chisq_p;
  double percentile=0.0;
  double sd;

  if (n < 30){
    /* using the formula for CDF above */
    if (n%2 == 0){
      k = n/2;
    } else {
      k = (n+1)/2;
    }
    chisq_p = pchisq(median,1,1,0);
    
    for (j=k; j <= n; j++){
      percentile+= dbinom((double)j,(double)n,chisq_p,0);
    }
    
    
  } else {
    /* using the normal approximation */
    
    sd = sqrt((double)1/(double)n*0.5*0.5/(0.4711363*0.4711363));
    
    percentile = pnorm(median, 0.4549364, sd, 1, 0);


  }
  return percentile;

}

void R_estimate_median_percentile(double *median, int *n){
  double percentile;

  percentile = estimate_median_percentile(*median, *n);
  
  *median = percentile;
}

/**********************************************************************************
 **
 ** void determine_row_weights(double *resids, int y_rows, int y_cols, double *row_weights)
 ** 
 ** double *resids - estimated residuals
 ** int y_rows - dimension of residuals matrix
 ** int y_cols - dimension of residuals matrix
 ** double *row_weights - on output will contain a weight (0-1) for row (pre-allocated. should be of length y_rows)
 **
 **
 ****************************************************************************************/


void determine_row_weights(double *resids, int y_rows, int y_cols, double *row_weights){
  
  double *current_row = Calloc(y_cols,double);
  double scale;
  int n = y_rows*y_cols;
  int i, j;
  
  double row_med;
  double chisq;
  double znorm;
  

  /* First figure out what we need to standardize the residuals */
  scale = med_abs(resids,n)/0.6745;

  for (i= 0; i < y_rows; i++){
    for (j=0; j < y_cols; j++){
      current_row[j] = (resids[j*y_rows + i]/scale)*(resids[j*y_rows + i]/scale);
    }
  
    row_med = median_nocopy(current_row, y_cols);

    /* figure out what quantile that this lies at on the distribution of the median of a sample from Chi-Sq(1) distribution */

    chisq = estimate_median_percentile(row_med,y_cols);

    if (chisq > 0.5){
      znorm = qnorm(chisq, 0.0, 1.0, 1, 0);
      
      row_weights[i] = psi_huber(znorm,1.345,0);     
      if (row_weights[i] < 0.0001){
	row_weights[i] = 0.0001;
      }

    } else {
      row_weights[i] = 1.0;
    }

  }

  Free(current_row);
}

/**********************************************************************************
 **
 ** void determine_row_weights(double *resids, int y_rows, int y_cols, double *row_weights)
 ** 
 ** double *resids - estimated residuals
 ** int y_rows - dimension of residuals matrix
 ** int y_cols - dimension of residuals matrix
 ** double *col_weights - on output will contain a weight (0-1) for each col (pre-allocated. should be of length y_cols)
 **
 **
 ****************************************************************************************/

void determine_col_weights(double *resids, int y_rows, int y_cols, double *col_weights){
      
  double *current_col = Calloc(y_rows,double);
  double scale;
  int n = y_rows*y_cols;
  int i, j;
  
  double row_med;
  double chisq;
  double znorm;
  

  /* First figure out what we need to standardize the residuals */
  scale = med_abs(resids,n)/0.6745;

  for (j=0; j < y_cols; j++){
    for (i= 0; i < y_rows; i++){
      current_col[i] = (resids[j*y_rows + i]/scale)*(resids[j*y_rows + i]/scale);
    }
  
    row_med = median_nocopy(current_col, y_rows);

    /* figure out what quantile that this lies at on the distribution of the median of a sample from Chi-Sq(1) distribution */

    chisq = estimate_median_percentile(row_med,y_rows);

    if (chisq > 0.5){
      znorm = qnorm(chisq, 0.0, 1.0, 1, 0);
      
      col_weights[j] = psi_huber(znorm,1.345,0);
      if (col_weights[j] < 0.0001){
	col_weights[j] = 0.0001;
      }
    } else {
      col_weights[j] = 1.0;
    }

  }

  Free(current_col);
  


}



/* testing code

   X <- matrix(rnorm(100),10,10)
   .C("R_determine_row_weights",as.vector(X),as.integer(10),as.integer(10),double(10))
   
   X <- matrix(rnorm(1000),100,10)
   .C("R_determine_col_weights",as.vector(X),as.integer(100),as.integer(10),double(10))

*/

void R_determine_row_weights(double *resids, int *y_rows, int *y_cols, double *row_weights){

  determine_row_weights(resids, *y_rows, *y_cols, row_weights);

}

void R_determine_col_weights(double *resids, int *y_rows, int *y_cols, double *col_weights){

  determine_col_weights(resids, *y_rows, *y_cols, col_weights);

}





/**********************************************************************************
 **
 ** void plmr_fit_core(double *y, int rows, int cols,double *out_beta, 
 **                double *out_resids, double *out_weights,
 **                double (* PsiFn)(double, double, int), double psi_k,int max_iter, 
 **                int initialized))
 **
 ** double *y - matrix of response variables (stored by column, with rows probes, columns chips
 ** int rows - dimensions of y
 ** int cols - dimensions of y
 **
 ** specializes procedure so decomposes matrix more efficiently
 ** note that routine is not as numerically stable as above.
 **
 ** fits a row + columns model
 **
 **********************************************************************************/

static void plmr_fit_core(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized, int rowrobust, int colrobust){

  int i,j,iter;
  /* double tol = 1e-7; */
  double acc = 1e-4;
  double scale =0.0;
  double conv;
  double endprobe;

  double *wts = out_weights; 

  double *row_weights = Calloc(y_rows, double);
  double *col_weights = Calloc(y_cols, double);

  double *resids = out_resids; 
  double *old_resids = Calloc(y_rows*y_cols,double);
  
  double *rowmeans = Calloc(y_rows,double);

  double *xtwx = Calloc((y_rows+y_cols-1)*(y_rows+y_cols-1),double);
  double *xtwy = Calloc((y_rows+y_cols),double);

  double sumweights, rows;
  
  rows = y_rows*y_cols;
  
  if (!initialized){
    
    /* intially use equal weights */
    for (i=0; i < rows; i++){
      wts[i] = 1.0;
    }
  }

  /* starting matrix */
  
  for (i=0; i < y_rows; i++){
    for (j=0; j < y_cols; j++){
      resids[j*y_rows + i] = y[j*y_rows + i];
    }
  }
  
  /* sweep columns (ie chip effects) */

  for (j=0; j < y_cols; j++){
    out_beta[j] = 0.0;
    sumweights = 0.0;
    for (i=0; i < y_rows; i++){
      out_beta[j] += wts[j*y_rows + i]* resids[j*y_rows + i];
      sumweights +=  wts[j*y_rows + i];
    }
    out_beta[j]/=sumweights;
    for (i=0; i < y_rows; i++){
      resids[j*y_rows + i] = resids[j*y_rows + i] -  out_beta[j];
    }
  }


 /* sweep rows  (ie probe effects) */
  
  for (i=0; i < y_rows; i++){
    rowmeans[i] = 0.0;
    sumweights = 0.0;
    for (j=0; j < y_cols; j++){
      rowmeans[i] += wts[j*y_rows + i]* resids[j*y_rows + i]; 
      sumweights +=  wts[j*y_rows + i];
    }
    rowmeans[i]/=sumweights;
    for (j=0; j < y_cols; j++){
       resids[j*y_rows + i] =  resids[j*y_rows + i] - rowmeans[i];
    }
  }
  for (i=0; i < y_rows-1; i++){
    out_beta[i+y_cols] = rowmeans[i];
  }


  if (!rowrobust){
    for (i=0; i < y_rows; i++){
      row_weights[i] = 1.0;
    }
  }
  
  if (!colrobust){
    for (j=0; j < y_cols; j++){
      col_weights[j] = 1.0;
    }
  }
  
  for (iter = 0; iter < max_iter; iter++){
    
    scale = med_abs(resids,rows)/0.6745;
    
    if (fabs(scale) < 1e-10){
      /*printf("Scale too small \n"); */
      break;
    }
    for (i =0; i < rows; i++){
      old_resids[i] = resids[i];
    }

    /* weights for individual measurements */

    for (i=0; i < rows; i++){
      wts[i] = PsiFn(resids[i]/scale,psi_k,0);  /*           psi_huber(resids[i]/scale,k,0); */
    }
   
    /* now determine row and column weights */
    if (iter > 0){
      if (rowrobust){
	determine_row_weights(resids, y_rows, y_cols, row_weights);
      }
      if (colrobust){
	determine_col_weights(resids, y_rows, y_cols, col_weights);
      }
      for (j= 0; j < y_cols; j++){
	for (i = 0; i < y_rows; i++){
	  wts[j*y_rows + i] = wts[j*y_rows + i]*row_weights[i]*col_weights[j];
	}
      }
    }


    /* weighted least squares */
    
    memset(xtwx,0,(y_rows+y_cols-1)*(y_rows+y_cols-1)*sizeof(double));


    XTWX(y_rows,y_cols,wts,xtwx);
    XTWXinv(y_rows, y_cols,xtwx);
    XTWY(y_rows, y_cols, wts,y, xtwy);

    
    for (i=0;i < y_rows+y_cols-1; i++){
      out_beta[i] = 0.0;
       for (j=0;j < y_rows+y_cols -1; j++){
    	 out_beta[i] += xtwx[j*(y_rows+y_cols -1)+i]*xtwy[j];
       }
    }

    /* residuals */
    
    for (i=0; i < y_rows-1; i++){
      for (j=0; j < y_cols; j++){
	resids[j*y_rows +i] = y[j*y_rows + i]- (out_beta[j] + out_beta[i + y_cols]); 
      }
    }

    for (j=0; j < y_cols; j++){
      endprobe=0.0;
      for (i=0; i < y_rows-1; i++){
	endprobe+= out_beta[i + y_cols];
      }
      resids[j*y_rows + y_rows-1] = y[j*y_rows + y_rows-1]- (out_beta[j] - endprobe);
    }

    /*check convergence  based on residuals */
    
    conv = irls_delta(old_resids,resids, rows);
    
    if (conv < acc){
      /*    printf("Converged \n");*/
      break; 

    }



  }
    
  /* order output in probes, samples order */
  /*
    for (i=0;i < y_rows+y_cols-1; i++){
    old_resids[i] = out_beta[i];
    }  
    for (i=0; i <y_rows-1;i++){
    out_beta[i] = old_resids[i+y_cols];
    }
    for (i=0; i < y_cols; i++){
    out_beta[i+(y_rows-1)] = old_resids[i];
    }
  */



  Free(xtwx);
  Free(xtwy);
  Free(old_resids);
  Free(rowmeans);


}


void plmr_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){

  plmr_fit_core(y, y_rows, y_cols, out_beta, out_resids, out_weights,PsiFn, psi_k, max_iter, initialized,1,1);
}

void plmrr_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){

  plmr_fit_core(y, y_rows, y_cols, out_beta, out_resids, out_weights,PsiFn, psi_k, max_iter, initialized,1,0);
}

void plmrc_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){

  plmr_fit_core(y, y_rows, y_cols, out_beta, out_resids, out_weights,PsiFn, psi_k, max_iter, initialized,0,1);
}





/**********************************************************************************
 **
 ** This is for testing the rlm_fit_anova function from R
 **
 *********************************************************************************/

void plmr_fit_R(double *y, int *rows, int *cols, double *out_beta, double *out_resids, double *out_weights, int *its){

  plmr_fit(y, *rows, *cols, out_beta, out_resids,out_weights,psi_huber,1.345, *its,0);
}


/*    

This is testing code for my own use.

library(affyPLM)
library(affydata)
data(Dilution)
  
y <- pm(Dilution)[33:48,]
y <- pm(Dilution)[49:64,]
y[,1] <- rnorm(16,1000,100)
.C("plmr_fit_R",as.double(log2(y)),as.integer(16),as.integer(4),double(20),double(64),double(64),as.integer(2))

matrix(.C("plmr_fit_R",as.double(log2(y)),as.integer(16),as.integer(4),double(20),double(64),double(64),as.integer(1))[[6]],16,4)


*/


static void plmr_wfit_core(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized, int rowrobust, int colrobust){

  int i,j,iter;
  /* double tol = 1e-7; */
  double acc = 1e-4;
  double scale =0.0;
  double conv;
  double endprobe;

  double *wts = out_weights; 
 
  double *row_weights = Calloc(y_rows, double);
  double *col_weights = Calloc(y_cols, double);

  double *resids = out_resids; 
  double *old_resids = Calloc(y_rows*y_cols,double);
  
  double *rowmeans = Calloc(y_rows,double);

  double *xtwx = Calloc((y_rows+y_cols-1)*(y_rows+y_cols-1),double);
  double *xtwy = Calloc((y_rows+y_cols),double);

  double sumweights, rows;
  
  rows = y_rows*y_cols;
  
  if (!initialized){
    
    /* intially use equal weights */
    for (i=0; i < rows; i++){
      wts[i] = w[i]*1.0;
    }
  }

  /* starting matrix */
  
  for (i=0; i < y_rows; i++){
    for (j=0; j < y_cols; j++){
      resids[j*y_rows + i] = y[j*y_rows + i];
    }
  }
  
  /* sweep columns (ie chip effects) */

  for (j=0; j < y_cols; j++){
    out_beta[j] = 0.0;
    sumweights = 0.0;
    for (i=0; i < y_rows; i++){
      out_beta[j] += wts[j*y_rows + i]* resids[j*y_rows + i];
      sumweights +=  wts[j*y_rows + i];
    }
    out_beta[j]/=sumweights;
    for (i=0; i < y_rows; i++){
      resids[j*y_rows + i] = resids[j*y_rows + i] -  out_beta[j];
    }
  }


 /* sweep rows  (ie probe effects) */
  
  for (i=0; i < y_rows; i++){
    rowmeans[i] = 0.0;
    sumweights = 0.0;
    for (j=0; j < y_cols; j++){
      rowmeans[i] += wts[j*y_rows + i]* resids[j*y_rows + i]; 
      sumweights +=  wts[j*y_rows + i];
    }
    rowmeans[i]/=sumweights;
    for (j=0; j < y_cols; j++){
       resids[j*y_rows + i] =  resids[j*y_rows + i] - rowmeans[i];
    }
  }
  for (i=0; i < y_rows-1; i++){
    out_beta[i+y_cols] = rowmeans[i];
  }
 

  if (!rowrobust){
    for (i=0; i < y_rows; i++){
      row_weights[i] = 1.0;
    }
  }
  
  if (!colrobust){
    for (j=0; j < y_cols; j++){
      col_weights[j] = 1.0;
    }
  }
  
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
    
    /* now determine row and column weights */
    if (iter > 0){
      if (rowrobust){
	determine_row_weights(resids, y_rows, y_cols, row_weights);
      }
      if (colrobust){
	determine_col_weights(resids, y_rows, y_cols, col_weights);
      }
 
      for (j= 0; j < y_cols; j++){
	for (i = 0; i < y_rows; i++){
	  wts[j*y_rows + i] = wts[j*y_rows + i]*row_weights[i]*col_weights[j];
	}
      }
    }

    /* printf("%f\n",scale); */


    /* weighted least squares */
    
    memset(xtwx,0,(y_rows+y_cols-1)*(y_rows+y_cols-1)*sizeof(double));


    XTWX(y_rows,y_cols,wts,xtwx);
    XTWXinv(y_rows, y_cols,xtwx);
    XTWY(y_rows, y_cols, wts,y, xtwy);

    
    for (i=0;i < y_rows+y_cols-1; i++){
      out_beta[i] = 0.0;
       for (j=0;j < y_rows+y_cols -1; j++){
    	 out_beta[i] += xtwx[j*(y_rows+y_cols -1)+i]*xtwy[j];
       }
    }

    /* residuals */
    
    for (i=0; i < y_rows-1; i++){
      for (j=0; j < y_cols; j++){
	resids[j*y_rows +i] = y[j*y_rows + i]- (out_beta[j] + out_beta[i + y_cols]); 
      }
    }

    for (j=0; j < y_cols; j++){
      endprobe=0.0;
      for (i=0; i < y_rows-1; i++){
	endprobe+= out_beta[i + y_cols];
      }
      resids[j*y_rows + y_rows-1] = y[j*y_rows + y_rows-1]- (out_beta[j] - endprobe);
    }

    /*check convergence  based on residuals */
    
    conv = irls_delta(old_resids,resids, rows);
    
    if (conv < acc){
      /*    printf("Converged \n");*/
      break; 

    }



  }
    
  /* order output in probes, samples order */
  /*
    for (i=0;i < y_rows+y_cols-1; i++){
    old_resids[i] = out_beta[i];
    }  
    for (i=0; i <y_rows-1;i++){
    out_beta[i] = old_resids[i+y_cols];
    }
    for (i=0; i < y_cols; i++){
    out_beta[i+(y_rows-1)] = old_resids[i];
    }
  */



  Free(xtwx);
  Free(xtwy);
  Free(old_resids);
  Free(rowmeans);


}



void plmr_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){
  
  plmr_wfit_core(y, y_rows, y_cols, w, out_beta, out_resids, out_weights, PsiFn , psi_k, max_iter, initialized, 1, 1);

}

void plmrr_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){
  
  plmr_wfit_core(y, y_rows, y_cols, w, out_beta, out_resids, out_weights, PsiFn , psi_k, max_iter, initialized, 1, 0);

}

void plmrc_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){
  
  plmr_wfit_core(y, y_rows, y_cols, w, out_beta, out_resids, out_weights, PsiFn , psi_k, max_iter, initialized, 0, 1);

}

