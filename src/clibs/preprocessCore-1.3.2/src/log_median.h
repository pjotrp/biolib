#ifndef LOG_MEDIAN_H
#define LOG_MEDIAN_H 1



void LogMedian(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);
void LogMedian_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

void logmedian(double *data, int rows, int cols, double *results, double *resultsSE);
void logmedian_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);

#endif
