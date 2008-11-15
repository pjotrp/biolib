#ifndef MEDIAN_H
#define MEDIAN_H 1



void ColMedian(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);
void ColMedian_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

void colmedian(double *data, int rows, int cols, double *results, double *resultsSE);
void colmedian_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);




#endif
