/*! \file rma_background4.h
    \brief Functions for computing and carrying out the RMA convolution background method.
    
    
*/

#ifndef RMA_BACKGROUND4_H
#define RMA_BACKGROUND4_H


#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>


/*! \brief Compute the parameters for the RMA background correction model
 *
 *
 *  Given a data matrix, compute the RMA convolution model parameters. The   
 *  three parameters estimated are alpha, mu and sigma (and are returned in that order)
 * 
 *
 *
 * @param PM a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param param a vector of length 3 where parameters for specified column will be stored on output
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param column specifies which column to compute parameters for. Should be 0-(cols-1)
 *
 */

void rma_bg_parameters(double *PM,double *param, int rows, int cols, int column);


/*! \brief Carryout the RMA background correction for a specified column.
 *
 *
 *  Given a data matrix and the RMA convolution model parameters for a specified column 
 * adjust that column using the RMA convolution model. Ie E(Signal | Observed, model parameters)   
 * 
 *
 *
 * @param PM a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param param a vector of length 3 where parameters for specified column will be stored on output
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param column specifies which column to compute parameters for. Should be 0-(cols-1)
 *
 */

void rma_bg_adjust(double *PM, double *param, int rows, int cols, int column);

/*! \brief Carryout the RMA background correction for each column of a matrix
 *
 *
 * Given a data matrix background adjust each column using the RMA convolution model. Ie E(Signal | Observed, model parameters) where the model is Observed = Signal + background, signal is assumed to be exponential
 * and background is normally distributed. 
 * 
 *
 *
 * @param PM a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 *
 */



void rma_bg_correct(double *PM, int rows, int cols);

SEXP R_rma_bg_correct(SEXP PMmat,SEXP copy);


#endif
