#ifndef PLMR_H
#define PLMR_H

#include "psi_fns.h"

void plmr_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

void plmrr_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

void plmrc_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

void plmr_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

void plmrr_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

void plmrc_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);



#endif
