/*********************************************************************
 **
 ** file: matrix_functions.c
 **
 ** Aim: This is where some matrix manipulation functions go.
 **
 ** Copyright (C) 2003-2004 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bolstad@stat.berkeley.edu>
 ** 
 ** created on: June 22, 2004
 **
 ** History: 
 ** June 22, 2004 - Initial version
 ** Mar 1, 2006 - change commenting style to ansi C style
 ** Aug 28, 2006 - change moduleCdynload to R_moduleCdynload
 ** Sept 26, 2006 - remove R_moduleCdynload. SHould fix windows build problems.
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

/********************************************************************
 **
 ** two static global variables to define if lapack library loaded
 ** and which library to use. 0 is LINPACK, 1 is LAPACK
 **
 ** Kind of bad, but will do it anyway
 **
 ********************************************************************/

static int Lapack_initialized = 0;

static int use_lapack = 1;

/*********************************************************************
 **
 ** static void Lapack_Init(void)
 **
 ** this function loads the Lapack library if it has not already been
 ** loaded and sets the use_lapack variable to 1 so that LAPACK
 ** is used (for Choleski and SVD routines)
 **
 **
 **
 ********************************************************************/

void Lapack_Init(void)
{
  int res = 1; /* R_moduleCdynload("lapack", 0, 1); */
    Lapack_initialized = -1;
    if(!res) return;

    /* Initializing LAPACK */
    use_lapack = 1;
    Lapack_initialized = 1;
    return;
}


/********************************************************************
 **
 ** external declarations for Choleski routines (LINPACK)
 **
 **
 *******************************************************************/

extern int dpofa_(double *x, int *lda, int *n, int *j);
extern int dpodi_(double *x, int *lda, int *n, double *d, int *j);


/********************************************************************
 **
 ** external declarations for Choleski routines (LAPACK)
 **
 **
 *******************************************************************/

extern int dpotrf_(const char *uplo, const int *n, double* a, const int *lda, int *info);
extern int dpotri_(const char *uplo, const int *n, double* a, const int *lda, int *info);


/*****************************************************************
 * svd routine - LINPACK
 *****************************************************************/

extern int dsvdc_(double *x, int *ldx, int *n, int *p, double *s, double *e, double *u, int *ldu,
		 double *v, int *ldv, double *work, int *job, int *info);

/*****************************************************************
 * svd routine - LAPACK
 *****************************************************************/

extern int dgesdd_(const char *jobz,
                      const int *m, const int *n,
                      double *a, const int *lda, double *s,
                      double *u, const int *ldu,
                      double *vt, const int *ldvt,
                      double *work, const int *lwork, int *iwork, int *info);







/*********************************************************************
 **
 ** int Choleski_decompose(double *X, double *L, int n)
 **
 ** double *X - a square matrix 
 ** double *L - space already allocated to store Cholesky decomposition
 ** int n - matrix dimension
 ** int lapack - if 0 use LINPACK otherwise LAPACK
 **
 ** RETURNS integer code indicating success or failure 0 means no error, 
 **      non zero indicates failure ie not positive definite
 **
 ** this function choleski decomposes a positive definite symmetric matrix,
 ** on output L will contain the Choleski decomposition in the upper triangle
 **
 **
 *********************************************************************/


static int Choleski_decompose(double *X, double *L, int n, int lapack){
  int i,j,error_code;
  char upper = 'U';

  for (i=0; i < n; i++){
    for (j=0; j < n; j++){
      if (i > j)
	L[j*n+i] = 0.0;
      else {
	L[j*n+i] = X[j*n + i];
      }
    }
  }
  if (!lapack){
    dpofa_(L,&n,&n,&error_code);
  } else {
    dpotrf_(&upper,&n,L,&n,&error_code);
  }
    


  return error_code;
}

/***********************************************************************
 **
 ** int Choleski_2_inverse(double *X, double *Xinv, int n)
 **
 ** double *X - matrix containing choleski decomposition in upper triangle
 ** double *Xinv - on output will contain the inverse
 ** int n - dimension of matrix
 ** int upperonly - if non zero return only the upper triangle of the inverse.
 ** int lapack - use LINPACK if 0 otherwise LAPACK
 **
 ** RETURNS integer code, indicating success 0  or error (non zero) 
 **
 ** this function uses the choleski decomposition of a 
 ** matrix to compute the inverse of a matrix.
 ** typically it would be used in conjunction with the choleski_decompose
 ** function above.
 **
 **
 **********************************************************************/

static int Choleski_2_inverse(double *X, double *Xinv, int n,int upperonly, int lapack){
  
  int i,j ,error_code=0,inverseonly;
  double d =0.0;
  char upper = 'U';
  
  for (i=0; i < n; i++){ 
    /* check for a zero or close to zero diagonal element */ 
    if(fabs(X[i*n+ i]) < 1e-06){
      error_code = 1;
      return error_code;
    }

    for (j=i; j < n; j++){
      Xinv[j*n + i] = X[j*n + i];
    }
  }

  inverseonly = 1;
  if (!lapack){
    dpodi_(Xinv,&n,&n,&d,&inverseonly);
  } else {
    dpotri_(&upper,&n,Xinv,&n,&error_code);
  }
  if (!upperonly){
    for (i=0; i < n; i++){
      for (j=0; j <= i-1; j++){
	Xinv[j*n+i] = Xinv[i*n+j];
      }
    }
  }
  return error_code;

}


/***********************************************************************
 **
 ** int Choleski_inverse(double *X, double *Xinv, double *work, int n)
 **
 ** double *X - matrix containing choleski decomposition in upper triangle
 ** double *Xinv - on output will contain the inverse
 ** double *work - working space n*n dimension
 ** int n - dimension of matrix
 ** int upperonly - if non zero return only upper triangle of inverse.
 **
 ** RETURNS integer code, indicating success 0  or error (non zero) 
 **
 ** This function will compute the inverse of a positive definite symmetric
 ** matrix using choleski decomposition.
 **
 **********************************************************************/

int Choleski_inverse(double *X, double *Xinv, double *work, int n, int upperonly){

  int error_code;
  
  error_code = Choleski_decompose(X, work, n,use_lapack);
  if (!error_code){
    error_code = Choleski_2_inverse(work, Xinv, n,upperonly,use_lapack);
  }
  return error_code;

}



/***************************************************************
 **
 ** int SVD_compute()
 **
 **
 ** Computes the singular value decomposition of a matrix. Current
 ** implemtnation uses a linpack routine, but this will later be transitioned
 ** to a lapack routine (which is faster)
 **
 ***************************************************************/

static int SVD_compute(double *X, int n, double *s, double *u, double *v,int lapack){
  
  int i,j, error_code;
  int lwork = 7*n*n + 4*n;
  int job = 21;
  char jobz = 'A';
  double *Xcopy= Calloc(n*n,double);              /* Calloc(n*n,double); */
  double *e =    Calloc(n,double);                /* Calloc(n,double); */
  double *work =  Calloc(n,double);               /* Calloc(n,double); */
  double *work2 =  Calloc(lwork,double);
  int *iwork = Calloc(8*n,int);


  for (i=0; i < n; i++){
    for (j=0; j < n; j++){
      Xcopy[j*n + i] = X[j*n+i];
    }
  }
  if (!lapack){
    dsvdc_(Xcopy,&n,&n,&n,s,e,u,&n,v,&n,work,&job,&error_code);
  } else {
    dgesdd_(&jobz,&n,&n,Xcopy,&n,s,u,&n,v,&n,work2,&lwork,iwork,&error_code);
  }
    

  Free(iwork);
  Free(work2);
  Free(work);
  Free(e);
  Free(Xcopy);
  
  return error_code;

}

/***************************************************************
 **
 ** int SVD_2_inverse(double *Xinv, int n, double *s, double *u, double *v,int lapack)
 **
 ** double *Xinv - on exit contains the inverse
 ** int n - Xinv is n by n
 ** double *s - SVD components length n
 ** double *u - SVD components n by n
 ** double *v - SVD components n by n
 ** int lapack - non zero if the decomposition was done by a LAPACK routine (implies v is the transpose)
 **
 ** given a Singular value decomposition of a matrix compute
 ** the generalized inverse.
 **
 ***************************************************************/

static int SVD_2_inverse(double *Xinv, int n, double *s, double *u, double *v,int lapack){
  double tolerance = 1e-7; /* 1.490116e-08; */
  int i,j,k;
  int nonzero =n;
  
  
  for (i = 0; i < n; i++){
    if (s[i] < tolerance*s[0]){
      nonzero = i;
      /* printf("nonzero %d",i); */
      break;
    }
  }


  /* for all columns where $d is not to small do */
  /*  svdu$v %*% (t(svdu$u)* 1/svdu$d); */
    
  for (i = 0; i < n; i++){
    for (j = 0; j < nonzero; j++){
      u[j*n + i] = u[j*n+i] * 1.0/s[j];
    }
  }
  if (!lapack){
    for (i = 0; i < n; i++){
      for (j = 0; j < n; j++){
	Xinv[j*n+i] = 0.0;
	for (k=0; k < nonzero; k++){
	  Xinv[j*n+i]+= v[k*n+i] * u[k*n+j];
	}
      }
    }
  } else {
    /* lapack so v is transposed */
    for (i = 0; i < n; i++){
      for (j = 0; j < n; j++){
	Xinv[j*n+i] = 0.0;
	for (k=0; k < nonzero; k++){
	  Xinv[j*n+i]+= v[i*n+k] * u[k*n+j];
	}
      }
    }
  }



  return 0;
}


/***************************************************************
 **
 ** int SVD_inverse(double *X, double *Xinv, int n)
 **
 ** double *X -  the matrix to be inverted
 ** double *Xinv - on exit contains inverse
 ** int n - X and Xinv are n by n
 **
 **
 ** given an n by n matrix compute its inverse by singular value decomposition
 ** this is particularly useful when dealling with singular or near singular
 ** matrices since if the regular inverse can not be computed a generalized
 ** inverse will be returned instead, rather than erroneous results.
 **
 ** Note that  we will use linpack routine for SVD at some point this will
 ** be transitioned to a lapack routine. (This has now been done).
 **
 **
 **
 **************************************************************/

int SVD_inverse(double *X, double *Xinv, int n){

  int error_code=0;
  double *s = Calloc(n+1,double);
  double *v = Calloc(n*n,double);
  double *u = Calloc(n*n,double);

  error_code = SVD_compute(X, n, s, u, v,use_lapack);
  SVD_2_inverse(Xinv,n, s, u, v,use_lapack);

  return error_code;

  Free(s);
  Free(v);
  Free(u);
}


/* void R_SVD_compute(double *X, int *n, double *s, double *u, double *v){
  SVD_compute(X, *n,s,u, v);
  } */


void R_SVD_inverse(double *X, double *Xinv, int *n){
  SVD_inverse(X, Xinv,*n);
}




