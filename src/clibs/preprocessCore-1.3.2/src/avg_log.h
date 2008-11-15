#ifndef AVG_LOG_H
#define AVG_LOG_H

void AverageLog(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);
void AverageLog_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

void averagelog_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);
void averagelog(double *data, int rows, int cols, double *results, double *resultsSE);

#endif
