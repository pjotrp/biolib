#ifndef PLMR_H
#define PLMR_H

#include "psi_fns.h"

/*! \brief robust linear regression fit row-colum model using PLM-r
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows and/or columns when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmr_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);


/*! \brief robust linear regression fit row-colum model using PLM-r
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows and/or columns when a significant number of probes are poorly performing
 *
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param w  weights for each observation: length y_rows*y_cols
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmr_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

/*! \brief robust linear regression fit row-colum model using PLM-rr
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmrr_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int ini
tialized);

/*! \brief robust linear regression fit row-colum model using PLM-rc
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmrc_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int ini
tialized);

/*! \brief robust linear regression fit row-colum model using PLM-rr
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param w  weights for each observation: length y_rows*y_cols
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmrr_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_
iter, int initialized);

/*! \brief robust linear regression fit row-colum model using PLM-rc
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire columns when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param w  weights for each observation: length y_rows*y_cols
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmrc_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_
iter, int initialized);






























#endif
