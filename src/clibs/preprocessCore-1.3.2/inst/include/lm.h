/*! \file lm.h
    \brief Functions for weighted least squares regression
        
*/

#ifndef LM_H
#define LM_H


/*! \brief Weighted least squares regression
 *
 * This function computes weighted linear regression estimates using QR decomposition
 *
 * 
 * @param x - Design matrix: dimension rows*cols
 * @param y - dependent variable: length rows
 * @param w - weights for each observation: length rows
 * @param rows - dimension of input
 * @param cols - dimension of input
 * @param tol - machine tolerance used in qr decomp
 * @param out_beta - place to output beta estimates: length cols
 * @param out_resids - place to output residuals: length rows
 *
 ************************************************************************/


void lm_wfit(double *x, double *y, double *w, int rows, int cols, double tol, double *out_beta, double *out_resids);


#endif
