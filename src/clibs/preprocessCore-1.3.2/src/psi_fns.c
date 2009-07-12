/*********************************************************************
 **
 ** file: psi_fns.c
 **
 ** Aim: implement M estimation psi functions for use in
 **      robust linear model fitting procedure.
 **
 ** Copyright (C) 2003 Ben Bolstad
 **
 ** created by: B. M. Bolstad <bolstad@stat.berkeley.edu>
 **
 ** Created on May 31, 2003
 **
 ** History
 ** May 31, 2003 - Initial version.Move psi_huber() over from rlm.c
 **                add fair, Cauchy, Geman-McClure, Welsch and Tukey
 ** Jun 03, 2003 - add Andrews and some NOTES/WARNINGS.
 ** Jun 04, 2003 - a mechanism for selecting a psi function
 **
 ********************************************************************/

/*********************************************************************
 **
 ** NOTES: on the tuning constants
 **
 ** Recommended values for the tuning constants (in general these are 
 ** chosen for 95% asymptotic efficiency in the case of the normal)
 **
 ** Huber - k = 1.345
 ** Fair - k = 1.3998
 ** Cauchy - k=2.3849 
 ** Welsch - k = 2.9846
 ** Tukey Biweight - k = 4.6851
 ** Andrews Sine - K = 1.339
 **
 ** Geman-McClure does not require a tuning constant.
 **
 ********************************************************************/

/*********************************************************************
 **
 ** WARNINGS:
 **
 ** Huber and Fair will converge to unique solutions. The others will 
 ** not. It is recommended that if you use one of the other methods you
 ** first use a fully iterated huber or other robust method and then 
 ** apply the chosen method.
 **
 **
 ********************************************************************/

#include "psi_fns.h"
#include <math.h>
#include <Rmath.h>

/*********************************************************************
 **
 ** double psi_huber(double u, double k,int deriv)
 **
 ** double u - data value
 ** double k - tuning constant
 ** int type - if 0 then return the evaluation of the weight function, if 1 returns the derivative
 **            other wise return psi itself
 **
 ** This function computes Hubers suggested PSI function.
 **
 *********************************************************************/

double psi_huber(double u, double k,int deriv){
  
  if (deriv == 0){
    if ( 1 < k/fabs(u)){
      return 1.0;
    } else {
      return  k/fabs(u);
    }
  } else if (deriv == 1){
    if (fabs(u) <= k){
      return 1.0;
    } else {
      return 0.0;
    }
  } else {
    if (fabs(u) <= k){
      return u;
    } else {
      if (u < 0){
	return -k;
      } else {
	return k;
      }
    }


  }
}



/*********************************************************************
 **
 ** double psi_fair(double u, double k,int deriv)
 **
 ** double u - data value
 ** double k - tuning constant
 ** int type - if 0 then return the evaluation of the weight function, if 1 returns the derivative
 **            other wise return psi itself
 **
 ** This function computes "fair" PSI function  
 **
 *********************************************************************/

double psi_fair(double u, double k,int deriv){
 
  if (deriv == 0){
    return 1.0/(1.0+fabs(u)/k);
  } else if (deriv == 1){
    if (u >=0){
      return 1.0/(1.0+fabs(u)/k) - u/(k*(1.0+fabs(u)/k)*(1.0+fabs(u)/k));
    } else {
      return 1.0/(1.0+fabs(u)/k) + u/(k*(1.0+fabs(u)/k)*(1.0+fabs(u)/k));
    }
  } else {    
    return u/(1.0+fabs(u)/k);
  }
}
  
/*********************************************************************
 **
 ** double psi_fair(double u, double k,int deriv)
 **
 ** double u - data value
 ** double k - tuning constant
 ** int type - if 0 then return the evaluation of the weight function, if 1 returns the derivative
 **            other wise return psi itself
 **
 ** This function computes the cauchy PSI function  
 **
 *********************************************************************/

double psi_cauchy(double u, double k,int deriv){
  
  if (deriv == 0){
    return 1.0/(1.0+(u/k)*(u/k));
  } else if (deriv == 1){
    return k*k*(k*k - u*u)/((k*k+u*u)*(k*k+u*u));
  } else {    
    return u/(1.0+(u/k)*(u/k));
  }
}

/*********************************************************************
 **
 ** double psi_GemanMcClure(double u, double k,int deriv)
 **
 ** double u - data value
 ** double k - tuning constant
 ** int type - if 0 then return the evaluation of the weight function, if 1 returns the derivative
 **            other wise return psi itself
 **
 ** This function computes the Geman-McClure PSI function  
 **
 *********************************************************************/

double psi_GemanMcClure(double u, double k,int deriv){
  
  if (deriv == 0){
    return 1.0/((1.0 + u*u)*(1.0 + u*u));
  } else if (deriv == 1){
    return (1.0 - 3.0*u*u)/((1.0+u*u)*(1.0+u*u)*(1.0+u*u));
  } else {    
    return u/((1.0 + u*u)*(1.0 + u*u));
  }
}


/*********************************************************************
 **
 ** double psi_Welsch(double u, double k,int deriv)
 **
 ** double u - data value
 ** double k - tuning constant
 ** int type - if 0 then return the evaluation of the weight function, if 1 returns the derivative
 **            other wise return psi itself
 **
 ** This function computes the Welsch PSI function  
 **
 *********************************************************************/

double psi_Welsch(double u, double k,int deriv){
  
  if (deriv == 0){
    return exp(-(u/k)*(u/k));
  } else if (deriv == 1){
    return exp(-(u/k)*(u/k))*(1 - 2.0*(u*u)/(k*k));
  } else {    
    return u*exp(-(u/k)*(u/k));
  }
}


/*********************************************************************
 **
 ** double psi_Welsch(double u, double k,int deriv)
 **
 ** double u - data value
 ** double k - tuning constant
 ** int type - if 0 then return the evaluation of the weight function, if 1 returns the derivative
 **            other wise return psi itself
 **
 ** This function computes the Welsch PSI function  
 **
 *********************************************************************/

double psi_Tukey(double u, double k,int deriv){
  
  if (deriv == 0){
    if (fabs(u) <= k){
      return pow((1.0 - (u/k)*(u/k)),2.0);
    } else {
      return 0;
    }
  } else if (deriv == 1){
     if (fabs(u) <= k){
       return (1.0 - (u/k)*(u/k))*(1.0-5.0*(u/k)*(u/k));
    } else {
      return 0;
    }
  } else {    
    if (fabs(u) <= k){
      return u*(1.0 - (u/k)*(u/k))* (1.0 - (u/k)*(u/k));
    } else {
      return 0;
    }
  }
}




/*********************************************************************
 **
 ** double psi_Andrews(double u, double k,int deriv)
 **
 ** double u - data value
 ** double k - tuning constant
 ** int type - if 0 then return the evaluation of the weight function, if 1 returns the derivative
 **            other wise return psi itself
 **
 ** This function computes the Andrews PSI function  
 **
 *********************************************************************/


double psi_Andrews(double u, double k,int deriv){
  
  if (deriv == 0){
    if (fabs(u) <= k*M_PI){
      return sin(u/k)/(u/k);
    } else {
      return 0;
    }
  } else if (deriv == 1){
     if (fabs(u) <= k*M_PI){
       return cos(u/k);
    } else {
      return 0;
    }
  } else {    
    if (fabs(u) <= k*M_PI){
      return k*sin(u/k);
    } else {
      return 0;
    }
  }
}


pt2psi psifuncArr[7];

pt2psi PsiFunc(int code){
  
  psifuncArr[0] = &psi_huber;
  psifuncArr[1] = &psi_fair;
  psifuncArr[2] = &psi_cauchy;
  psifuncArr[3] = &psi_GemanMcClure;
  psifuncArr[4] = &psi_Welsch;
  psifuncArr[5] = &psi_Tukey;
  psifuncArr[6] = &psi_Andrews;

  return psifuncArr[code];
}
