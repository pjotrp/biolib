/*! \file median.h
    \brief Functions for column wise summarizing a matrix by using the median
        
*/

#ifndef MEDIAN_H
#define MEDIAN_H 1

/*! \brief Compute the median and SE of the median for subset of rows
 * 
 *  Given a data matrix of probe intensities compute median and SE of this estimate
 *  on a column by column basis using only a specified subset of rows. Specifically, the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. 
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output medians. Should be of length cols
 * @param nprobes the number of elements in cur_rows
 * @param resultsSE pre-allocated space to store SE of medians. Should be of length cols
 *
 *  
 */

void ColMedian(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);

/*! \brief compute the median for specified subset of rows
 * 
 *  Given a data matrix of probe intensities compute median expression measure 
 *  on a column by column basis using only a specified subset of rows. Specifically, the median
 *  is computed for each column.  
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output medians. Should be of length cols
 * @param nprobes the number of elements in cur_rows
 *
 *
 *  
 */

void ColMedian_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

/*! \brief Compute the median and SE of the median
 * 
 *  Given a data matrix of probe intensities compute median measure and SE of this estimate
 *  on a column by column basis. Specifically, each element is log2 transformed, then the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. This function guarantees that 
 *  no additional memory is temporarily allocated to copy the input data matrix. However, this means that
 *  on output the input matrix will be unchanged.
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

void colmedian(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief Compute the median and SE of the median
 * 
 *  Given a data matrix of probe intensities compute median measure and SE of this estimate
 *  on a column by column basis. The sample standard error is also computed. On output the data matrix will
 *  be changed.
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output averages. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of averages. Should be of length cols
 *
 *  
 */

void colmedian_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);




#endif
