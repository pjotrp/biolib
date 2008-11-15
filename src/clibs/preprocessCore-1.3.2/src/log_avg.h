#ifndef LOG_AVG_H
#define LOG_AVG_H 1

void logaverage(double *data, int rows, int cols, double *results, double *resultsSE);
void LogAverage(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);
void LogAverage_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

#endif
