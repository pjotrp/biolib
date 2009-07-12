/*********************************************************************
 **
 ** file: plmd.c
 **
 ** Aim: implement PLM-d. A variation of the PLM methodology
 **
 ** Copyright (C) 2007-2008 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bmb@bmbolstad.com>
 ** 
 ** created on: Dec 3, 2007
 **
 **
 ** History:
 ** Dec 3, 2007 - Initial version. 
 ** Jan 21, 2008 - improve detect_split_probe
 ** Jan 23-24, 2008 - improve design matrix code
 **                
 **
 **
 **
 **
 *********************************************************************/

/*********************************************************************
 **
 ** Background: Suppose that arrays can be grouped together by some
 **             sort of blocking variable with levels m=1,...,M 
 **
 ** standard PLM: y_ij = beta_j + alpha_i + epsilon_ij            
 **
 ** where beta_j are the expression values and 
 ** alpha_i are the probe effects (constrained to sum to zero to make the model identifiable
 **
 ** Modfied PLM: (discussed in section 2.4.6 of the affyPLM vignette)
 **
 ** y_ij = beta_j + alpha_im + e_ij
 ** 
 ** which has a separate set of probe effects estimated for each block. 
 ** (in the affyPLM setup for each m, sum_i=1,..,I alpha_im =0)
 **
 ** PLM-d tries to be a hybrid approach between these two. In particular
 ** fit unified probe effects across blocks except in situations where there 
 ** seems to be evidence that the probe effect differs across blocks.
 **
 ** In other words, fit the model
 **
 ** y_ij = beta_j + alpha_im + e_ij
 **
 ** with alpha_i = alpha_i1 = alpha_i2 = ... = alpha_im  (except where there is evidence to the contrary)
 ** and sum_{i,m} alpha_im = 0
 **
 ** For instance suppose that the we have 6 arrays, with the first 3 in m=1 and the last 3 in m=2
 **
 ** Furthermore suppose that we have a probeset with 8 probes. 
 **
 ** Let's assume that the second and the eighth probes are known to behave differently between the blocks
 ** (later we discuss how this will be decided in the PLM-d procedure)
 **
 ** then the model we would fit would require us to estimate
 **
 ** beta_1, ..., beta_6  (the chip effects/aka expression level)
 **
 ** alpha_1, 
 ** alpha_21, alpha_22, 
 ** alpha_3
 ** alpha_4
 ** alpha_5
 ** alpha_6
 ** alpha_7
 ** alpha_81, alpha_82
 **
 ** In R we would generate the model matrix like this
 ** 
 **
 ** chips <- as.factor(rep(c(1,2,3,4,5,6),c(8,8,8,8,8,8)))
 ** probes <- rep(c(1,2,3,4,5,6,7,8),6)
 **
 ** probes[24 + c(2,10,18)] <- 9
 ** probes[24 + c(8,16,24)] <- 10
 ** probes <- as.factor(probes)
 **
 ** let X_beta = model.matrix(~ -1 + chips)
 **
 ** So  X_beta is 
 **
 **
       1      0      0      0      0      0
       1      0      0      0      0      0
       1      0      0      0      0      0
       1      0      0      0      0      0
       1      0      0      0      0      0
       1      0      0      0      0      0
       1      0      0      0      0      0
       1      0      0      0      0      0
       0      1      0      0      0      0
       0      1      0      0      0      0
       0      1      0      0      0      0
       0      1      0      0      0      0
       0      1      0      0      0      0
       0      1      0      0      0      0
       0      1      0      0      0      0
       0      1      0      0      0      0
       0      0      1      0      0      0
       0      0      1      0      0      0
       0      0      1      0      0      0
       0      0      1      0      0      0
       0      0      1      0      0      0 
       0      0      1      0      0      0
       0      0      1      0      0      0 
       0      0      1      0      0      0 
       0      0      0      1      0      0
       0      0      0      1      0      0
       0      0      0      1      0      0
       0      0      0      1      0      0
       0      0      0      1      0      0
       0      0      0      1      0      0
       0      0      0      1      0      0
       0      0      0      1      0      0
       0      0      0      0      1      0
       0      0      0      0      1      0
       0      0      0      0      1      0
       0      0      0      0      1      0
       0      0      0      0      1      0
       0      0      0      0      1      0
       0      0      0      0      1      0
       0      0      0      0      1      0
       0      0      0      0      0      1
       0      0      0      0      0      1
       0      0      0      0      0      1
       0      0      0      0      0      1
       0      0      0      0      0      1
       0      0      0      0      0      1
       0      0      0      0      0      1
       0      0      0      0      0      1


 ** let X_alpha = model.matrix(~ -1 + probes)%*%contr.sum(10)
 **
 ** So X alpha is
 **
     1    0    0    0    0    0    0    0    0
     0    1    0    0    0    0    0    0    0
     0    0    1    0    0    0    0    0    0
     0    0    0    1    0    0    0    0    0
     0    0    0    0    1    0    0    0    0
     0    0    0    0    0    1    0    0    0
     0    0    0    0    0    0    1    0    0
     0    0    0    0    0    0    0    1    0
     1    0    0    0    0    0    0    0    0
     0    1    0    0    0    0    0    0    0
     0    0    1    0    0    0    0    0    0
     0    0    0    1    0    0    0    0    0
     0    0    0    0    1    0    0    0    0
     0    0    0    0    0    1    0    0    0
     0    0    0    0    0    0    1    0    0
     0    0    0    0    0    0    0    1    0
     1    0    0    0    0    0    0    0    0
     0    1    0    0    0    0    0    0    0
     0    0    1    0    0    0    0    0    0
     0    0    0    1    0    0    0    0    0
     0    0    0    0    1    0    0    0    0
     0    0    0    0    0    1    0    0    0
     0    0    0    0    0    0    1    0    0
     0    0    0    0    0    0    0    1    0
     1    0    0    0    0    0    0    0    0
     0    0    0    0    0    0    0    0    1
     0    0    1    0    0    0    0    0    0
     0    0    0    1    0    0    0    0    0
     0    0    0    0    1    0    0    0    0
     0    0    0    0    0    1    0    0    0
     0    0    0    0    0    0    1    0    0
    -1   -1   -1   -1   -1   -1   -1   -1   -1
     1    0    0    0    0    0    0    0    0
     0    0    0    0    0    0    0    0    1
     0    0    1    0    0    0    0    0    0
     0    0    0    1    0    0    0    0    0
     0    0    0    0    1    0    0    0    0
     0    0    0    0    0    1    0    0    0 
     0    0    0    0    0    0    1    0    0
    -1   -1   -1   -1   -1   -1   -1   -1   -1
     1    0    0    0    0    0    0    0    0
     0    0    0    0    0    0    0    0    1
     0    0    1    0    0    0    0    0    0
     0    0    0    1    0    0    0    0    0
     0    0    0    0    1    0    0    0    0
     0    0    0    0    0    1    0    0    0
     0    0    0    0    0    0    1    0    0
    -1   -1   -1   -1   -1   -1   -1   -1   -1
 **
 **
 **
 ** X = [X_beta X_alpha]
 **
 ** Let B = [beta_1 beta_2 beta_3 beta_4 beta_5 beta_6 alpha_1, alpha_21, alpha_22, alpha_3, alpha_4, alpha_5, alpha_6, alpha_7, alpha_81]'
 **
 ** So the model can be expressed as
 **
 ** Y = XB + E
 **
 ** The PLM-d procedure is as follows
 **
 ** 1) use the ordinary PLM procedure (fitting the model y_ij = beta_j + alpha_i + epsilonij to get initial estimates
 ** 2) Examine the residuals, find probes where the residuals appear to be related to blocking variable
 **    using a (robustified) one-way anova. Choose the probe which has the most association with blocking variable if there is one. Else stop.
 ** 3) Fit new model (using robust regression) where we include separate block specific probe effects for chosen variable
 ** 4) Examine residuals for newly fitted model. Look at relationship between residuals and probes which have not been
 **    divided between block groups. Using (robustified) one-way anova choose probe which has the most significant associtiaton with blocking variable if there
 **    is one. If probe chosen return to 3. otherwise stop.
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

#include "plmd.h"

#include <R_ext/Rdynload.h>
#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*********************************************************************
 **
 ** static double rho_huber(double u, double k)
 **
 ** double u - scaled observation
 ** double k - parameter
 **
 ** Computes huber rho function. Note that by definition here will need a factor of
 ** 2 to multiply result in plmd_split_test. However, definition here
 ** is consistent with the psi_huber in psi_fns.c
 **
 ********************************************************************/

static double rho_huber(double u, double k){
  
  if (fabs(u) <= k){
    return u*u/2.0;
  } else {
    return k*(fabs(u) - k/2.0);
  }
}


/*********************************************************************
 **
 ** static double plmd_split_test(double *values, int length,  int ngroups, int *grouplabels)
 **
 ** double *values - residual values (scaled so scale = 1.0)
 ** int length - length of values (and also grouplabels)
 ** int ngroups - number of different groups into which values are divided into
 ** int *grouplabels - labels for each value in values indicating which group observation
 **                    belongs in. Should be a value 0,....,ngroups-1
 **
 ** A robust LLRT (log likelihood ratio test) is used to determine if there
 ** is evidence that the mean differs between groups.
 **
 ** This function computes a test statistic that is approximately
 ** chisq with ngroups-1 df under the null hypothesis
 **
 ********************************************************************/


static double plmd_split_test(double *values, int length,  int ngroups, int *grouplabels){

  /* Model 1: NULL model (ie mean model) */
  /* Model 2: Basically a robust 1-way ANOVA */
  
  double *X_1, *X_2;  /* design models */

  double *resid_1, *resid_2;
  double *weights_1, *weights_2;
  double *beta_1, *beta_2;

  double scale_1, scale_2;

  double T1, T2, TL;
  double Xi, ave_deriv_psi, ave_psi_sq;
  int i;

  /* Allocating space */
  X_1 = Calloc(length, double);
  X_2 = Calloc(ngroups*length, double);
  
  resid_1 = Calloc(length, double);
  resid_2 = Calloc(length, double);

  weights_1 = Calloc(length, double);
  weights_2 = Calloc(length, double);

  beta_1 = Calloc(1,double);
  beta_2 = Calloc(ngroups,double);
  
  /* initializing design matrices */

  for (i = 0; i < length; i++){
    X_2[length*grouplabels[i]  + i] = 1.0;
    X_1[i] = 1.0;
  }


  /* Fitting the models */
  rlm_fit(X_1, values, length, 1, beta_1, resid_1, weights_1, psi_huber, 1.345, 20, 0);
  rlm_fit(X_2, values, length, ngroups, beta_2, resid_2, weights_2, psi_huber, 1.345, 20, 0);

  scale_1 = 1.0; //med_abs(resid_1, length)/0.6745;
  scale_2 = med_abs(resid_2, length)/0.6745;
  
  T1 = 0.0;
  T2 = 0.0;
  TL = 0.0;
  ave_deriv_psi = 0.0;
  ave_psi_sq = 0.0;

  for (i = 0; i < length; i++){
    T1+= rho_huber(resid_1[i]/scale_1, 1.345);
    T2+= rho_huber(resid_2[i]/scale_1, 1.345);

    ave_deriv_psi += psi_huber(resid_2[i]/scale_1, 1.345, 1);
    ave_psi_sq += psi_huber(resid_2[i]/scale_2, 1.345, 2)*psi_huber(resid_2[i]/scale_2, 1.345, 2);
  }
  ave_deriv_psi/=(double)length;
  ave_psi_sq/=(double)length;
  
  Xi = ave_deriv_psi/ave_psi_sq;

  TL = T1 - T2;

  /* check that we are not negative due to say numeric imprecession etc) */
  if (TL < 0.0){
    TL = 0.0;
  }


  /*  Rprintf("%f %f %f %f\n", T1, T2, ave_deriv_psi, ave_psi_sq); */

  /* De-allocate space */
  Free(X_1);
  Free(X_2);
  Free(resid_1);
  Free(resid_2);
  Free(weights_1);
  Free(weights_2);
  Free(beta_1);
  Free(beta_2);

  return 2*Xi*TL;

}


void R_split_test(double *values, int *length,  int *ngroups, int *grouplabels, double *result){
  
  *result = plmd_split_test(values, *length, *ngroups, grouplabels);

}


/*********************************************************************
 **
 ** static int plmd_detect_split_probe(double *residuals, int y_rows, int y_cols, int ngroups, int *grouplabels, int *was_split)
 **
 ** double *residuals - a matrix of residuals from a robust PLM (or PLM-d) fit.
 ** int y_rows - number of rows in matrix (corresponds to number of probes)
 ** int y_cols - number of cols in matrix (corresponds to number of arrays)
 ** int ngroups - number of groups into which the arrays may be divided
 ** int *grouplabels - a label for each column assigning it to a group. Values should be in 0, ..., ngroups -1
 ** int *was_split - was a probe previously split (if so then do not need to split it again). vector of
 **                  0, 1 values of length y_rows
 **
 ** This function determines which (if any) of the currently unsplit probes 
 ** should be split based on computing the LLRT for each probe.
 **
 ** returns 0, ..., y_rows -1 if a probe is chosen for splitting 
 ** returns -1 if no suitable probe is found.
 **
 **
 ********************************************************************/

static int plmd_detect_split_probe(double *residuals, int y_rows, int y_cols, int ngroups, int *grouplabels, int *was_split){

  int i,j;
  double *split_statistic = Calloc(y_rows,double);

  double *cur_row = Calloc(y_cols, double);

  double chisq_q;
  double max_split_statistic;
  double which_max;

  double scale;


  scale =  med_abs(residuals, y_rows*y_cols)/0.6745;

  /* Check all unsplit probes */
  for (i = 0; i < y_rows; i++){
    if (!was_split[i]){
      for (j =0; j < y_cols; j++){
	cur_row[j] = residuals[j*y_rows + i]/scale;
      }
    
      split_statistic[i] = plmd_split_test(cur_row, y_cols, ngroups, grouplabels);
    } else {
      split_statistic[i] = 0.0;
    }
  }
  
  /* find probe with maximum split_statistic */

  which_max = -1;
  max_split_statistic = 0.0;

  for (i= 0; i < y_rows; i++){
    if (max_split_statistic < split_statistic[i]){
      which_max = i;
      max_split_statistic = split_statistic[i];
    }
  }



  /* Check to see if we have a significant split_statistic */
  /* test at 0.1% significance level */
  if (which_max > -1){
    
    chisq_q = qchisq(0.999,ngroups-1,1,0);
    
    if (chisq_q >  max_split_statistic){
      which_max = -1;
    }
  }
  
  Free(cur_row);
  Free(split_statistic);
  
  return which_max;


}

/*********************************************************************
 **
 ** double *plmd_get_design_matrix(int y_rows, int y_cols, int ngroups, int *grouplabels,int *was_split,int *X_rows,int *X_cols)
 **
 ** int y_rows - number of probes
 ** int y_cols - number of arrays
 ** int ngroups - number of groups
 ** int *grouplabels - a label in 0, ..., ngroups-1 for each array (length y_cols)
 ** int *was_split - a vector of 0,1 values length y_rows indicating whether or not a given probe was split
 ** int *X_rows - on return contains the number of rows in the design matrix
 ** int *X_cols - on return contains the number of columns in the design matrix
 **
 ** returns the design matrix for the model described by its parameters
 ** (see the description above for how the design matrix should look)
 ** Note that the calling function will be responsible for deallocating
 ** the memory allocated for the design matrix
 **
 ********************************************************************/

double *plmd_get_design_matrix(int y_rows, int y_cols, int ngroups, int *grouplabels,int *was_split,int *X_rows,int *X_cols){

  double *X;
  
  int i,j;
  int probe;

  int num_splits = 0;

  int cur_group;
  int cur_col;
  int col;

  /* count the number of probes that have been split */

  for (i=0; i < y_rows; i++){
    num_splits +=was_split[i];
  }

  
  /* Number of columns in design_matrix 

     y_cols - number of chips
     
     y_rows - 1 + (ngroups -1)*num_splits



   */

  *X_rows = (y_rows*y_cols);
  *X_cols = (y_cols + y_rows - 1 + (ngroups -1)*num_splits);


  X = Calloc((y_rows*y_cols)*(y_cols + y_rows - 1 + (ngroups -1)*num_splits),double);



  /* Setting the X_beta part of the matrix */

  
  for (j = 0; j < y_cols; j++){
    for (i = j*y_rows; i < (j+1)*y_rows; i++){
      X[j*(y_rows*y_cols) + i] = 1.0;
    }
  }
  
  /* Now the X_alpha part of the matrix */

  cur_col = y_cols;
  for (probe = 0; probe < y_rows-1; probe++){

    if (was_split[probe]){
      /*Split probe so need ngroups columns set up */
      for (j = 0; j < y_cols; j++){
	cur_group = grouplabels[j];
	i = j*y_rows + probe;
	X[(cur_col + cur_group)*(y_rows*y_cols) + i] = 1.0;
      }
      cur_col+= ngroups;
    } else {
      /* just a single column */
      for (i=probe; i < y_cols*y_rows; i=i+y_rows){
	X[cur_col*(y_rows*y_cols) + i] = 1.0;
      }	
      cur_col++;
    }
  }
  /* Last probe */
  
  if (was_split[probe]){
    for (j = 0; j < y_cols; j++){
      cur_group = grouplabels[j];
      if (cur_group == ngroups -1){
	i = j*y_rows + probe;
	for (col = y_cols; col < y_cols + y_rows - 1 + (ngroups -1)*num_splits; col++){
	  X[col*(y_rows*y_cols) + i] = -1.0;
	}     
      } else {
	i = j*y_rows + probe;
	X[(cur_col + cur_group)*(y_rows*y_cols) + i] = 1.0;
      }
    }
  } else {
    for (col = y_cols; col < y_cols + y_rows - 1 + (ngroups -1)*num_splits; col++){
       for (i=probe; i < y_cols*y_rows; i=i+y_rows){
	 X[col*(y_rows*y_cols) + i] = -1.0;
       }	
    }
  }

  return X;
}


void R_test_get_design_matrix(int *yrows, int *ycols){

  int i, j;

  int ngroups = 1;
  int *grouplabels = Calloc(*ycols, int);
  int *was_split = Calloc(*yrows, int);
  
  int num_splits;
  int y_rows = *yrows;
  int y_cols = *ycols;


  double *X;
  
  int X_rows;
  int X_cols;


  X = plmd_get_design_matrix(y_rows, y_cols, ngroups, grouplabels,was_split, &X_rows, &X_cols);
    
  
  for (i=0; i < y_rows*y_cols; i++){
    for (j = 0; j < y_rows + y_cols -1; j++){
      Rprintf("%2.2f ",X[j*(y_rows*y_cols) + i]);
    }
    Rprintf("\n");
  }


  Free(X);


  Rprintf("\n");

  ngroups = 2;

  for (j = 0; j < y_cols/2; j++){
    grouplabels[j] = 1;
  }

  num_splits = 1;
  was_split[0] =1;

  X = plmd_get_design_matrix(y_rows, y_cols, ngroups, grouplabels,was_split, &X_rows, &X_cols);
    
  
  for (i=0; i < y_rows*y_cols; i++){
    for (j = 0; j < y_rows + y_cols -1 + (ngroups -1)*num_splits; j++){
      Rprintf("%2.2f ",X[j*(y_rows*y_cols) + i]);
    }
    Rprintf("\n");
  }


  Free(X);


  Rprintf("\n");

  ngroups = 2;

  for (j = 0; j < y_cols/2; j++){
    grouplabels[j] = 1;
  }

  num_splits = 2;
  was_split[0] =1;
  was_split[y_rows-1] =1;
  
  X = plmd_get_design_matrix(y_rows, y_cols, ngroups, grouplabels,was_split, &X_rows, &X_cols);

 
  for (i=0; i < y_rows*y_cols; i++){
    for (j = 0; j < y_rows + y_cols -1 + (ngroups -1)*num_splits; j++){
      Rprintf("%2.2f ",X[j*(y_rows*y_cols) + i]);
    }
    Rprintf("\n");
  }
  
  Free(grouplabels);
}

  


/*********************************************************************
 **
 ** void plmd_fit(double *y, int y_rows, int y_cols, int ngroups, int *grouplabels, int *was_split,
	      double *out_beta, double *out_resids, double *out_weights,
	      double (* PsiFn)(double, double, int), double psi_k,int max_iter)
 **
 ** double *y - matrix of observations (probes in rows, arrays in columns)
 ** int y_rows - number of probes
 ** int y_cols - number of arrays
 ** int ngroups - number of groups into whicharrays may be divided
 ** int *grouplabels - assign each array to a group. values should be in 0, ... ngroups -1. 
 **                    length of grouplabels is y_cols
 ** int *was_split - on output 1 indicates separate probe effects fit for each group of arrays
 **                            0 indicates a unified probe effect fit across all arrays
 ** double *out_beta - on output contains parameter estimates. Note that this space should be of 
 **                 length y_cols + y_rows*ngroups -1, but not all the space may be used
 **                 the first y_cols values are the chip effect/expression summary values.
 **                 the remaining values are the probe effects. With these exact break down
 **                 of how these are assigned to probes requires the information in "was_split"
 ** double *out_resids - on output contains fitted residuals (should be of size y_rows*y_cols
 ** double *out_weights - on output contains weights used for each observation (should be of size y_rows*y_cols)
 ** double (* PsiFn)(double, double, int) - psi function for M-estimation
 ** double psi_k - parameter for PsiFn
 ** int max_iter - maximum number of iterations in any iteratively reweighted least squares procedure
 **
 ** Fits PLM-d model (Probe Level Model - Dynamic). The idea is to determine dynamically which probes seem to
 ** systematically vary with respect to the grouplabel variable. When such a probe is found, a model is fit which 
 ** incorporates different probe effects for each group. Otherwise a unified probe effect is fit across all arrays.
 **
 ** In the case that no such probes are found the fitted model is a standard PLM fit.
 **
 ********************************************************************/


void plmd_fit(double *y, int y_rows, int y_cols, int ngroups, int *grouplabels, int *was_split,
	      double *out_beta, double *out_resids, double *out_weights,
	      double (* PsiFn)(double, double, int), double psi_k,int max_iter){

  int initialized = 0;
 
  int split_probe = -1;


  double *X;

  int X_rows;
  int X_cols;


  /* Initially nothing is split */
  memset(was_split, 0 , y_rows*sizeof(int));


  /* Start out with standard PLM fit */
  rlm_fit_anova(y, y_rows, y_cols, out_beta, out_resids, out_weights,
                PsiFn, psi_k, max_iter, initialized);



  /* Figure out which if any probes to split by group label */
  /* Choose the most significant of these and fit new model */
  /* repeat until no more splits */
  
  do {
    split_probe = plmd_detect_split_probe(out_resids, y_rows, y_cols, ngroups, grouplabels, was_split);
    /*   Rprintf("Splitting %d\n",split_probe); */
    if (split_probe != -1){
      was_split[split_probe] = 1;
      X = plmd_get_design_matrix(y_rows, y_cols, ngroups, grouplabels, was_split,&X_rows, &X_cols);
      

      rlm_fit(X,y, X_rows, X_cols, out_beta, out_resids, out_weights,
                PsiFn, psi_k, max_iter, initialized);
    
      Free(X);
    }
  } while (split_probe != -1);
  



}



void plmd_fit_R(double *y, int *rows, int *cols, int *ngroups, int *grouplabels, double *out_beta, double *out_resids, double *out_weights){

  int *was_split = Calloc(*rows,int);
      
  plmd_fit(y, *rows, *cols, *ngroups, grouplabels, was_split, 
	   out_beta, out_resids,out_weights,
	   psi_huber,1.345, 20);


  Free(was_split);
  
}




