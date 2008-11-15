#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "R_ext/Boolean.h"

/*
taken from simpleaffy2.c in the simpleaffy package
Copyright (C) 2004 Crispin Miller

 This is a numerical approximation to the normal distribution as described in   
 Abramowitz and Stegun: Handbook of Mathematical functions
 see page 931: 26.2.1, 932:26.2.17
*/

double pnorm_approx(double z) {
    double b1 =  0.31938153; 
    double b2 = -0.356563782; 
    double b3 =  1.781477937;
    double b4 = -1.821255978;
    double b5 =  1.330274429; 
    double p  =  0.2316419; 
    double c2 =  0.3989423; 
    double a =fabs(z); 
    double t = 1.0/(1.0+a*p); 
    double b = c2*exp((-z)*(z/2.0)); 
    double n = ((((b5*t+b4)*t+b3)*t+b2)*t+b1)*t; 
    n = 1.0-b*n; 
    if (z >  6.0) { return 1.0; };
    if (z < -6.0) { return 0.0; };
    if ( z < 0.0 ) n = 1.0 - n; 
    return n; 
}

/* Given a double array length nx, rank it, and put the results in 'r' */
void rank(double *x, int nx, double *r) {
  int i       = 0;
  int rank    = 1;
  int ranksum = 1;
  int ntie    = 1;
  int prev    = 0;
  r[0] = 1.0;
  for(i = 1; i < nx; i++) {
    if(x[i] == x[prev]) {
      ntie++;
      rank++;
      ranksum += rank;
    }
    else {
      if(ntie > 1) {
	while(prev < i) {
	  r[prev] = (double) ranksum/ (double) ntie;
	  prev++;
	}
      }
      rank++;
      ranksum = rank;
      r[i] = rank;
      prev = i;
      ntie = 1;
    }
  }
  if(ntie > 1) {
    while(prev < i) {
      r[prev] = (double) ranksum/ (double) ntie;
      prev++;
    }
  }
 
}

/* a straight translation of relevant bits of the wilcox.test method
   in the R base library */
double wilcox(double *x, int n, double mu) {
  int i = 0;
  int j = 0;
  double *r    = 0;  
  double *absx = 0;
  int    *xidx = 0;
  double STATISTIC = 0;    
  double NTIES_SUM = 0;
  int    prev      = 0;
  int    ntie      = 0;
  double z         = 0;
  double SIGMA     = 0;
  double PVAL      = 0; 
  double nx        = n;

  for(i = 0; i < nx; i++) {
    x[j] = x[i] - mu;
    if(x[j] != 0) j++; /* eliminate zeros */
  }

  nx = j;
  r      = (double *) R_alloc(nx,sizeof(double));
  absx   = (double *) R_alloc(nx,sizeof(double));
  xidx   = (int *) R_alloc(nx,sizeof(int));

  for(i = 0 ; i < nx; i++) {
    absx[i] = fabs(x[i]);
    xidx[i] = i;
  }
  rsort_with_index(absx,xidx,nx);
  rank(absx,nx,r);
  for(i = 0; i < nx; i++) {
    r[i] = (x[xidx[i]] > 0) ? r[i] : -r[i];
  }

  for(i =0; i < nx; i++) {
    if(r[i] > 0) {
      STATISTIC += r[i];
    }
  }
  for(i = 1; i < nx; i++) {
    if(r[prev] == r[i]) {
      ntie++;
    }
    else {
      if(ntie > 1) {
	NTIES_SUM += ntie * ntie * ntie - ntie; 
      }
      ntie = 0;
      prev = i;
    }
  }

  NTIES_SUM += ntie * ntie * ntie - ntie; /* added by Crispin Noc 2005 */

  z     = STATISTIC - (nx * (nx + 1))/4;
  SIGMA = sqrt((nx * (nx + 1) * (2 * nx + 1)) / 24 - (NTIES_SUM / 48));
  PVAL  = pnorm_approx(z / SIGMA);
  PVAL    = 1 - PVAL;
  return(PVAL);
}    


/* compute the detection p-value for a particular probe using the algorithm described in 
 Liu et al. Bioinformatics(2002) 1593-1599
 pms is a list of probe perfect matches, mms is a list of mismatches n, the number of probe-pairs.
 tao and sat are parameters, as desccribed in the Liu et al. paper 
*/
double pma(double *pms, double*mms, int n, double tao,double sat) {
  int i = 0;
  int *ignore  = 0; 
  int totalSat = 0;
  int last     = 0;
  double *dv   = 0;
  double p     = 0;
  if(sat >= 0) {
    ignore = (int *) R_alloc(n, sizeof(int));
    /* saturation correction from the paper*/
    totalSat = 0;
    for(i = 0; i < n; i++) {
      if(mms[i] > sat) {
	ignore[i] = 1;
	totalSat++;
      }
      else ignore[i] = 0;
    }
    last = 0;
    if((totalSat > 0) & (totalSat < n)) { /* ignore probes with
					     saturated mms unless
					     they're all saturated */
      for(i = 0; i < n; i++) {
	if(!ignore[i]) {
	  pms[last] = pms[i];
	  mms[last] = mms[i];
	  last++;
	}
      }
      n = last;
    }
  }
  dv = (double *) R_alloc(n, sizeof(double));
  for(i =0; i < n; i++){   
    dv[i] =(pms[i] - mms[i]) / (pms[i] + mms[i]);
  }
  p = wilcox(dv,i,tao);
  return(p); 
}

/*
 compute for all probes
 assumes that pm mm pairs line up in the arrays and that the names do to. Also assumes that probes within a set are contiguous in each array.
 pm, mm and names are all length n long, and are, effectively, three columns from a matrix
 returns with 'dpval' containing the detection p values for each probeset.  
*/
void DetectionPValue (double *pm, double *mm, char **names, int *nprobes, double *tao, double *sat, double *dpval, int *nprobesets) {
  int start = 0;
  int i = 0;
  int j = 0;
  for(i = 1; i < *nprobes; i++) {
    if(strcmp(names[i],names[start]) != 0) {
      dpval[j] = pma(&(pm[start]),&(mm[start]),i-start,*tao,*sat);
      start = i;
      j++;
      if(j > *nprobesets) { error("Expecting %d unique probesets, found %d\n",*nprobesets,j); }
    }
  }
  dpval[j] = pma(&(pm[start]),&(mm[start]),i - start,*tao,*sat);
}












