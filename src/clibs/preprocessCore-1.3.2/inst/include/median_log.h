/*! \file median_log.h
    \brief Functions for column wise summarizing a matrix by computing the median of \f$\log_2\f$ transformed data     
*/

#ifndef MEDIAN_LOG_H
#define MEDIAN_LOG_H 1

/*! \brief  \f$\log_2\f$ transform the data and compute the median 
 * 
 *  Given a data matrix of probe intensities \f$\log_2\f$ transform it and then compute the median. Also compute SE of this estimate
 *  on a column by column basis using only a specified subset of rows. Specifically, the median of each column is based on
 *  \f$\log_2\f$ transformed data. The sample standard error is also computed. 
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output log2 medians. Should be of length cols
 * @param nprobes the number of rows in cur_rows
 * @param resultsSE pre-allocated space to store SE of log2 medians. Should be of length cols
 *
 *  
 */

void MedianLog(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);

/*! \brief  \f$\log_2\f$ transform the data and compute the median 
 * 
 *  Given a data matrix of probe intensities \f$\log_2\f$ transform it and then compute the median on a column by column basis using only a specified subset of rows. 
 *  Specifically, the median of each column is based on \f$\log_2\f$ transformed data.
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output log2 medians. Should be of length cols
 * @param nprobes the number of rows in cur_rows
 *  
 */

void MedianLog_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

/*! \brief compute the median for each column of \f$\log_2\f$ transformed data.
 * 
 *  Given a data matrix of probe intensities \f$\log_2\f$ transform it then compute median of each column. Also produce the SE of this estimate
 *  on a column by column basis. Specifically, the median is computed for each column and then \f$\log_2\f$ transformed.
 *  The sample standard error is also computed. On output the data matrix will
 *  be unchanged.
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output log2 medians. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of log2 medians. Should be of length cols
 *
 *  
 */

void medianlog(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief compute the median for each column of \f$\log_2\f$ transformed data.
 * 
 *  Given a data matrix of probe intensities \f$\log_2\f$ transform it then compute median of each column. Also produce the SE of this estimate
 *  on a column by column basis. Specifically, the median is computed for each column and then \f$\log_2\f$ transformed.
 *  The sample standard error is also computed. On output the data matrix will
 *  be changed.
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output log2 medians. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of log2 medians. Should be of length cols
 *
 *  
 */

void medianlog_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);




#endif
