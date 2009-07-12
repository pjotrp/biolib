#ifndef R_COLSUMMARIZE_H
#define R_COLSUMMARIZE_H

SEXP R_colSummarize_avg_log(SEXP RMatrix);
SEXP R_colSummarize_log_avg(SEXP RMatrix);
SEXP R_colSummarize_log_median(SEXP RMatrix);
SEXP R_colSummarize_median_log(SEXP RMatrix);
SEXP R_colSummarize_biweight_log(SEXP RMatrix);
SEXP R_colSummarize_medianpolish_log(SEXP RMatrix);

SEXP R_colSummarize_avg(SEXP RMatrix);
SEXP R_colSummarize_median(SEXP RMatrix);
SEXP R_colSummarize_biweight(SEXP RMatrix);
SEXP R_colSummarize_medianpolish(SEXP RMatrix);

#endif
