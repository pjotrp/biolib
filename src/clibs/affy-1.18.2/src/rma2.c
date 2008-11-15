/************************************************************************
 **
 ** file: rma.c
 **
 ** Copyright (C) 2002 - 2007   B. M. Bolstad
 **
 ** created by: B. M. Bolstad   <bmb@bmbolstad.com>
 ** created on: June 26, 2002
 **
 ** last modified: January 6, 2003
 ** 
 ** last modified: Apr 4, 2003
 **
 ** License: GPL V2 or later (same as the rest of the Affy package)
 **
 ** version 1.1 - Initial release to affy package
 **
 ** Version History (LEADING UP TO AND INCLUDING AFFYEXTENSIONS)
 ** 0.1 - Initial version released on July 14, 2002. Implements median
 **       polish RMA method with 
 ** 0.2 - background implemented in c with the density estimation still carried
 **       out by the R function density()
 ** 0.25 - correct background implementation, version 0.2 is broken.
 **        background is implemented in rma_background.c
 ** 0.30 - Have a copy and none copy path. ie we can either work inplace or on
 **        duplicates. the purpose of this is to reduce memory overhea. For 
 **        someone with an interest only in expression estimates this should not be a problem
 ** 
 ** Version History (AFTER INCLUSION INTO AFFY PACKAGE)
 ** 1.1 - Initial inclusion into Affy package, heavy modification to how PM data structure
 **       dealt with.
 **
 ** OLD COMMENTS
 **
 ** a c language implementation of the RMA method as given in the RMA.R file I 
 ** received from Rafael at an earlier point, but assume already had background 
 ** correction to PM's at somepoint (perhaps in the c code) bg will be written in later.
 ** Possibly another background method will be inserted in at this stage. <-- COMMENT DEPRECIATED
 ** 
 ** Note that the normalization code that is used in this algorithm is updated
 ** from that in the affy version 1.1.1 (there will be slight differences in the 
 ** expression values because of this), there is also slight differences in the 
 ** ordering of the results.  <-- THIS COMMENT IS DEPRECIATED. Quantile
 ** normalization updates will happen in the bioconductor cvs.
 **
 ** Ideally and at some later point a more modular approach that can be called 
 ** in a better manner from R than this will be written. This is a quick and 
 ** dirty approach to get something that will run acceptably.in terms of memory 
 ** and speed. From a software engineering viewpoint expect the code to be poorly 
 ** constructed.  <-- SOMEWHAT DEPRECIATED. some work should be done to
 ** clean things up. The user will generally only be dealing with the R 
 ** interface.
 **
 ** Input to the function should be processed from within R
 **
 ** NEW COMMENTS
 **
 ** This is the main c function for implementing the RMA method
 ** it provides c interfaces to be called from R.
 **
 ** Specific Modification History
 **
 ** Note that the qnorm code here will not be the development tree
 ** LG: what do you mean ?
 **
 ** BMB: legacy comment, from when this code was outside affy, in AffyExtensions
 **      and before that as raw c code that was floating around.
 **
 ** Specific Modification History
 ** Nov 2, 2002 - modify so that it will work efficently with affy2
 ** Nov 3, 2002 - More modifications, remove cruft from old version
 ** Nov 4, 2002 - testing, check docs etc
 ** Nov 10,2002 - remove pesky debug printf()
 ** Dec 5, 2002 - add ability to turn background off
 ** Dec 31, 2002 - add ability to change to type 2 background
 ** Jan 2, 2003 - clean up old/incorrect documentation/comments
 **
 ** Dec 26, 2002 - '//' is not a valid way to comment out (and some C compilers complain about it)
 **                (Laurent)
 ** Jan 6, 2003 - fix merging. Note "//" is valid according to the language standards (http://anubis.dkuug.dk/jtc1/sc22/open/n2794/n2794.txt)
 ** Feb 6, 2003 - change some printfs to Rprintfs this will allow the windows users to see some
 **               verbage when running rma
 ** Feb 25, 2003 - try to reduce or eliminate compiler warnings (from gcc -Wall) 
 ** Apr 4, 2003 - fix up so that the number of probes in a probeset is allowed to be more dynamic
 ** Dec 9, 2003 - fix a bug in do_RMA (max_nrows in Calloc)
 ** Mar 6, 2004 - all mallocs/frees are now Calloc/Frees. Removed
 **               the function R_median_polish
 ** Jul 27, 2004 - fix a small memory leak
 ** Aug 4, 2004 - move the "Background correcting" message. 
 ** Nov 8, 2004 - change how things are structured in do_RMA()
 ** Sep 3, 2005 - In extremely high memory usage situations
 **               R was garbage collecting something that shouldn't have
 **               been. This was leading to a seg fault. Fixed by
 **               moving an UNPROTECT.
 ** Nov 9, 2006 - integrate changes suggested/supplied by Paul Gordon (gordonp@ucalgary.ca)
 **               specifically memcpy, caching log(2.0), and partial sorting for median calculation 
 ** Nov 13, 2006 - moved median code to rma_common.c
 ** May 24, 2007 - median_polish code is now from preprocessCore package
 ** Oct 26, 2007 - add verbose flag
 ** Oct 28, 2007 - remove any vestigial references to MM
 ** Mar 31, 2008 - use rma background correction from preprocessCore
 **
 ************************************************************************/


#include "rma_common.h"
#include "rma_background4.h"

#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "preprocessCore_background_stubs.c"
#include "preprocessCore_normalization_stubs.c"
#include "preprocessCore_summarization_stubs.c"



void do_RMA(double *PM, const char **ProbeNames, int *rows, int * cols,double *results,char **outNames,int nps);


/************************************************************************************
 **
 **  void do_RMA(double *PM, char **ProbeNames, int *rows, int * cols)
 **
 ** double *PM - matrix of dimension rows by cols (probes by chips) should already be 
 **              normalized and background corrected.
 ** char **ProbeNames - Probeset names, one for each probe.
 ** int *rows, *cols - dimensions of matrix
 **
 ** perform the multichip averaging. PM should be background corrected and normalized
 **
 ** assumed that Probes are sorted, by ProbeNames, so that we can just look at 
 ** consecutive rows in PM matrix when doing the median polish
 **
 ** each item is then used to create a matrix that is median polished to give
 ** expression estimates.
 **
 ************************************************************************************/

void do_RMA(double *PM, const char **ProbeNames, int *rows, int *cols, double *results, char **outNames, int nps){
  int j = 0;
  int i = 0;
  int k = 0;
  int size;
  const char *first;
  int first_ind;
  int max_nrows = 1000;


  /* buffers of size 200 should be enough. */

  int *cur_rows=Calloc(max_nrows,int);
  int nprobes=0;

  double *cur_exprs = Calloc(*cols,double);
  double *cur_se_exprs = Calloc(*cols,double);
  /* double *OLDPM = NULL; */

  first = ProbeNames[0];
  first_ind = 0;
  i = 0;     /* indexes current probeset */
  j = 0;    /* indexes current row in PM matrix */
  k = 0;    /* indexes current probe in probeset */
  while ( j < *rows){
    if (strcmp(first,ProbeNames[j]) == 0){
      if (k >= max_nrows){
	max_nrows = 2*max_nrows;
	cur_rows = Realloc(cur_rows, max_nrows, int);
      }
      cur_rows[k] = j;
      k++;
      j++;
      
    } else {
      nprobes = k;
      MedianPolish(PM, *rows, *cols, cur_rows, cur_exprs, nprobes, cur_se_exprs);
      for (k =0; k < *cols; k++){
	results[k*nps + i] = cur_exprs[k];
      } 
      size = strlen(first);
      outNames[i] = Calloc(size+1,char);
      strcpy(outNames[i],first);
      i++;
      first = ProbeNames[j];
      k = 0;
    }
  }
  nprobes = k;
  MedianPolish(PM, *rows, *cols, cur_rows, cur_exprs, nprobes, cur_se_exprs);
  for (k =0; k < *cols; k++){
    results[k*nps + i] = cur_exprs[k];
  } 
  size = strlen(first);
  outNames[i] = Calloc(size+1,char);
  strcpy(outNames[i],first);
  
  Free(cur_se_exprs);
  Free(cur_exprs);
  Free(cur_rows);
}

/********************************************************************************************
 **
 ** void rma_c_call(SEXP PMmat, SEXP ProbeNamesVec,SEXP N_probes,SEXP norm_flag)
 **
 ** SEXP PMmat - matrix of Perfect-match values
 ** SEXP ProbeNamesVec - vector containing names of probeset for each probe
 ** SEXP N_probes - number of PM/MM probes on an array
 ** SEXP norm_flag  - non zero for use quantile normalization, 0 for no normalization
 ** SEXP verbose - TRUE/FALSE or 1/0 for be verbose or not
 **
 ** a function to actually carry out the RMA method taking the R objects and manipulating
 ** into C data structures.
 **
 ** this function assumes any sort of background correction was carried out previously
 ** This function carries out the other two steps of the RMA algorithm:
 ** Normalization and Summarization.
 **
 ** In particular the data is quantile normalized and then it is
 ** summarized using median polish
 **
 *******************************************************************************************/

SEXP rma_c_call(SEXP PMmat,  SEXP ProbeNamesVec,SEXP N_probes,SEXP norm_flag, SEXP verbose){
  
  int rows, cols;
  double *outexpr;
  double *PM;
  char **outnames;
  const char **ProbeNames;
  int i,nprobesets;
  


  SEXP dim1;
  SEXP outvec; /* ,outnamesvec; */
  SEXP dimnames,names;

  SEXP temp;
  
  PROTECT(dim1 = getAttrib(PMmat,R_DimSymbol)); 
  rows = INTEGER(dim1)[0];
  cols = INTEGER(dim1)[1]; 

  PM = NUMERIC_POINTER(AS_NUMERIC(PMmat));
  
  nprobesets=INTEGER(N_probes)[0];
  
  /*  printf("%i\n",nprobesets); */
  /* printf("%d ",INTEGER(norm_flag)[0]); */
  if (INTEGER(norm_flag)[0]){
  /* normalize PM using quantile normalization */
  /*  printf("Normalizing\n"); */
    if (INTEGER(verbose)[0]){
      Rprintf("Normalizing\n");
    }
    qnorm_c(PM,&rows,&cols);
  }

  ProbeNames = Calloc(rows,const char *);

  for (i =0; i < rows; i++)
    ProbeNames[i] = CHAR(VECTOR_ELT(ProbeNamesVec,i));
  
  
  outnames = Calloc(nprobesets,char *);

  /* PROTECT(outvec = NEW_NUMERIC(nprobesets*cols)); */
  
  PROTECT(outvec = allocMatrix(REALSXP, nprobesets, cols));


  outexpr = NUMERIC_POINTER(outvec);
 	    
  /* printf("Calculating Expression\n"); */
  if (INTEGER(verbose)[0]){
    Rprintf("Calculating Expression\n");
  }

  do_RMA(PM, ProbeNames, &rows, &cols,outexpr,outnames,nprobesets);

  

  /* now lets put names on the matrix */

  PROTECT(dimnames = allocVector(VECSXP,2));
  PROTECT(names = allocVector(STRSXP,nprobesets));
  
  for ( i =0; i < nprobesets; i++){
    PROTECT(temp = mkChar(outnames[i]));
    SET_VECTOR_ELT(names,i,temp); /* was a direct mkChar prior to Sep 2, 2005*/
    UNPROTECT(1);
  }
  SET_VECTOR_ELT(dimnames,0,names);
  setAttrib(outvec, R_DimNamesSymbol, dimnames);
  UNPROTECT(2);
  for (i =0; i < nprobesets; i++)
    Free(outnames[i]);
  
  Free(outnames);
  Free(ProbeNames);
  UNPROTECT(2);
  return outvec;
}

/*******************************************************************************************************************
 **
 ** SEXP rma_c_complete(SEXP PMmat, SEXP MMmat, SEXP ProbeNamesVec,SEXP N_probes,SEXP densfunc, SEXP rho)
 **
 ** SEXP PMmat  - PM's
 ** SEXP MMmat - MM's
 ** SEXP ProbeNamesVec - names of probeset for each row
 ** SEXP N_probes - number of probesets
 ** SEXP densfunc - density function to use in computation of background
 ** SEXP rho - an R environment 
 ** SEXP norm_flag - TRUE/FALSE or 1/0 for normalize/not
 ** SEXP bg_flag - TRUE/FALSE  or 1/0 for background correct/not
 ** SEXP bg_type - integer indicating "RMA" background to use. 2 is equivalent to bg.correct.rma in affy 1.1.1
 **                all other values default to 1.0.2 "RMA" background
 ** SEXP verbose - TRUE/FALSE or 1/0 for be verbose or not
 ** 
 ** Main function to be called from R. Modifies the PM matrix from the parent environment. More dangerous than the
 ** function below, but less memory intensive. This is a function that implements the complete RMA method. ie
 ** background correction, quantile normalization, then expression summarization using median polish
 **
 *******************************************************************************************************************/

SEXP rma_c_complete(SEXP PMmat, SEXP ProbeNamesVec,SEXP N_probes,SEXP densfunc, SEXP rho,SEXP norm_flag, SEXP bg_flag, SEXP bg_type, SEXP verbose){
  SEXP dim1;
  double *PM;
  int rows,cols;


  if (INTEGER(bg_flag)[0]){ 
    if (INTEGER(verbose)[0]){
      Rprintf("Background correcting\n");
    }
    PROTECT(dim1 = getAttrib(PMmat,R_DimSymbol));
    rows = INTEGER(dim1)[0];
    cols = INTEGER(dim1)[1];
    PM = NUMERIC_POINTER(PMmat);
    rma_bg_correct(PM, rows, cols);
    UNPROTECT(1);
  }
  return rma_c_call(PMmat, ProbeNamesVec,N_probes,norm_flag,verbose);
}

/********************************************************************************************************************
 **
 ** SEXP rma_c_complete_copy(SEXP PMmat, SEXP MMmat, SEXP ProbeNamesVec,SEXP N_probes,SEXP densfunc, SEXP rho,SEXP norm_flag, SEXP bg_flag)
 **
 ** SEXP PMmat   - PM's
 ** SEXP ProbeNamesVec - names of probeset for each row
 ** SEXP N_probes  - number of probesets
 ** SEXP densfunc - density function to use in computation of background
 ** SEXP rho - an r environment to work within when doing density call in background step
 ** SEXP norm_flag - TRUE/FALSE or 1/0 for normalize/not
 ** SEXP bg_flag - TRUE/FALSE  or 1/0 for background correct/not
 ** SEXP bg_type - integer indicating "RMA" background to use. 2 is equivalent to bg.correct.rma in affy 1.1.1
 **                all other values default to 1.0.2 "RMA" background
 ** SEXP verbose - TRUE/FALSE or 1/0 for be verbose or not
 *
 ** Main function to be called from R. Makes a copy of the PM matrix and then works with that. Safer than the 
 ** other function above, but more memory intensive. This is the function that implements the complete RMA method.
 ** ie background correction, quantile normalization, then expression summarization using median polish
 **
 ********************************************************************************************************************/

SEXP rma_c_complete_copy(SEXP PMmat,  SEXP ProbeNamesVec,SEXP N_probes,SEXP densfunc, SEXP rho,SEXP norm_flag, SEXP bg_flag, SEXP bg_type, SEXP verbose){
  SEXP dim1,PMcopy,exprs;
  int rows,cols;
  double *PM;

  if (INTEGER(bg_flag)[0]){
    if (INTEGER(verbose)[0]){
      Rprintf("Background correcting\n");
    }  
    PROTECT(dim1 = getAttrib(PMmat,R_DimSymbol));
    rows = INTEGER(dim1)[0];
    cols = INTEGER(dim1)[1];
    PROTECT(PMcopy = allocMatrix(REALSXP,rows,cols));
    PM = NUMERIC_POINTER(PMcopy);
    copyMatrix(PMcopy,PMmat,0);
    rma_bg_correct(PM, rows, cols);
    exprs = rma_c_call(PMcopy, ProbeNamesVec, N_probes, norm_flag, verbose);
    UNPROTECT(2);
    return exprs;
  } else {
    PROTECT(dim1 = getAttrib(PMmat,R_DimSymbol));
    rows = INTEGER(dim1)[0];
    cols = INTEGER(dim1)[1];
    PROTECT(PMcopy = allocMatrix(REALSXP,rows,cols));
    copyMatrix(PMcopy,PMmat,0);
    exprs = rma_c_call(PMcopy, ProbeNamesVec, N_probes, norm_flag, verbose);
    UNPROTECT(2);
    return exprs;
  }
}
