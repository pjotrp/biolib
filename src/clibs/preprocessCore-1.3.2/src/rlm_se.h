#ifndef RLM_SE_H
#define RLM_SE_H 1


void rlm_compute_se(double *X,double *Y, int n, int p, double *beta, double *resids,double *weights,double *se_estimates,double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k);
void rlm_compute_se_anova(double *Y, int y_rows,int y_cols, double *beta, double *resids,double *weights,double *se_estimates, double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k);
void rlm_compute_se_anova_given_probe_effects(double *Y, int y_rows,int y_cols, double *probe_effects,double *beta, double *resids,double *weights,double *se_estimates, double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k);

#endif
