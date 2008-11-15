#ifndef MEDIAN_LOG_H
#define MEDIAN_LOG_H 1



void MedianLog(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);
void MedianLog_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

void medianlog(double *data, int rows, int cols, double *results, double *resultsSE);
void medianlog_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);




#endif
