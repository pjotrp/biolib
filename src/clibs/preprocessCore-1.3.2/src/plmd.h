#ifndef PLMD_H
#define PLMD_H





void plmd_fit(double *y, int y_rows, int y_cols, int ngroups, int *grouplabels, int *was_split,
	      double *out_beta, double *out_resids, double *out_weights,
	      double (* PsiFn)(double, double, int), double psi_k,int max_iter);


double *plmd_get_design_matrix(int y_rows, int y_cols, int ngroups, int *grouplabels,int *was_split,int *X_rows,int *X_cols);







#endif
