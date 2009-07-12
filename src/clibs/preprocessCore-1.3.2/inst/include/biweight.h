/*! \file biweight.h
    \brief Functions for column wise summarizing a matrix by \f$log2\f$ transforming the data and then using a 1-step Tukey Biweight
    
    
*/

#ifndef BIWEIGHT_H
#define BIWEIGHT_H 1

/*! \brief log2 transform the data and then use a 1-step Tukey Biweight to summarize each column
 * 
 *  Given a data matrix of probe intensities compute average expression measure then log2 it and SE of this estimate
 *  on a column by column basis
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols
 *
 *  
 */

void tukeybiweight(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief Use a 1-step Tukey Biweight to summarize each column
 * 
 *  Given a data matrix of probe intensities compute average expression measure then log2 it and SE of this estimate
 *  on a column by column basis
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols
 *
 *  
 */

void tukeybiweight_no_log(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief Use a 1-step Tukey Biweight to summarize each column
 *
 * Given a data matrix of probe intensities, and a list of rows in the matrix 
 * corresponding to a single probeset, compute log2 transformed 1-step Tukey Biweight expression measure. 
 * Note that data is a probes by chips matrix. Also compute SE estimates
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols
 *
 *  
 */

void TukeyBiweight(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);

/*! \brief Use a 1-step Tukey Biweight to summarize each column
 *
 * Given a data matrix of probe intensities, and a list of rows in the matrix 
 * corresponding to a single probeset, log2 transform each data item and then compute 1-step Tukey Biweight expression measure. 
 * Note that data is a probes by chips matrix.
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 *
 *  
 */

void TukeyBiweight_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

/*! \brief Use a 1-step Tukey Biweight to summarize each column
 *
 * Given a data matrix of probe intensities, and a list of rows in the matrix 
 * corresponding to a single probeset, compute 1-step Tukey Biweight expression measure. 
 * Note that data is a probes by chips matrix.
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 *  
 */

void TukeyBiweight_no_log_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

/*! \brief compute a 1-step Tukey Biweight
 *
 *
 * implements one step Tukey Biweight as documented in the Affymetrix 
 * Statistical Algorithms Description Document. 
 *
 * @param x  vector of data
 * @param length length of vector of data
 *
 */

double Tukey_Biweight(double *x, int length);

#endif
