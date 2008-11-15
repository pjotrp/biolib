/*! \file rlm_se.h
    \brief Functions for computing SE for fitted robust linear models
        
*/

#ifndef RLM_SE_H
#define RLM_SE_H 1

/*! \brief Estimate SE for robust linear regression fit using iteratively reweighted least squares
 *
 * 
 * @param X  Design matrix: dimension n*p
 * @param Y  dependent variable: length n
 * @param n  dimension of input
 * @param p  dimension of input
 * @param beta  fitted parameter estimates: length p
 * @param resids estimated residuals: length n
 * @param weights  estimated weights: length n
 * @param se_estimates on output contains standard error estimates : length p
 * @param varcov a place to store estimated variance covariance matrix: dimension p*p (or set to NULL)
 * @param residSE estimated residual standard error
 * @param method should be integer 1,2,3 or 4 (4 is the default).
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 *
 */


void rlm_compute_se(double *X,double *Y, int n, int p, double *beta, double *resids,double *weights,double *se_estimates,double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k);

/*! \brief Estimate SE for robust linear regression fit using iteratively reweighted least squares
 *
 * Specialized to the model y = cols + rows + error model
 * 
 * @param Y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param beta  fitted parameter estimates: length y_rows + y_cols -1
 * @param resids estimated residuals: length y_rows*y_cols
 * @param weights  estimated weights: length y_rows*y_cols
 * @param se_estimates on output contains standard error estimates : y_rows + y_cols -1
 * @param varcov a place to store estimated variance covariance matrix: dimension (y_rows + y_cols -1)*(y_rows + y_cols -1) (or set to NULL)
 * @param residSE estimated residual standard error
 * @param method should be integer 1,2,3 or 4 (4 is the default).
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 *
 */

void rlm_compute_se_anova(double *Y, int y_rows,int y_cols, double *beta, double *resids,double *weights,double *se_estimates, double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k);

/*! \brief Estimate SE for robust linear regression fit using iteratively reweighted least squares
 *
 * Specialized to the model y = cols + rows + error model where the rows parameters are previously specified
 * designed to work independently for each column so can be applied "chip by chip"
 * 
 * @param Y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param probe_effects previously computed row effects with length y_rows. Assumed that it sums to 0.
 * @param beta  fitted parameter estimates: length y_rows + y_cols -1
 * @param resids estimated residuals: length y_rows*y_cols
 * @param weights  estimated weights: length y_rows*y_cols
 * @param se_estimates on output contains standard error estimates : y_rows + y_cols -1
 * @param varcov a place to store estimated variance covariance matrix: dimension (y_rows + y_cols -1)*(y_rows + y_cols -1) (or set to NULL)
 * @param residSE estimated residual standard error
 * @param method should be integer 1,2,3 or 4 (4 is the default). Currently ignored.
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 *
 */


void rlm_compute_se_anova_given_probe_effects(double *Y, int y_rows,int y_cols, double *probe_effects,double *beta, double *resids,double *weights,double *se_estimates, double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k);




#endif
