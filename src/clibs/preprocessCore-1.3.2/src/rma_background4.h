#ifndef RMA_BACKGROUND4_H
#define RMA_BACKGROUND4_H

void rma_bg_parameters(double *PM,double *param, int rows, int cols, int column);
void rma_bg_adjust(double *PM, double *param, int rows, int cols, int column);
void rma_bg_correct(double *PM, int rows, int cols);

SEXP R_rma_bg_correct(SEXP PMmat,SEXP copy);

#endif
