/*! BIOLIB 'C' interface to affyio - for linking against the Bio* languages
 *
 * Author: Pjotr Prins 2008
 */

#include <stdlib.h>
#include <string.h>
#include <R.h>  // For R's Free function only
#include <biolib_preprocesscore.h>

/*!
 * Perform RMA on a matrix of probeset (rows).
 *
 * @param matrix
 * @param num_probesets
 * @param num_probes
 * @param backgroundcorrect 0: don't correct, 1: RMA
 * @param normalize 0: no, 1: quantile
 * @param destructive changes the matrix structure in place
 *
 * @return pointer to array of probeset RMA values
 * 
 */

double *rma(double *matrix, unsigned int num_probesets, unsigned int num_probes, 
         int backgroundcorrect, int normalize, bool destructive)
{
  double *work_matrix = matrix;
  if (!destructive) {
    // allocate new matrix
  }
  if (backgroundcorrect == 1) {
    rma_bg_correct(double *PM, int rows, int cols);
  }
  if (normalize == 1) {
    if (qnorm_c(double *data, int *rows, int *cols) == 1) {
      // raise PROBLEM
    }
  }
  // for every probeset do
  MedianPolish(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE);
  if (!destructive) {
    // free work matrix
  }
}


