/*! \file log_median.h
    \brief Functions for column wise summarizing a matrix by computing the median and then \f$\log_2\f$ transforming
        
*/



#ifndef LOG_MEDIAN_H
#define LOG_MEDIAN_H 1

/*! \brief compute the median for subset of rows and the \f$\log_2\f$ transform it
 * 
 *  Given a data matrix of probe intensities compute median and then \f$\log_2\f$ transform it. Also compute SE of this estimate
 *  on a column by column basis using only a specified subset of rows. Specifically, the median of each column is computed
 *  the it is \f$\log_2\f$ transformed. The sample standard error is also computed. 
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes the number of 
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols
 *
 *  
 */

void LogMedian(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);

/*! \brief compute the median for subset of rows and the \f$\log_2\f$ transform it
 * 
 *  Given a data matrix of probe intensities compute median and then \f$\log_2\f$ transform it. Computed on a column by column basis using only a specified subset of rows. 
 * Specifically, the median of each column is computed
 *  the it is \f$\log_2\f$ transformed.
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes the number of rows in cur_rows
 *
 *  
 */

void LogMedian_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

/*! \brief compute the median for each column and then \f$\log_2\f$ transform it
 * 
 *  Given a data matrix of probe intensities compute median and then \f$\log_2\f$ transform it. Also produce the SE of this estimate
 *  on a column by column basis. Specifically, the median is computed for each column and then \f$\log_2\f$ transformed.
 *  The sample standard error is also computed. On output the data matrix will
 *  be unchanged.
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

void logmedian(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief compute the median for each column and then \f$\log_2\f$ transform it
 * 
 *  Given a data matrix of probe intensities compute median and then \f$\log_2\f$ transform it. Also produce the SE of this estimate
 *  on a column by column basis. Specifically, the median is computed for each column and then \f$\log_2\f$ transformed.
 *  The sample standard error is also computed. On output the data matrix will
 *  be changed.  
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

void logmedian_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);

#endif
