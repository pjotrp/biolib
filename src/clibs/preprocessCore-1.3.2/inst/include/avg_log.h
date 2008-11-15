/*! \file avg_log.h
    \brief Functions for column wise summarizing a matrix by \f$log2\f$ transforming the data and then averaging
    
    
*/


#ifndef AVG_LOG_H
#define AVG_LOG_H

/*! \brief log2 transform and then compute the mean and SE of the mean for subset of rows
 * 
 *  Given a data matrix of probe intensities compute average log2 expression measure and SE of this estimate
 *  on a column by column basis using only a specified subset of rows. Specifically, each element is log2 transformed, then the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. 
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

void AverageLog(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);

/*! \brief log2 transform and then compute the mean for subset of rows
 * 
 *  Given a data matrix of probe intensities compute average log2 expression measure and SE of this estimate
 *  on a column by column basis using only a specified subset of rows. Specifically, each element is log2 transformed, then the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. 
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes the number of 
 *
 *
 *  
 */

void AverageLog_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

/*! \brief log2 transform and then compute the mean and SE of the mean
 * 
 *  Given a data matrix of probe intensities compute average log2 expression measure and SE of this estimate
 *  on a column by column basis. Specifically, each element is log2 transformed, then the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. This function guarantees that 
 *  no additional memory is temporarily allocated to copy the input data matrix. However, this means that
 *  on output the input matrix will be changed.
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

void averagelog_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief log2 transform and then compute the mean and SE of the mean
 * 
 *  Given a data matrix of probe intensities compute average log2 expression measure and SE of this estimate
 *  on a column by column basis. Specifically, each element is log2 transformed, then the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. On output the data matrix will
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

void averagelog(double *data, int rows, int cols, double *results, double *resultsSE);

#endif
