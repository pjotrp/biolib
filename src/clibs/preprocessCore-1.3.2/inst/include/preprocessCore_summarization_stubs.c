#include <Rinternals.h>
#include <R_ext/Rdynload.h>

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

void averagelog_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double*, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, double *, double *))R_GetCCallable("preprocessCore","averagelog_no_copy");
  
  fun(data,rows,cols,results,resultsSE);
  return;
}

/*! \brief log2 transform and then compute the mean and SE of the mean
 * 
 *  Given a data matrix of probe intensities compute average log2 expression measure and SE of this estimate
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

void averagelog(double *data, int rows, int cols, double *results, double *resultsSE){


  static void(*fun)(double*, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, double *, double *))R_GetCCallable("preprocessCore","averagelog");
  
  fun(data,rows,cols,results,resultsSE);
  return;
}

/*! \brief log2 transform and then compute the mean and SE of the mean
 *
 * Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute average log2 expression measure. 
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

void AverageLog(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){

  static void(*fun)(double*, int, int, int*, double *, int, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, int*, double *, int, double *))R_GetCCallable("preprocessCore","AverageLog");
  
  fun(data,rows,cols,cur_rows,results,nprobes,resultsSE);
  return;
}

/*! \brief log2 transform and then compute the mean
 *
 *  Given a data matrix of probe intensities, and a list of rows in the matrix 
 *  corresponding to a single probeset, compute average log2 expression measure. 
 *  Note that data is a probes by chips matrix. 
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

void AverageLog_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){
  

  static void(*fun)(double*, int, int, int*, double *, int) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, int*, double *, int))R_GetCCallable("preprocessCore","AverageLog_noSE");
  fun(data,rows,cols,cur_rows,results,nprobes);
  return;
}

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

void logaverage(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double*, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, double *, double *))R_GetCCallable("preprocessCore","logaverage");
  fun(data,rows,cols,results,resultsSE);
  return;
}

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

void LogAverage(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){


  static void(*fun)(double*, int, int, int*, double *, int, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, int*, double *, int, double *))R_GetCCallable("preprocessCore","LogAverage");
  fun(data, rows, cols, cur_rows, results, nprobes, resultsSE);
  return;
}

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

void LogAverage_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){


  static void(*fun)(double*, int, int, int*, double *, int) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, int*, double *, int))R_GetCCallable("preprocessCore","LogAverage_noSE");
  fun(data, rows, cols, cur_rows, results, nprobes);
  return;
}

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

void tukeybiweight(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double *, int, int, double *, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *))R_GetCCallable("preprocessCore","tukeybiweight");
  fun(data, rows, cols, results, resultsSE);
  return;
}

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

void tukeybiweight_no_log(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double *, int, int, double *, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *))R_GetCCallable("preprocessCore","tukeybiweight_no_log");
  fun(data, rows, cols, results, resultsSE);
  return;
}

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

void TukeyBiweight(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){


  static void(*fun)(double *, int, int, int *, double *, int, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int, double *))R_GetCCallable("preprocessCore","TukeyBiweight");
  fun(data, rows, cols, cur_rows,results, nprobes, resultsSE);
  return;
}

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

void TukeyBiweight_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){


  static void(*fun)(double *, int, int, int *, double *, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int))R_GetCCallable("preprocessCore","TukeyBiweight_noSE");
  fun(data, rows, cols, cur_rows,results, nprobes);
  return;
}

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

void TukeyBiweight_no_log_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){


  static void(*fun)(double *, int, int, int *, double *, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int))R_GetCCallable("preprocessCore","TukeyBiweight_no_log_noSE");
  fun(data, rows, cols, cur_rows,results, nprobes);
  return;
}


/*! \brief compute a 1-step Tukey Biweight
 *
 *
 * implements one step Tukey Biweight as documented in the Affymetrix 
 * Statistical Algorithms Description Document. 
 *
 * @param x  vector of data
 * @param length  length of vector of data
 *
 */

double Tukey_Biweight(double *x, int length){

  static double(*fun)(double *, int) = NULL;

  if (fun == NULL)
    fun = (double (*)(double *, int))R_GetCCallable("preprocessCore","Tukey_Biweight");

  return fun(x,length);

}


void lm_wfit(double *x, double *y, double *w, int rows, int cols, double tol, double *out_beta, double *out_resids){

  static void(*fun)(double *, double *, double *, int, int, double, double *, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, double *, double *, int, int, double, double *, double *))R_GetCCallable("preprocessCore","lm_wfit");

  fun(x,y,w,rows,cols,tol,out_beta,out_resids);
  return;

}




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

void median_polish_fit_no_copy(double *data, int rows, int cols, double *r, double *c, double *t){


  static void(*fun)(double *, int, int, double *, double *, double*) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double*))R_GetCCallable("preprocessCore","median_polish_fit_no_copy");

  fun(data, rows, cols, r, c, t);
  return;

}

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

void median_polish_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double *, int, int, double *, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *))R_GetCCallable("preprocessCore","median_polish_no_copy");
  fun(data,rows,cols,results,resultsSE);
  return;

}

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

void median_polish_log2_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){
  
  static void(*fun)(double *, int, int, double *, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *))R_GetCCallable("preprocessCore","median_polish_log2_no_copy");
  fun(data,rows,cols,results,resultsSE);
  return;

}

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

void median_polish_log2(double *data, int rows, int cols, double *results, double *resultsSE, double *residuals){

  static void(*fun)(double *, int, int, double *, double *, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *))R_GetCCallable("preprocessCore","median_polish_log2");
  
  fun(data,rows,cols,results,resultsSE,residuals);
  return;

}

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

void median_polish(double *data, int rows, int cols, double *results, double *resultsSE, double *residuals){

  static void(*fun)(double *, int, int, double *, double *, double *) = NULL;
  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *))R_GetCCallable("preprocessCore","median_polish");
  
  fun(data,rows,cols,results,resultsSE,residuals);
  return;
}

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


void MedianPolish(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){


  static void(*fun)(double *, int, int, int *, double *, int, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int, double *))R_GetCCallable("preprocessCore","MedianPolish");

  fun(data,rows,cols,cur_rows,results,nprobes,resultsSE);
  return;

}

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

void MedianPolish_no_log(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){


  static void(*fun)(double *, int, int, int *, double *, int, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int, double *))R_GetCCallable("preprocessCore","MedianPolish_no_log");

  fun(data,rows,cols,cur_rows,results,nprobes,resultsSE);
  return;

}




void rlm_fit(double *x, double *y, int rows, int cols, double *out_beta, double *out_resids, double *out_weights, double (* PsiFn)(double, double, int), double psi_k, int max_iter,int initialized){

  static void(*fun)(double *, double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","rlm_fit");
  
  fun(x, y, rows, cols, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;


}



void rlm_wfit(double *x, double *y, double *w, int rows, int cols, double *out_beta, double *out_resids, double *out_weights, double (* PsiFn)(double, double, int), double psi_k, int max_iter,int initialized){

  static void(*fun)(double *, double *, double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;


  if (fun == NULL)
    fun = (void(*)(double *, double *, double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","rlm_wfit");

  fun(x, y, w, rows, cols, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;




}



double med_abs(double *x, int length){
  static double(*fun)(double *, int) = NULL;


  if (fun == NULL)
    fun = (double(*)(double *, int))R_GetCCallable("preprocessCore","med_abs");


  return fun(x, length);




}



void rlm_fit_anova(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){


  static void(*fun)(double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;


  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","rlm_fit_anova");

  fun(y, y_rows, y_cols, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}


void rlm_wfit_anova(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){
  
  static void(*fun)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;


  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","rlm_wfit_anova");

  fun(y, y_rows, y_cols, w, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;


}


void rlm_compute_se(double *X,double *Y, int n, int p, double *beta, double *resids,double *weights,double *se_estimates,double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k){
  
  static void(*fun)(double *,double *, int, int, double *, double *, double *, double *, double *, double *, int, double (*)(double, double, int), double) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *,double *, int, int, double *, double *, double *, double *, double *, double *, int, double (*)(double, double, int), double))R_GetCCallable("preprocessCore","rlm_compute_se");
  fun(X, Y, n, p, beta, resids, weights, se_estimates, varcov, residSE, method, PsiFn, psi_k);
  return;

}


void rlm_compute_se_anova(double *Y, int y_rows,int y_cols, double *beta, double *resids,double *weights,double *se_estimates, double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k){

  static void(*fun)(double *, int, int, double *, double *,double *,double *, double *, double *, int, double (*)(double, double, int), double) = NULL;
  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *,double *,double *, double *, double *, int, double (*)(double, double, int), double))R_GetCCallable("preprocessCore","rlm_compute_se_anova");

  fun(Y, y_rows, y_cols, beta, resids, weights, se_estimates, varcov, residSE, method, PsiFn, psi_k);
  return;

}

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

void MedianLog(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){

  static void(*fun)(double *, int, int, int *, double *, int, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int, double *))R_GetCCallable("preprocessCore","MedianLog");
  fun(data, rows, cols, cur_rows, results, nprobes, resultsSE);
  return;

}

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

void MedianLog_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){

  static void(*fun)(double *, int, int, int *, double *, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int))R_GetCCallable("preprocessCore","MedianLog_noSE");
  fun(data, rows, cols, cur_rows, results, nprobes);
  return;

}

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



void medianlog(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double *, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *))R_GetCCallable("preprocessCore","medianlog");
  fun(data, rows, cols, results, resultsSE);
  return;

}

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

void medianlog_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double *, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *))R_GetCCallable("preprocessCore","medianlog_no_copy");
  fun(data, rows, cols, results, resultsSE);
  return;

}

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
 * @param nprobes the number of rows in cur_rows
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols
 *
 *  
 */

void LogMedian(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){

  static void(*fun)(double *, int, int, int *, double *, int, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int, double *))R_GetCCallable("preprocessCore","LogMedian");
  fun(data, rows, cols, cur_rows, results, nprobes, resultsSE);
  return;

}

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


void LogMedian_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){

  static void(*fun)(double *, int, int, int *, double *, int, double *) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, int *, double *, int, double *))R_GetCCallable("preprocessCore","LogMedian_noSE");
  fun(data, rows, cols, cur_rows, results, nprobes, resultsSE);
  return;

}

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

void logmedian(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double *, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *))R_GetCCallable("preprocessCore","logmedian");
  fun(data, rows, cols, results, resultsSE);
  return;

}

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

void logmedian_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double *, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *))R_GetCCallable("preprocessCore","logmedian_no_copy");
  fun(data, rows, cols, results, resultsSE);
  return;

}


/*! \brief Compute the mean and SE of the mean
 * 
 *  Given a data matrix of probe intensities compute average log2 expression measure and SE of this estimate
 *  on a column by column basis. Specifically, each element is log2 transformed, then the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. This function guarantees that 
 *  no additional memory is temporarily allocated to copy the input data matrix. However, this means that
 *  on output the input matrix may be changed.
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

void colaverage_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double*, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, double *, double *))R_GetCCallable("preprocessCore","colaverage_no_copy");
  
  fun(data,rows,cols,results,resultsSE);
  return;
}

/*! \brief Compute the mean and SE of the mean
 * 
 *  Given a data matrix of probe intensities compute average log2 expression measure and SE of this estimate
 *  on a column by column basis. Specifically, each element is log2 transformed, then the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. This function guarantees that 
 *  no additional memory is temporarily allocated to copy the input data matrix. However, this means that
 *  on output the input matrix may be changed.
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

void colaverage(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double*, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, double *, double *))R_GetCCallable("preprocessCore","colaverage");
  
  fun(data,rows,cols,results,resultsSE);
  return;
}


/*! \brief Compute the mean and SE of the mean for subset of rows
 * 
 *  Given a data matrix of probe intensities compute averageexpression measure and SE of this estimate
 *  on a column by column basis using only a specified subset of rows. Specifically, the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. 
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output averages. Should be of length cols
 * @param nprobes the number of elements in cur_rows
 * @param resultsSE pre-allocated space to store SE of averages. Should be of length cols
 *
 *  
 */

void ColAverage(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){

  static void(*fun)(double*, int, int, int*, double *, int, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, int*, double *, int, double *))R_GetCCallable("preprocessCore","ColAverage");
  
  fun(data, rows, cols, cur_rows, results, nprobes, resultsSE);
  return;
}

/*! \brief compute the mean for specified subset of rows
 * 
 *  Given a data matrix of probe intensities compute average expression measure and SE of this estimate
 *  on a column by column basis using only a specified subset of rows. Specifically, the arithmetic mean
 *  is computed for each column. The sample standard error is also computed. 
 *    
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows indices specifying which rows in the matrix to use
 * @param results pre-allocated space to store output averages. Should be of length cols
 * @param nprobes the number of elements in cur_rows
 *
 *
 *  
 */

void ColAverage_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){

  static void(*fun)(double*, int, int, int*, double *, int) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, int*, double *, int))R_GetCCallable("preprocessCore","ColAverage_noSE");
  
  fun(data, rows, cols, cur_rows, results, nprobes);
  return;
}

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

void colmedian_no_copy(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double*, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, double *, double *))R_GetCCallable("preprocessCore","colmedian_no_copy");
  
  fun(data,rows,cols,results,resultsSE);
  return;
}

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

void colmedian(double *data, int rows, int cols, double *results, double *resultsSE){

  static void(*fun)(double*, int, int, double *, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, double *, double *))R_GetCCallable("preprocessCore","colmedian");
  
  fun(data,rows,cols,results,resultsSE);
  return;
}


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

void ColMedian(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){

  static void(*fun)(double*, int, int, int*, double *, int, double *) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, int*, double *, int, double *))R_GetCCallable("preprocessCore","ColMedian");
  
  fun(data, rows, cols, cur_rows, results, nprobes, resultsSE);
  return;
}

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

void ColMedian_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){

  static void(*fun)(double*, int, int, int*, double *, int) = NULL;
  
  if (fun == NULL)
    fun =  (void(*)(double*, int, int, int*, double *, int))R_GetCCallable("preprocessCore","ColMedian_noSE");
  
  fun(data, rows, cols, cur_rows, results, nprobes);
  return;
}


/*! \brief robust linear regression fit row-colum model using PLM-r
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows and/or columns when a siginficant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */



void plmr_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){


  static void(*fun)(double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","plmr_fit");

  fun(y, y_rows, y_cols, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}

/*! \brief robust linear regression fit row-colum model using PLM-r
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows and/or columns when a siginficant number of probes are poorly performing
 *
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param w  weights for each observation: length y_rows*y_cols
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */


void plmr_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){


  
  static void(*fun)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","plmr_wfit");
  
  fun(y, y_rows, y_cols, w, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}




/*! \brief robust linear regression fit row-colum model using PLM-rr
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmrr_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){


  static void(*fun)(double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","plmrr_fit");

  fun(y, y_rows, y_cols, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}


/*! \brief robust linear regression fit row-colum model using PLM-rc
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmrc_fit(double *y, int y_rows, int y_cols,double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){
  
  static void(*fun)(double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","plmrc_fit");
  
  fun(y, y_rows, y_cols, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}


/*! \brief robust linear regression fit row-colum model using PLM-rr
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire rows when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param w  weights for each observation: length y_rows*y_cols
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmrr_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){

  static void(*fun)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","plmrr_wfit");
  
  fun(y, y_rows, y_cols, w, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}



/*! \brief robust linear regression fit row-colum model using PLM-rc
 *
 * Fits the model y = cols + rows + errors with constraint sum rows = 0. PLM-r (Probe Level Model-robust) attempts
 * to dyamically downweight entire columns when a significant number of probes are poorly performing
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param w  weights for each observation: length y_rows*y_cols
 * @param out_beta  place to output beta estimates: length (y_rows + y_cols -1)
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void plmrc_wfit(double *y, int y_rows, int y_cols, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double, double, int), double psi_k,int max_iter, int initialized){
  
  static void(*fun)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","plmrc_wfit");
  
  fun(y, y_rows, y_cols, w, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}


/*! \brief apply row effects of a robust linear regression fit row-colum model
 *
 * Using pre-computed row effects from the model y = cols + rows + errors with constraint sum rows = 0
 * apply on a single column by column basis to robustly estimate col effects for each column
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param probe_effects  previously computed row effects with length y_rows. Assumed that it sums to 0.
 * @param out_beta  place to output beta estimates: length y_cols
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void rlm_fit_anova_given_probe_effects(double *y, int y_rows, int y_cols, double *probe_effects, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double,double, int), double psi_k,int max_iter, int initialized){

  static void(*fun)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","rlm_fit_anova_given_probe_effects");
  
  fun(y, y_rows, y_cols, probe_effects, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}

/*! \brief Estimate SE for robust linear regression fit using iteratively reweighted least squares
 *
 * Specialized to the model y = cols + rows + error model where the rows parameters are previously specified
 * designed to work independently for each column so can be applied "chip by chip"
 * 
 * @param Y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param probe_effects previously computed row effects with length y_rows. Assumed that it sums to 0.
 * @param beta  fitted parameter estimates: length y_rows + y_cols -1
 * @param resids estimated residuals: length y_rows*y_cols
 * @param weights  estimated weights: length y_rows*y_cols
 * @param se_estimates on output contains standard error estimates : y_rows + y_cols -1
 * @param varcov a place to store estimated variance covariance matrix: dimension (y_rows + y_cols -1)*(y_rows + y_cols -1) (or set to NULL)
 * @param residSE estimated residual standard error
 * @param method should be integer 1,2,3 or 4 (4 is the default). Currently ignored.
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 *
 */




void rlm_compute_se_anova_given_probe_effects(double *Y, int y_rows,int y_cols, double *probe_effects,double *beta, double *resids,double *weights,double *se_estimates, double *varcov, double *residSE, int method,double (* PsiFn)(double, double, int), double psi_k){

  static void(*fun)(double *, int, int,  double *, double *, double *,double *,double *, double *, double *, int, double (*)(double, double, int), double) = NULL;
  
  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *,double *, double *,double *,double *, double *, double *, int, double (*)(double, double, int), double))R_GetCCallable("preprocessCore","rlm_compute_se_anova_given_probe_effects");

  fun(Y, y_rows, y_cols, probe_effects, beta, resids, weights, se_estimates, varcov, residSE, method, PsiFn, psi_k);
  return;

}





/*! \brief apply row effects of a robust linear regression fit row-colum model
 *
 * Using pre-computed row effects from the model y = cols + rows + errors with constraint sum rows = 0
 * apply on a single column by column basis to robustly estimate col effects for each column
 *
 * @param y  dependent variable: length y_rows*y_cols
 * @param y_rows  dimension of input
 * @param y_cols  dimension of input
 * @param probe_effects  previously computed row effects with length y_rows. Assumed that it sums to 0.
 * @param w  weights for each observation: length y_rows*y_cols
 * @param out_beta  place to output beta estimates: length y_cols
 * @param out_resids  place to output residuals: length y_rows*y_cols
 * @param out_weights  place to output weights: length y_rows*y_cols
 * @param PsiFn  a function used to determine weights based on standardized residuals
 * @param psi_k  a tuning parameter for the PsiFn
 * @param max_iter  maximum number of iterations (if don't converge before)
 * @param initialized  do we have initial estimates of beta 
 *
 */

void rlm_wfit_anova_given_probe_effects(double *y, int y_rows, int y_cols, double *probe_effects, double *w, double *out_beta, double *out_resids, double *out_weights,double (* PsiFn)(double,double, int), double psi_k,int max_iter, int initialized){

  static void(*fun)(double *, int, int, double *, double *, double *, double *, double *, double (*)(double, double, int), double, int, int) = NULL;

  if (fun == NULL)
    fun = (void(*)(double *, int, int, double *, double *, double *, double *, double *, double (*)(double, double, int), double, int, int))R_GetCCallable("preprocessCore","rlm_wfit_anova_given_probe_effects");
  
  fun(y, y_rows, y_cols, probe_effects, w, out_beta, out_resids,out_weights, PsiFn, psi_k, max_iter, initialized);
  return;

}
