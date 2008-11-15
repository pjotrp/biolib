/*****************************************************************************
 **
 ** file: weightedkerneldensity.c
 **
 ** aim : compute weighted kernel density estimates
 **
 ** Copyright (C) 2003-2008 Ben Bolstad
 **
 ** created on: Mar 24, 2003
 **
 ** Description
 ** 
 ** the aim here is to implement kernel density estimators, with the option to 
 ** weight each observation. For speed we will use the FFT to convolve a weighted
 ** histogram with a kernel.
 ** 
 **
 ** History
 **
 ** Mar 9, 2003 - Initial version
 ** Mar 10, 2003 - Add in FFT framework, Push into AffyExtensions
 ** Mar 11, 2003 - Add ability to do kernel density with arbitrary weights
 ** Apr 22, 2003 - fix computation of bandwidth. Add in linear interpolation
 **                so as to be more consistent with R.
 ** Apr 5, 2004 - all calloc/free are now Calloc/Free
 ** Mar 24, 2005 - Add in IQR function to handle obscure cases.
 ** Mar 15, 2008 - add KernelDensity_lowmem. weightedkerneldensity.c is ported from affyPLM to preprocessCore
 **
 ****************************************************************************/

#include <R_ext/Arith.h>
#include <R_ext/Applic.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> /* For memcpy */
#include "rma_common.h"


/*****************************************************************************
 **
 ** void weighted_massdist(double *x, int nx, double *w, double *xlow, double *xhigh, double *y, int *ny)
 **
 ** see AS R50 and AS 176  (AS = Applied Statistics)
 **
 ** idea is to discretize the data,  but have modified algorithm to put weights on each observation 
 **
 ** double *x - the data
 ** int nx - length of x
 ** double *w - weight for each one of x, vector should also be of length nx
 ** double *xlow - minimum value in x dimension
 ** double *xhigh - maximum value in x dimension
 ** double *y - on output will contain discretation scheme of data
 ** int ny - length of y
 **
 ****************************************************************************/

static void weighted_massdist(double *x, int *nx, double *w, double *xlow, double *xhigh, double *y, int *ny){
  
  double fx, xdelta, xmass, xpos;
  int i, ix, ixmax, ixmin;
  
  ixmin = 0;
  ixmax = *ny - 2;
  xmass = 0.0;
  xdelta = (*xhigh - *xlow) / (*ny - 1);
  
  for(i=0; i < *ny ; i++){
    y[i] = 0.0;
  }

  for (i=0; i < *nx; i++){
    xmass += w[i];
  }
  
  xmass = 1.0/xmass;
  /* Rprintf("%f\n",xmass);*/

  for(i=0; i < *nx ; i++) {
    if(R_FINITE(x[i])) {
      xpos = (x[i] - *xlow) / xdelta;
      ix = floor(xpos);
      fx = xpos - ix;
      if(ixmin <= ix && ix <= ixmax) {
	y[ix] += w[i]*(1 - fx);
	y[ix + 1] +=  w[i]*fx;
      }
      else if(ix == -1) {
	y[0] += w[i]*fx;
      }
      else if(ix == ixmax + 1) {
	y[ix] += w[i]*(1 - fx);
      }
    }
  }
  
  for(i=0; i < *ny; i++)
    y[i] *= xmass;
  
}

/*****************************************************************************
 **
 ** void unweighted_massdist(double *x, int nx, double *xlow, double *xhigh, double *y, int *ny)
 **
 ** see AS R50 and AS 176  (AS = Applied Statistics)
 **
 ** idea is to discretize the data,  does not put weights on each observation 
 **
 ** double *x - the data
 ** int nx - length of x
 ** double *w - weight for each one of x, vector should also be of length nx
 ** double *xlow - minimum value in x dimension
 ** double *xhigh - maximum value in x dimension
 ** double *y - on output will contain discretation scheme of data
 ** int ny - length of y
 **
 ****************************************************************************/

static void unweighted_massdist(double *x, int *nx, double *xlow, double *xhigh, double *y, int *ny){
  
  double fx, xdelta, xpos;
  int i, ix, ixmax, ixmin;
  
  ixmin = 0;
  ixmax = *ny - 2;
  xdelta = (*xhigh - *xlow) / (*ny - 1);
  
  for(i=0; i < *ny ; i++){
    y[i] = 0.0;
  }

  for(i=0; i < *nx ; i++) {
    if(finite(x[i])) {
      xpos = (x[i] - *xlow) / xdelta;
      ix = (int)floor(xpos);
      fx = xpos - ix;
      if(ixmin <= ix && ix <= ixmax) {
        y[ix] += (1 - fx);
        y[ix + 1] +=  fx;
      }
      else if(ix == -1) {
        y[0] += fx;
      }
      else if(ix == ixmax + 1) {
        y[ix] += (1 - fx);
      }
    }
  }
  for(i=0; i < *ny; i++)
    y[i] *= (1.0/(double)(*nx));
}



/*********************************************************************
 ** 
 ** void twiddle(int N, int i, double *tf_real, double *tf_imag)
 **
 ** int N - length of data series
 ** int i - 
 ** double *tf_real - on output contains real part of twiddle factor 
 ** double *tf_imag - on output contains imaginary part of twiddle factor  
 **
 ** twiddle factor in FFT 
 **
 ********************************************************************/

static  void twiddle(int N, int i,double *tf_real, double *tf_imag){
  double pi = 3.14159265358979323846; 
  if (i ==0){
    *tf_real = 1;
    *tf_imag = 0;
   } else {
    *tf_real = cos(2*pi*(double)i/(double)N);  
    *tf_imag = -sin(2*pi*(double)i/(double)N); 
  }
} 

/*********************************************************************
 ** 
 ** void twiddle2(int N, int i, double *tf_real, double *tf_imag)
 **
 ** int N - length of data series
 ** int i - 
 ** double *tf_real - on output contains real part of twiddle factor 
 ** double *tf_imag - on output contains imaginary part of twiddle factor  
 **
 ** twiddle factor in FFT when computing inverse FFT
 **
 ********************************************************************/

static void twiddle2(int N, int i,double *tf_real, double *tf_imag){
  double pi = 3.14159265358979323846; 
  if (i ==0){
    *tf_real = 1;
    *tf_imag = 0;
   } else {
    *tf_real = cos(2*pi*(double)i/(double)N);  
    *tf_imag = sin(2*pi*(double)i/(double)N); 
  }
} 


/*********************************************************************
 **
 ** void fft_dif(double *f_real, double *f_imag, int p){
 **
 ** compute the FFT using Decimation In Frequency of a data sequence of length 2^p
 **
 ** double *f_real - real component of data series
 ** double *f_imag - imaginary component of data series
 ** int p -  where 2^p is length of data series
 ** 
 ** computes the FFT in place, result is in reverse bit order.
 **
 ********************************************************************/

static void fft_dif(double *f_real, double *f_imag, int p){
  
  int BaseE, BaseO, i, j, k, Blocks, Points, Points2;
  double even_real, even_imag, odd_real, odd_imag;
  double tf_real, tf_imag;

  Blocks = 1;
  Points = 1 << p;
  

  for (i=0; i < p; i++){
    Points2 = Points >> 1;
    BaseE = 0;
    for (j=0; j < Blocks; j++){
      BaseO = BaseE + Points2;
      for (k =0; k < Points2; k++){
	even_real = f_real[BaseE + k] + f_real[BaseO + k]; 
	even_imag = f_imag[BaseE + k] + f_imag[BaseO + k];  
	twiddle(Points,k,&tf_real, &tf_imag); 
	odd_real = (f_real[BaseE+k]-f_real[BaseO+k])*tf_real - (f_imag[BaseE+k]-f_imag[BaseO+k])*tf_imag;
	odd_imag = (f_real[BaseE+k]-f_real[BaseO+k])*tf_imag + (f_imag[BaseE+k]-f_imag[BaseO+k])*tf_real; 
	f_real[BaseE+k] = even_real;
	f_imag[BaseE+k] = even_imag;
	f_real[BaseO+k] = odd_real;
	f_imag[BaseO+k] = odd_imag;
	
      } 
      BaseE = BaseE + Points;
    }                     
    Blocks = Blocks << 1; 
    Points = Points >> 1;
  }
} 

/*********************************************************************
 **
 ** void fft_ditI(double *f_real, double *f_imag, int p){
 **
 ** compute the IFFT using Decimation In time of a data sequence of length 2^p
 **
 ** double *f_real - real component of data series
 ** double *f_imag - imaginary component of data series
 ** int p -  where 2^p is length of data series
 ** 
 ** computes the IFFT in place, where input is in reverse bit order.
 ** output is in normal order.
 **
 ********************************************************************/

static void fft_ditI(double *f_real, double *f_imag, int p){
  int i,j,k, Blocks, Points, Points2, BaseB, BaseT;
  double top_real, top_imag, bot_real, bot_imag, tf_real, tf_imag;

  Blocks = 1 << (p-1);
  Points = 2;  
  for (i=0; i < p; i++){
    Points2 = Points >> 1;
    BaseT = 0;
    for (j=0; j < Blocks; j++){
      BaseB = BaseT+Points2;
      for (k=0; k < Points2; k++){
	top_real = f_real[BaseT+k];
	top_imag = f_imag[BaseT+k];	
	twiddle2(Points,k,&tf_real, &tf_imag);
	bot_real = f_real[BaseB+k]*tf_real - f_imag[BaseB+k]*tf_imag;
	bot_imag = f_real[BaseB+k]*tf_imag + f_imag[BaseB+k]*tf_real;
	f_real[BaseT+k] = top_real + bot_real;
	f_imag[BaseT+k] = top_imag + bot_imag;
	f_real[BaseB+k] = top_real - bot_real;   
	f_imag[BaseB+k] = top_imag - bot_imag; 
      }     
      BaseT= BaseT + Points; 
    }
    Blocks = Blocks >> 1;
    Points = Points << 1;
  }
  
} 

/*******************************************************************
 **
 ** static void fft_density_convolve(double *y, double *kords, int n)
 **
 ** double *y - ve
 ** double *kords - 
 ** int n - 
 **
 **
 ******************************************************************/

static void fft_density_convolve(double *y, double *kords, int n){
  int i;
  int nlog2 = (int)(log((double)n)/log(2.0) + 0.5); /* ugly hack to stop rounding problems */
  double *y_imag = Calloc(n,double);
  double *kords_imag = Calloc(n,double);
  double *conv_real = Calloc(n,double);
  double *conv_imag = Calloc(n,double);
 

  
  
  /* printf("nlog2: %.30lf  %d\n", log((double)n)/log(2.0),nlog2); */

  fft_dif(y, y_imag, nlog2);
  fft_dif(kords,kords_imag,nlog2);
  
  for (i=0; i < n; i++){
    conv_real[i] = y[i]*kords[i] + y_imag[i]*kords_imag[i];
    conv_imag[i] = y[i]*(-1*kords_imag[i]) + y_imag[i]*kords[i];
  }
  
  fft_ditI(conv_real, conv_imag, nlog2);

  for (i=0; i < n; i++){
    kords[i] = conv_real[i];
  }


  Free(conv_real);
  Free(conv_imag);
  Free(kords_imag);
  Free(y_imag);
  

}

/**************************************************************
 **
 ** static void kernelize(double *data, int n, double bw, int kernel)
 **
 ** double *data - data to kernelize
 ** int n - length of data.
 ** double bw - bandwidth for Kernel
 ** int kernel - an integer specifying which kernel to use 
 **              1 is gaussian, 2 is Epanechnikov,
 **              3 is ...........
 **
 **
 ***************************************************************/

static void kernelize(double *data, int n, double bw, int kernel){
  
  double a = 0.0;
  int i;


  if (kernel == 1){
    /* Gaussian Kernel */
     
  } else if (kernel == 2){
    /* Epanechnikov Kernel */
    a = bw * sqrt(5.0);
    for (i =0; i < n; i++){
      if (fabs(data[i]) < a){
	data[i] = 3.0/(4.0*a)*(1.0 - (fabs(data[i])/a)*  (fabs(data[i])/a));
      } else {
	data[i] = 0.0;
      }
    }
  }

}


/*****************************************************************
 **
 ** static double compute_sd(double *x, int length)
 **
 ** double *x - data vector
 ** int length - length of x
 **
 ** compute the standard deviation of a data vector
 **
 *****************************************************************/

static double compute_sd(double *x, int length){
  
  int i;
  double sum=0.0,sum2=0.0;

  for (i = 0; i < length; i++){
    sum+=x[i];
  }
  
  sum = sum/(double)length;
  for (i=0; i < length; i++){
    sum2+=(x[i]-sum)*(x[i] - sum);
  }
  
  return(sqrt(sum2/(double)(length-1)));
}

/*****************************************************************
 **
 ** static double bandwidth(double *x, int length, double iqr)
 **
 ** double *x - data vector
 ** int length - length of x
 ** double iqr - IQR of *x
 **
 ** compute the kernel bandwidth
 **
 *****************************************************************/

static double bandwidth(double *x, int length, double iqr){

  double hi;
  double lo;
  
  hi = compute_sd(x, length);
  
  if (hi > iqr){
    lo = iqr/1.34;
  } else {
    lo = hi;
  }

  if (lo == 0){
    if (hi !=0){
      lo = hi;
    } else if (fabs(x[1]) != 0){
      lo = fabs(x[1]);
    } else {
      lo = 1.0;
    }
  }

  return (0.9*lo*pow((double)length, -0.2));

}  

/******************************************************************
 **
 ** double linear_interpolate_helper(double v, double *x, double *y, int n)
 **
 ** double v
 ** double *x
 ** double *y
 ** int n
 **
 ** linearly interpolate v given x and y.
 **
 **
 **********************************************************************/

static double linear_interpolate_helper(double v, double *x, double *y, int n)
{
  int i, j, ij;
 
  i = 0;
  j = n - 1;
    
  if(v < x[i]) return y[0];
  if(v > x[j]) return y[n-1];
 
  /* find the correct interval by bisection */
  
  while(i < j - 1) { /* x[i] <= v <= x[j] */
    ij = (i + j)/2; /* i+1 <= ij <= j-1 */
    if(v < x[ij]) j = ij;
    else i = ij;
    /* still i < j */
  }
  /* provably have i == j-1 */
  
  /* interpolation */
  
  if(v == x[j]) return y[j];
  if(v == x[i]) return y[i];
  /* impossible: if(x[j] == x[i]) return y[i]; */
  
  return y[i] + (y[j] - y[i]) * ((v - x[i])/(x[j] - x[i]));
  
}

/*********************************************************************
 **
 ** void linear_interpolate(double *x, double *y, double *xout, double *yout, int length)
 **
 ** double *x
 ** double *y
 ** double *xout
 ** double *yout
 ** int length
 **
 ** given x and y, interpolate linearly at xout putting the results in yout
 **
 **
 **********************************************************************/



static void linear_interpolate(double *x, double *y, double *xout, double *yout, int length){

   int i;
   
   for(i=0 ; i < length; i++)
     yout[i] = linear_interpolate_helper(xout[i], x, y, length);
}

static double IQR(double *x, int length);

/**********************************************************************
 **
 ** void KernelDensity(double *x, int *nxxx, double *output, double *xords, double *weights)
 **
 ** double *x - data vector
 ** int *nxxx - length of x
 ** double *output - place to output density values
 ** double *xords - x coordinates corresponding to output
 ** double *weights - a weight for each item of *x should be of length *nxxx
 ** int *nout - length of output should be a power of two, preferably 512 or above
 **
 ** 
 **
 **********************************************************************/

void KernelDensity(double *x, int *nxxx, double *weights, double *output, double *output_x, int *nout){

  int nx = *nxxx;

  int n = *nout;
  int n2= 2*n;
  int i;
  double low, high,iqr,bw,to,from;
  double *kords = Calloc(2*n,double);
  double *buffer = Calloc(nx,double);
  double *y = Calloc(2*n,double);
  double *xords = Calloc(n,double);

  /* for (i =0; i < nx; i++){
    buffer[i] = x[i];
    }
  */
  memcpy(buffer,x,nx*sizeof(double));


  qsort(buffer,nx,sizeof(double),(int(*)(const void*, const void*))sort_double);
  
  low  = buffer[0];
  high = buffer[nx-1];
  iqr =  IQR(buffer,nx);  /* buffer[(int)(0.75*nx + 0.5)] - buffer[(int)(0.25*nx+0.5)]; */
  

  bw = bandwidth(x,nx,iqr);
  
  low = low - 7*bw;
  high = high + 7*bw;
    

  for (i=0; i <= n; i++){
    kords[i] = (double)i/(double)(2*n -1)*2*(high - low);
  }  
  for (i=n+1; i < 2*n; i++){
    kords[i] = -kords[2*n - i];
  }
  
  /* bw = bandwidth(x,nx,iqr); */
  
  /* printf("iqr: %f bw: %f\n",iqr,bw); */
  
  kernelize(kords, 2*n,bw,2);

  weighted_massdist(x, &nx, weights, &low, &high, y, &n);

  fft_density_convolve(y,kords,n2);
  to = high - 4*bw;  /* corrections to get on correct output range */
  from = low + 4* bw;
  for (i=0; i < n; i++){
    xords[i] = (double)i/(double)(n -1)*(high - low)  + low;
    output_x[i] = (double)i/(double)(n -1)*(to - from)  + from;
  }

  for (i =0; i < n; i++){
    kords[i] = kords[i]/n2;
  }

  /* to get results that agree with R really need to do linear interpolation */

  linear_interpolate(xords, kords, output_x, output,n);

  Free(xords);
  Free(y);
  Free(buffer);
  Free(kords);

}

/**
 **
 ** Note the following function assumes that data (x) is sorted
 **
 ** Aim is to duplicate R quantile function
 **
 **/


static double IQR(double *x, int length){

  double lowindex, highindex;
  double lowfloor, highfloor;
  double lowceil, highceil;
  int low_i, high_i;
  double low_h, high_h;


  double qslow, qshigh;
  
  lowindex = (double)(length -1)*0.25;
  highindex = (double)(length -1)*0.75;

  lowfloor = floor(lowindex);
  highfloor = floor(highindex);

  lowceil = ceil(lowindex);
  highceil = ceil(highindex);
  
  low_i = lowindex > lowfloor;
  high_i = highindex > highfloor;
  
  qslow = x[(int)lowfloor];
  qshigh = x[(int)highfloor];
  
  low_h = lowindex - lowfloor;
  high_h = highindex - highfloor;
  
  if (low_h > 1e-10){
    qslow = (1.0 - low_h)*qslow + low_h*x[(int)lowceil];
  }
  if (high_h > 1e-10){
    qshigh = (1.0 - high_h)*qshigh + high_h*x[(int)highceil];
  }

  return qshigh - qslow;

}


/**********************************************************************
 **
 ** void KernelDensity_lowmem(double *x, int *nxxx, double *output, double *xords, double *weights)
 **
 ** double *x - data vector (note order will be changed on output)
 ** int *nxxx - length of x
 ** double *output - place to output density values
 ** double *xords - x coordinates corresponding to output
 ** double *weights - a weight for each item of *x should be of length *nxxx
 ** int *nout - length of output should be a power of two, preferably 512 or above
 **
 ** 
 **********************************************************************/

void KernelDensity_lowmem(double *x, int *nxxx, double *output, double *output_x, int *nout){

  int nx = *nxxx;

  int n = *nout;
  int n2= 2*n;
  int i;
  double low, high,iqr,bw,from,to;
  double *kords = Calloc(2*n,double);
  double *buffer = x; 
  double *y = Calloc(2*n,double);
  double *xords = Calloc(n,double);

  qsort(buffer,nx,sizeof(double),(int(*)(const void*, const void*))sort_double);
 
  low  = buffer[0];
  high = buffer[nx-1];
  iqr =  IQR(buffer,nx); //buffer[(int)(0.75*nx+0.5)] - buffer[(int)(0.25*nx+0.5)];
  

  bw = bandwidth(x,nx,iqr);
  
  low = low - 7*bw;
  high = high + 7*bw;
    

  for (i=0; i <= n; i++){
    kords[i] = (double)i/(double)(2*n -1)*2*(high - low);
  }  
  for (i=n+1; i < 2*n; i++){
    kords[i] = -kords[2*n - i];
  }
  
  //bw = bandwidth(x,nx,iqr);
  
  /* printf("bw: %f\n",bw);*/

  kernelize(kords, 2*n,bw,2);

  unweighted_massdist(x, &nx, &low, &high, y, &n);

  fft_density_convolve(y,kords,n2);


  to = high - 4*bw;  /* corrections to get on correct output range */
  from = low + 4* bw;

  for (i=0; i < n; i++){
    xords[i] = (double)i/(double)(n -1)*(high - low)  + low;
    output_x[i] = (double)i/(double)(n -1)*(to - from)  + from;
  }

  for (i =0; i < n; i++){
    kords[i] = kords[i]/n2;
  }

  // to get results that agree with R really need to do linear interpolation

  linear_interpolate(xords, kords, output_x, output,n);
  
  Free(xords);
  Free(y);
  Free(kords);

}
