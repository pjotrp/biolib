#ifndef WEIGHTEDKERNELDENSITY_H
#define WEIGHTEDKERNELDENSITY_H

void KernelDensity(double *x, int *nxxx, double *weights, double *output, double *xords, int *nout);
void KernelDensity_lowmem(double *x, int *nxxx, double *output, double *output_x, int *nout);
#endif
