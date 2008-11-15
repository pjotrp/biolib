/*! \file rlm.h
    \brief Functions for fitting robust linear models
        
*/


#ifndef RLM_H
#define RLM_H 1

/*! \brief robust linear regression fit using iteratively reweighted least squares
 *
 * 
 * @param x  Design matrix: dimension rows*cols
 * @param y  dependent variable: length rows
 * @param rows  dimension of input
 * @param cols  dimension of input
 * @param out_beta  place to output beta estimates: length cols
 * @param out_resids  place to output residuals: length rows
 * @param out_weights  place to output weights: length rows
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void rlm_fit(double *x, double *y, int rows, int cols, double *out_beta, double *out_resids, double *out_weights, double (* PsiFn)(double, double, int), double psi_k, int max_iter,int initialized);
/*! \brief robust linear regression fit using iteratively reweighted least squares
 *
 * 
 * @param x  Design matrix: dimension rows*cols
 * @param y  dependent variable: length rows
 * @param w  weights for each observation: length rows
 * @param rows  dimension of input
 * @param cols  dimension of input
 * @param out_beta  place to output beta estimates: length cols
 * @param out_resids  place to output residuals: length rows
 * @param out_weights  place to output weights: length rows
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void rlm_wfit(double *x, double *y, double *w, int rows, int cols, double *out_beta, double *out_resids, double *out_weights, double (* PsiFn)(double, double, int), double psi_k, int max_iter,int initialized);



double med_abs(double *x, int length);
/* double irls_delta(double *old, double *new, int length); */

/*! \brief robust linear regression fit row-colum model
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0
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

void rlm_fit_anova(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

/*! \brief robust linear regression fit row-colum model
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0
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

void rlm_wfit_anova(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

/*! \brief apply row effects of a robust linear regression fit row-colum model
 *
 * Using pre-computed row effects from the model y = cols + rows + errors with constraint sum rows = 0
 * apply on a single column by column basis to robustly estimate col effects for each column
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param probe_effects  previously computed row effects with length y_rows. Assumed that it sums to 0.
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void rlm_fit_anova_given_probe_effects(double *y, int y_rows, int y_cols, double *probe_effects, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, 
double, int), double psi_k,int max_iter, int initialized);

/*! \brief apply row effects of a robust linear regression fit row-colum model
 *
 * Using pre-computed row effects from the model y = cols + rows + errors with constraint sum rows = 0
 * apply on a single column by column basis to robustly estimate col effects for each column
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param probe_effects  previously computed row effects with length y_rows. Assumed that it sums to 0.
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

void rlm_wfit_anova_given_probe_effects(double *y, int y_rows, int y_cols, double *probe_effects, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);




#endif
