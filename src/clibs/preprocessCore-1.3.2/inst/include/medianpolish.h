/*! \file medianpolish.h
    \brief Functions for column wise summarizing a matrix by using the median polish algorithm
    
    
*/

#ifndef MEDIANPOLISH_H
#define MEDIANPOLISH_H 1

/*! \brief Compute medianpolish  
 *
 *
 *      Given a data matrix, compute median polish parameter estimates 
 *      Note that data is a probes by chips matrix. Also compute SE estimates. 
 *      The input data matrix contains the fitted residuals on output.
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param r pre-allocated space to store estimated row effects. Should be of length rows. Assumed on input that this is zero-ed out.
 * @param c pre-allocated space to store estimated column effects. Should be of length cols. Assumed on input that this is zero-ed out.
 * @param t pre-allocated space to store "intercept" effect. Should be of length 1.
 *
 */

void median_polish_fit_no_copy(double *data, int rows, int cols, double *r, double *c, double *t);

/*! \brief Compute medianpolish  
 *
 *
 *      Given a data matrix of probe intensities, compute median polish expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates. 
 *      The input data matrix contains the fitted residuals on output.
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols. Note that this is just NA values
 *  
 */

void median_polish_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief Compute medianpolish  
 *
 *
 *      Given a data matrix of probe intensities, compute median polish expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates. This function
 *      \f$\log_2\f$ transforms its input before apply the median polish. The input data matrix
 *      contains the fitted residuals on output.
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols. Note that this is just NA values
 *  
 */

void median_polish_log2_no_copy(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief Compute medianpolish  
 *
 *
 *      Given a data matrix of probe intensities, compute median polish expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates. This function
 *      \f$\log_2\f$ transforms its input before apply the median polish.
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols. Note that this is just NA values
 * @param residuals pre-allocated space to store the redsiuals. Should be of length rows*cols
 *  
 */

void median_polish_log2(double *data, int rows, int cols, double *results, double *resultsSE, double *residuals);

/*! \brief Compute medianpolish  
 *
 *
 *      Given a data matrix of probe intensities, compute median polish expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates.
 *      
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols. Note that this is just NA values
 * @param residuals pre-allocated space to store the redsiuals. Should be of length rows*cols
 *  
 */

void median_polish(double *data, int rows, int cols, double *results, double *resultsSE, double *residuals);

/*! \brief Compute medianpolish  
 *
 *
 *      Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute median polish expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates. This function
 *      \f$\log_2\f$ transforms its inpue before apply the median polish.
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols. Note that this is just NA values
 *
 *  
 */

void MedianPolish(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);

/*! \brief Compute medianpolish  
 *
 *
 *      Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute median polish expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols. Note that this is just NA values
 *
 *  
 */

void MedianPolish_no_log(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);


#endif
