#ifndef MEDIANPOLISH_H
#define MEDIANPOLISH_H 1

void median_polish_fit_no_copy(double *data, int rows, int cols, double *r, double *c, double *t);
void median_polish_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);
void median_polish_log2_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);
void median_polish_log2(double *data, int rows, int cols, double *results, double *resultsSE, double *residuals);
void median_polish(double *data, int rows, int cols, double *results, double *resultsSE, double *residuals);
void MedianPolish(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);
void MedianPolish_no_log(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);


#endif
