#ifndef RLM_H
#define RLM_H 1

void rlm_fit(double *x, double *y, int rows, int cols, double *out_beta, double *out_resids, double *out_weights, double (* PsiFn)(double, double, int), double psi_k, int max_iter,int initialized);

void rlm_wfit(double *x, double *y, double *w, int rows, int cols, double *out_beta, double *out_resids, double *out_weights, double (* PsiFn)(double, double, int), double psi_k, int max_iter,int initialized);



double med_abs(double *x, int length);
double irls_delta(double *old, double *new, int length);

void rlm_fit_anova(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

void rlm_wfit_anova(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

void rlm_fit_anova_given_probe_effects(double *y, int y_rows, int y_cols, double *probe_effects, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

void rlm_wfit_anova_given_probe_effects(double *y, int y_rows, int y_cols, double *probe_effects, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized);

#endif
