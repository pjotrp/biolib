/*! \file log_avg.h
    \brief Functions for column wise summarizing a matrix by averaging and then \f$log2\f$ transforming the computed mean
    
    
*/

#ifndef LOG_AVG_H
#define LOG_AVG_H 

/*! \brief compute the mean then log2 transform and also SE of the log2 mean
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

void logaverage(double *data, int rows, int cols, double *results, double *resultsSE);

/*! \brief compute the average and then log2 transform it.
 *
 * Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute log2 average expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates
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

void LogAverage(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);


/*! \brief compute the average and then log2 transform it.
 *
 * Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute log2 average expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates
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

void LogAverage_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes);

#endif
