#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H 1


void Lapack_Init(void);
int SVD_inverse(double *X, double *Xinv, int n);
int Choleski_inverse(double *X, double *Xinv, double *work, int n, int upperonly);




#endif
