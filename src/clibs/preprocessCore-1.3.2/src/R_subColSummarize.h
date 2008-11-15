#ifndef R_SUBCOLSUMMARIZE_H
#define R_SUBCOLSUMMARIZE_H

SEXP R_subColSummarize_avg_log(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_log_avg(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_avg(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_biweight_log(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_biweight(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_median_log(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_log_median(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_median(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_medianpolish_log(SEXP RMatrix, SEXP R_rowIndexList);
SEXP R_subColSummarize_medianpolish(SEXP RMatrix, SEXP R_rowIndexList);


#endif
