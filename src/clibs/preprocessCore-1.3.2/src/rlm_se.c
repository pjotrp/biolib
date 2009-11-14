/*********************************************************************
 **
 ** file: rlm_se.c
 **
 ** Aim: implement computation of standard errors for robust linear models.
 **
 ** Copyright (C) 2003-2004 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bolstad@stat.berkeley.edu>
 ** 
 ** created on: Jan 27, 2003
 **
 ** Last modified: Feb 11, 2003
 **
 ** We provide implemementations of all three methods of computing standard errors
 ** given in Huber (1981) Robust Statistic. Wiley. In particular equations
 ** (6.5), (6.6) and (6.7). Finally we will implement the standard errors in terms
 ** of the standard errors from a weighted linear regression. Note that Huber strongly advises
 ** against the use of this last method as it is "not robust in general". We provide it to agree 
 ** with previous implementations in R code.
 **  
 ** In particular we implement functions
 ** RLM_SE_Method_1 (6.5)
 ** RLM_SE_Method_2 (6.6)
 ** RLM_SE_Method_3 (6.7)
 ** RLM_SE_Method_4 (weighted regression method)
 **
 **
 ** History
 **
 ** Jan 27, 2003 - Initial version using weighted least squares type se
 ** Jan 28, 2003 - More work, try to get huber recommendations working.
 **                Realize that the W matrix is sometimes not of full 
 **                rank. to get around this problem recommend using
 **                generalized inverse (compute using svd). <-- TO DO
 **                Add in better checking to the inversion routines (Choleski).
 ** Jan 31, 2003 - make Choleski inverse take parameter to return only
 **                upper triangle of inverse matrix
 **                Actually make se routines check that nothing bad happens 
 **                when taking the inverse.
 ** Feb 02, 2003 - Test if choleski failed, if did use an svd to compute 
 **                a generalize invese and use this instead.
 **                code for testing failure to se.type 2,3 added
 **                SVD approach to inverses added and tested.
 ** Feb 08, 2003 - Move a code block which will improve efficiency for
 **                se.type = 4
 **                TO BE DONE: replace linpack routines with Lapack routines to further improve speed
 ** Feb 10, 2003 - Change sumpsi, sumpsi2 to user option 2 (the actual psi function) in psi_huber.
 **                this will fix a bug in se.type=1,2,3. we would agree completely
 **                with summary.rlm in R except that we estimate the scale parameter using
 **                residuals from the final fit and R uses a scale from one step back.
 **                A mechanism has been added to switch between LAPACK and LINPACK with the default 
 **                being LAPACK.
 ** Feb 11, 2003 - Make LINPACK DEFAULT, comment out LAPACK in chol, svd routines, solves linking 
 **                problems on windows, will get fixed later
 ** Feb 24, 2003 - comment out a few declared but unused variables, some of these might be used later
 ** Mar 28, 2003 - uncomment LAPACK code. LAPACK will be default using R 1.7.0 and later, which
 **                will be a requirement for AffyExtensions 0.5-1 and later
 ** Jun 11, 2003 - Modify Standard error routines to handle different psi_fns.
 ** Jul 23, 2003 - remove the warning about moduleCdynload by including appropriate header file
 ** Sep 06, 2003 - now we return the whole variance covariance matrix and residual SE with appropriate
 **                DF
 ** Sep 07, 2003 - variance matrix from method == 4 now returned
 ** Sep 08, 2003 - variance matrix from method == 1, 2, 3 returned
 ** Sep 13, 2003 - copy only upper triangle of variance matrix into output.
 **                Also if the variance matrix is the NULL pointer don't store anything
 **                at all.
 ** Jan 17, 2004 - tweak how kappa is estimated so it works better
 **                in with non - huber psis
 ** June 22, 2004 - moved some functions to matrix_functions.c
 ** March 1, 2006 - change all comments to ansi style
 **                
 ********************************************************************/

#include "rlm.h"
#include "rlm_se.h"
#include "psi_fns.h"
#include "matrix_functions.h"

#include <R_ext/Rdynload.h>
#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*************************************************************************
 **
 ** void RLM_SE_Method_1(double residvar, double *XTX, int p, double *se_estimates)
 **
 ** double residvar - residual variance estimate
 ** double *XTX - t(Design matrix)%*% Design Matrix
 ** double p - number of parameters
 ** double *se_estimates - on output contains standard error estimates for each of
 **                        the parametes
 **
 ** this function computes the parameter standard errors using the first
 ** method described in Huber (1981)
 ** 
 ** ie k^2 (sum psi^2/(n-p))/(sum psi'/n)^2 *(XtX)^(-1)
 **
 **
 ************************************************************************/


static void RLM_SE_Method_1(double residvar, double *XTX, int p, double *se_estimates,double *varcov){
  int i,j;
  double *XTXinv = Calloc(p*p,double);
  double *work = Calloc(p*p,double);

  if (!Choleski_inverse(XTX,XTXinv,work,p,1)){
    for (i =0; i < p; i++){
      se_estimates[i] = sqrt(residvar*XTXinv[i*p + i]);
    }
  } else {
    printf("Singular matrix in SE inverse calculation");    
  }    


  if (varcov != NULL)
    for (i =0; i < p; i++){
      for (j = i; j < p; j++){
	varcov[j*p +i]= residvar*XTXinv[j*p +i];
      }
    }
  
  Free(work);
  Free(XTXinv);
}


/*************************************************************************
 **
 ** void RLM_SE_Method_2(double residvar, double *W, int p, double *se_estimates)
 **
 ** double residvar - residual variance estimate
 ** double *XTX - t(Design matrix)%*% Design Matrix
 ** double p - number of parameters
 ** double *se_estimates - on output contains standard error estimates for each of
 **                        the parametes
 **
 ** this function computes the parameter standard errors using the second
 ** method described in Huber (1981)
 ** 
 ** ie K*(sum psi^2/(n-p))/(sum psi'/n) *(W)^(-1)
 **
 **
 ************************************************************************/

static void RLM_SE_Method_2(double residvar, double *W, int p, double *se_estimates,double *varcov){
  int i,j; /* l,k; */
  double *Winv = Calloc(p*p,double);
  double *work = Calloc(p*p,double);

  if (!Choleski_inverse(W,Winv,work,p,1)){
    for (i =0; i < p; i++){
      se_estimates[i] = sqrt(residvar*Winv[i*p + i]);
      /* printf("%f ", se_estimates[i]); */
    }
  } else {
    /* printf("Using a G-inverse\n"); */
    SVD_inverse(W, Winv,p);
    for (i =0; i < p; i++){
      se_estimates[i] = sqrt(residvar*Winv[i*p + i]);
      /* printf("%f ", se_estimates[i]); */
    }
  }

  if (varcov != NULL)
    for (i =0; i < p; i++){
      for (j = i; j < p; j++){
	varcov[j*p +i]= residvar*Winv[j*p +i];
      }
    }
  
  
  Free(work);
  Free(Winv);

}

/*************************************************************************
 **
 ** void RLM_SE_Method_3(double residvar, double *XTX, double *W, int p, double *se_estimates)
 **
 ** double residvar - residual variance estimate
 ** double *XTX - t(Design matrix)%*% Design Matrix
 ** double p - number of parameters
 ** double *se_estimates - on output contains standard error estimates for each of
 **                        the parametes
 **
 ** this function computes the parameter standard errors using the third
 ** method described in Huber (1981)
 ** 
 ** ie 1/(K)*(sum psi^2/(n-p))*(W)^(-1)(XtX)W^(-1)
 **
 **
 ************************************************************************/

static int RLM_SE_Method_3(double residvar, double *XTX, double *W, int p, double *se_estimates,double *varcov){
  int i,j,k;   /* l; */
  int rv;

  double *Winv = Calloc(p*p,double);
  double *work = Calloc(p*p,double);
  

  /***************** 

  double *Wcopy = Calloc(p*p,double);

  
  for (i=0; i <p; i++){
    for (j=0; j < p; j++){
      Wcopy[j*p + i] = W[j*p+i];
    }
    } **********************/
  
  if(Choleski_inverse(W,Winv,work,p,1)){
    SVD_inverse(W, Winv,p);
  }
  
  /*** want W^(-1)*(XtX)*W^(-1) ***/

  /*** first Winv*(XtX) ***/

  for (i=0; i <p; i++){
    for (j=0; j < p; j++){
      work[j*p + i] = 0.0;
      for (k = 0; k < p; k++){
	work[j*p+i]+= Winv[k*p +i] * XTX[j*p + k];
      }
    }
  }
 
  /* now again by W^(-1) */
  
   for (i=0; i <p; i++){
    for (j=0; j < p; j++){
      W[j*p + i] =0.0;
      for (k = 0; k < p; k++){
	W[j*p+i]+= work[k*p +i] * Winv[j*p + k];
      }
    }
   }
  
   for (i =0; i < p; i++){
     se_estimates[i] = sqrt(residvar*W[i*p + i]);
     /* printf("%f ", se_estimates[i]); */
   }
   
   rv = 0;
   if (varcov != NULL)
     for (i =0; i < p; i++){
       for (j = i; j < p; j++){
	 varcov[j*p +i]= residvar*W[j*p +i];
       }
   }
  
  Free(work);
  Free(Winv);

  return rv;

}



/*********************************************************************
 **
 ** void rlm_compute_se(double *X,double *Y, int n, int p, double *beta, double *resids,double *weights,double *se_estimates, int method)
 **
 ** given a robust linear model fit to data, compute the standard errors of the parameter estimates
 **
 ** double *X
 ** double *Y
 ** int n
 ** int p
 ** double *beta
 ** double *resids
 ** double *weights
 ** double *se_estimates
 ** int method
 **
 **
 **
 **
 **
 ** Note that we compute Kappa using a simplification for Huber Psi
 **
 ** ie Kappa = 1 + p/n* var(psi')/(E psi')^2
 **
 ** simplifies to
 **
 ** Kappa = 1 + p*(1-m)/(n*m)
 **
 ** where m is the proportion of psi' = 1 (ie the unwinsorized observations)
 **
 ** note that W_jk = sum_i (psi'(r_i)*x_{ij}*x_{ik}) ie a weighted form of XTX
 ** 
 **  
 ** 
 **
 **
 *********************************************************************/


void rlm_compute_se(double *X,double *Y, int n, int p, double *beta, double *resids,double *weights,double *se_estimates, double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k){
  
  int i,j,k; /* counter/indexing variables */
  double k1 = psi_k;   /*  was 1.345; */
  double sumpsi2=0.0;  /* sum of psi(r_i)^2 */
  /*  double sumpsi=0.0; */
  double sumderivpsi=0.0; /* sum of psi'(r_i) */
  double Kappa=0.0;      /* A correction factor */
  double scale=0.0;
  
  double *XTX = Calloc(p*p,double);
  double *W = Calloc(p*p,double);
  double *work = Calloc(p*p,double);
  double RMSEw = 0.0;
  double vs=0.0,m,varderivpsi=0.0; 

  /* Initialize Lapack library */
  /* if(!Lapack_initialized) Lapack_Init(); */

  if (method == 4){
    for (i=0; i < n; i++){
      RMSEw+= weights[i]*resids[i]*resids[i];
    }
    
    RMSEw = sqrt(RMSEw/(double)(n-p));

    residSE[0] =  RMSEw;

    for (j =0; j < p;j++){
      for (k=0; k < p; k++){
	W[k*p + j] = 0.0;
	for (i=0; i < n; i++){
	  W[k*p + j]+=  weights[i]*X[j*n +i]*X[k*n + i];
	}
      }
    }
    if (!Choleski_inverse(W, XTX, work, p,1)){
      
      for (i =0; i < p; i++){
	se_estimates[i] = RMSEw*sqrt(XTX[i*p + i]);
      }
    } else {
      printf("Singular matrix in SE inverse: Method 4\n");
      
    }


    if (varcov != NULL)
      for (i = 0; i < p; i++)
	for (j = i; j < p; j++)
	  varcov[j*p + i] =  RMSEw*RMSEw*XTX[j*p + i];
  } else {

    scale = med_abs(resids,n)/0.6745;
    
    residSE[0] =  scale;
    
    /* compute most of what we will need to do each of the different standard error methods */
    for (i =0; i < n; i++){
      sumpsi2+= PsiFn(resids[i]/scale,k1,2)*PsiFn(resids[i]/scale,k1,2); 
      /* sumpsi += psi_huber(resids[i]/scale,k1,2); */
      sumderivpsi+= PsiFn(resids[i]/scale,k1,1);
    }
    
    m = (sumderivpsi/(double) n);

    for (i = 0; i < n; i++){
      varderivpsi+=(PsiFn(resids[i]/scale,k1,1) - m)*(PsiFn(resids[i]/scale,k1,1) - m);
    }
    varderivpsi/=(double)(n);

    /*    Kappa = 1.0 + (double)p/(double)n * (1.0-m)/(m); */


    Kappa = 1.0 + ((double)p/(double)n) *varderivpsi/(m*m);

    
    /* prepare XtX and W matrices */
  
    for (j =0; j < p;j++){
      for (k=0; k < p; k++){
	for (i = 0; i < n; i++){
	  XTX[k*p+j]+=  X[j*n +i]*X[k*n + i];
	  W[k*p + j]+=  PsiFn(resids[i]/scale,k1,1)*X[j*n +i]*X[k*n + i];	
	}
      }
    }

    if (method==1) {
      Kappa = Kappa*Kappa;
      vs = scale*scale*sumpsi2/(double)(n-p);
      Kappa = Kappa*vs/(m*m);
      RLM_SE_Method_1(Kappa, XTX, p, se_estimates,varcov);
    } else if (method==2){
      vs = scale*scale*sumpsi2/(double)(n-p);
      Kappa = Kappa*vs/m;
      RLM_SE_Method_2(Kappa, W, p, se_estimates,varcov);
      
    } else if (method==3){
      
      vs = scale*scale*sumpsi2/(double)(n-p);
      Kappa = 1.0/Kappa*vs;
      i = RLM_SE_Method_3(Kappa, XTX, W, p, se_estimates,varcov);
      if (i){
	for (i=0; i <n; i++){
	  printf("%2.1f ", PsiFn(resids[i]/scale,k1,1));
	} 
	printf("\n");
      }
    } 
  }
  Free(work);
  Free(XTX);
  Free(W);
}

