#ifndef AVG_H
#define AVG_H

void ColAverage(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);
void ColAverage_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

void colaverage_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);
void colaverage(double *data, int rows, int cols, double *results, double *resultsSE);

#endif
