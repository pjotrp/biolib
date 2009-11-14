#ifndef LM_H
#define LM_H



void lm_wfit(double *x, double *y, double *w, int rows, int cols, double tol, double *out_beta, double *out_resids);


#endif
