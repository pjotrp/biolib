/*****************************************************
 **
 ** file: init_package.c
 **
 ** Copyright (C) 2007-2008    B. M. Bolstad
 **
 ** aim: Register c code routines so that they can be called in other packages.
 **"
 ** History
 ** May 20, 2007 - Initial version
 ** May 24-27, 2007 - add in additional registered functions
 ** Sep 9, 2007 - add the R_rlm_rma_default and R_wrlm_rma_default_model as registered functions
 ** Sep 10, 2007 - add logmedian medianlog dunctions
 ** Mar 11, 2007 - add R_rlm_rma_given_probe_effects etc functions
 **
 *****************************************************/

#include "qnorm.h"
#include "medianpolish.h"

#include "log_avg.h"
#include "avg_log.h"
#include "avg.h"

#include "median_log.h"
#include "log_median.h"
#include "median.h"

#include "biweight.h"
#include "lm.h"
#include "rlm.h"
#include "rlm_se.h"

#include "R_rlm_interfaces.h"
#include "R_colSummarize.h"
#include "R_subColSummarize.h"

#include "plmr.h"
#include "R_plmr_interfaces.h"

#include "rma_background4.h"


#include <R_ext/Rdynload.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <R_ext/RConverters.h>


#if _MSC_VER >= 1000
__declspec(dllexport)
#endif


static const R_CallMethodDef callMethods[]  = {
  {"R_qnorm_c",(DL_FUNC)&R_qnorm_c,2},
  {"R_qnorm_robust_weights", (DL_FUNC)&R_qnorm_robust_weights, 3},
  {"R_qnorm_robust_c",(DL_FUNC)&R_qnorm_robust_c,6},
  {"R_qnorm_determine_target",(DL_FUNC)&R_qnorm_determine_target,2},
  {"R_qnorm_using_target",(DL_FUNC)&R_qnorm_using_target,3},
  {"R_qnorm_within_blocks",(DL_FUNC)&R_qnorm_within_blocks,3},
  {"R_rlm_rma_default_model",(DL_FUNC)&R_rlm_rma_default_model,3},
  {"R_wrlm_rma_default_model", (DL_FUNC)&R_wrlm_rma_default_model,4},
  {"R_medianpolish_rma_default_model", (DL_FUNC)&R_medianpolish_rma_default_model,1},
  {"R_colSummarize_avg_log", (DL_FUNC)&R_colSummarize_avg_log,1},  
  {"R_colSummarize_log_avg", (DL_FUNC)&R_colSummarize_log_avg,1},
  {"R_colSummarize_median_log", (DL_FUNC)&R_colSummarize_median_log,1},
  {"R_colSummarize_log_median", (DL_FUNC)&R_colSummarize_log_median,1},
  {"R_colSummarize_biweight_log", (DL_FUNC)&R_colSummarize_biweight_log,1},
  {"R_colSummarize_medianpolish_log",(DL_FUNC)&R_colSummarize_medianpolish_log,1},  
  {"R_colSummarize_avg",(DL_FUNC)&R_colSummarize_avg,1},
  {"R_colSummarize_median",(DL_FUNC)&R_colSummarize_median,1},
  {"R_colSummarize_biweight", (DL_FUNC)&R_colSummarize_biweight,1},
  {"R_colSummarize_medianpolish",(DL_FUNC)&R_colSummarize_medianpolish,1},
  {"R_subColSummarize_avg_log", (DL_FUNC)&R_subColSummarize_avg_log,2},  
  {"R_subColSummarize_log_avg", (DL_FUNC)&R_subColSummarize_log_avg,2},
  {"R_subColSummarize_avg", (DL_FUNC)&R_subColSummarize_avg,2},
  {"R_subColSummarize_biweight_log", (DL_FUNC)&R_subColSummarize_biweight_log,2},
  {"R_subColSummarize_biweight", (DL_FUNC)&R_subColSummarize_biweight,2},
  {"R_subColSummarize_median_log", (DL_FUNC)&R_subColSummarize_median_log,2},
  {"R_subColSummarize_log_median", (DL_FUNC)&R_subColSummarize_log_median,2},
  {"R_subColSummarize_median",(DL_FUNC)&R_subColSummarize_median,2},
  {"R_subColSummarize_medianpolish_log",(DL_FUNC)&R_subColSummarize_medianpolish_log,2},
  {"R_subColSummarize_medianpolish",(DL_FUNC)&R_subColSummarize_medianpolish,2},
  {"R_plmr_model",(DL_FUNC)&R_plmr_model,3},
  {"R_wplmr_model", (DL_FUNC)&R_wplmr_model,4},
  {"R_plmrr_model",(DL_FUNC)&R_plmrr_model,3},
  {"R_wplmrr_model", (DL_FUNC)&R_wplmrr_model,4},
  {"R_plmrc_model",(DL_FUNC)&R_plmrc_model,3},
  {"R_wplmrc_model", (DL_FUNC)&R_wplmrc_model,4},
  {"R_rlm_rma_given_probe_effects", (DL_FUNC)&R_rlm_rma_given_probe_effects,4},
  {"R_rlm_rma_given_probe_effects", (DL_FUNC)&R_wrlm_rma_given_probe_effects,5},
  {"R_rma_bg_correct",(DL_FUNC)&R_rma_bg_correct,2},
  {NULL, NULL, 0}
  };

void R_init_preprocessCore(DllInfo *info){

  R_registerRoutines(info, NULL, callMethods, NULL, NULL);


  /* The normalization routines */
  R_RegisterCCallable("preprocessCore", "qnorm_c", (DL_FUNC)&qnorm_c);
  R_RegisterCCallable("preprocessCore", "R_qnorm_robust_weights", (DL_FUNC)&R_qnorm_robust_weights);
  R_RegisterCCallable("preprocessCore", "qnorm_robust_c", (DL_FUNC)&qnorm_robust_c);
  R_RegisterCCallable("preprocessCore", "qnorm_c_using_target", (DL_FUNC)&qnorm_c_using_target);
  R_RegisterCCallable("preprocessCore", "qnorm_c_determine_target", (DL_FUNC)&qnorm_c_determine_target);
  R_RegisterCCallable("preprocessCore", "qnorm_c_within_blocks", (DL_FUNC)&qnorm_c_within_blocks);

  /* The summarization routines */

  R_RegisterCCallable("preprocessCore", "median_polish_fit_no_copy", (DL_FUNC)&median_polish_fit_no_copy);
  R_RegisterCCallable("preprocessCore", "median_polish_no_copy", (DL_FUNC)&median_polish_no_copy);
  R_RegisterCCallable("preprocessCore", "median_polish_log2_no_copy", (DL_FUNC)&median_polish_log2_no_copy);
  R_RegisterCCallable("preprocessCore", "median_polish_log2", (DL_FUNC)&median_polish_log2);
  R_RegisterCCallable("preprocessCore", "median_polish", (DL_FUNC)&median_polish);
  R_RegisterCCallable("preprocessCore", "MedianPolish", (DL_FUNC)&MedianPolish);
  R_RegisterCCallable("preprocessCore", "MedianPolish_no_log", (DL_FUNC)&MedianPolish_no_log);


  R_RegisterCCallable("preprocessCore","AverageLog", (DL_FUNC)&AverageLog);
  R_RegisterCCallable("preprocessCore","averagelog_no_copy", (DL_FUNC)&averagelog_no_copy);
  R_RegisterCCallable("preprocessCore","averagelog", (DL_FUNC)&averagelog);
  R_RegisterCCallable("preprocessCore","AverageLog_noSE", (DL_FUNC)&AverageLog_noSE);

  R_RegisterCCallable("preprocessCore","ColAverage", (DL_FUNC)&ColAverage);
  R_RegisterCCallable("preprocessCore","colaverage_no_copy", (DL_FUNC)&colaverage_no_copy);
  R_RegisterCCallable("preprocessCore","colaverage", (DL_FUNC)&colaverage);
  R_RegisterCCallable("preprocessCore","ColAverage_noSE", (DL_FUNC)&ColAverage_noSE);

  R_RegisterCCallable("preprocessCore","MedianLog", (DL_FUNC)&MedianLog);
  R_RegisterCCallable("preprocessCore","medianlog_no_copy", (DL_FUNC)&medianlog_no_copy);
  R_RegisterCCallable("preprocessCore","medianlog", (DL_FUNC)&medianlog);
  R_RegisterCCallable("preprocessCore","MedianLog_noSE", (DL_FUNC)&MedianLog_noSE);
  
  R_RegisterCCallable("preprocessCore","LogMedian", (DL_FUNC)&LogMedian);
  R_RegisterCCallable("preprocessCore","logmedian_no_copy", (DL_FUNC)&logmedian_no_copy);
  R_RegisterCCallable("preprocessCore","logmedian", (DL_FUNC)&logmedian);
  R_RegisterCCallable("preprocessCore","LogMedian_noSE", (DL_FUNC)&LogMedian_noSE);
 
  R_RegisterCCallable("preprocessCore","ColMedian", (DL_FUNC)&ColMedian);
  R_RegisterCCallable("preprocessCore","colmedian_no_copy", (DL_FUNC)&colmedian_no_copy);
  R_RegisterCCallable("preprocessCore","colmedian", (DL_FUNC)&colmedian);
  R_RegisterCCallable("preprocessCore","ColMedian_noSE", (DL_FUNC)&ColMedian_noSE);

  R_RegisterCCallable("preprocessCore","logaverage", (DL_FUNC)&logaverage);
  R_RegisterCCallable("preprocessCore","LogAverage", (DL_FUNC)&LogAverage);
  R_RegisterCCallable("preprocessCore","LogAverage_noSE", (DL_FUNC)&LogAverage_noSE);

  R_RegisterCCallable("preprocessCore","tukeybiweight", (DL_FUNC)&tukeybiweight);
  R_RegisterCCallable("preprocessCore","tukeybiweight_no_log", (DL_FUNC)&tukeybiweight_no_log);
  R_RegisterCCallable("preprocessCore","TukeyBiweight", (DL_FUNC)&TukeyBiweight);
  R_RegisterCCallable("preprocessCore","TukeyBiweight_noSE", (DL_FUNC)&TukeyBiweight_noSE);
  R_RegisterCCallable("preprocessCore","TukeyBiweight_no_log_noSE", (DL_FUNC)&TukeyBiweight_no_log_noSE);
  R_RegisterCCallable("preprocessCore","Tukey_Biweight", (DL_FUNC)&Tukey_Biweight);
  

  R_RegisterCCallable("preprocessCore","lm_wfit", (DL_FUNC)&lm_wfit);
  
  
  R_RegisterCCallable("preprocessCore","rlm_fit", (DL_FUNC)&rlm_fit);
  R_RegisterCCallable("preprocessCore","rlm_wfit", (DL_FUNC)&rlm_wfit);

  R_RegisterCCallable("preprocessCore","rlm_compute_se", (DL_FUNC)&rlm_compute_se);

  R_RegisterCCallable("preprocessCore", "med_abs", (DL_FUNC)&med_abs);
  
  /* The PLM functions */
  R_RegisterCCallable("preprocessCore","rlm_fit_anova", (DL_FUNC)&rlm_fit_anova);
  R_RegisterCCallable("preprocessCore","rlm_wfit_anova", (DL_FUNC)&rlm_wfit_anova);
  R_RegisterCCallable("preprocessCore","rlm_compute_se_anova", (DL_FUNC)&rlm_compute_se_anova);
   

  /* The PLM-R functions */
  R_RegisterCCallable("preprocessCore","plmr_fit", (DL_FUNC)&plmr_fit); 
  R_RegisterCCallable("preprocessCore","plmr_wfit", (DL_FUNC)&plmr_wfit);
   
  R_RegisterCCallable("preprocessCore","plmrc_fit", (DL_FUNC)&plmrc_fit); 
  R_RegisterCCallable("preprocessCore","plmrc_wfit", (DL_FUNC)&plmrc_wfit);
   
  R_RegisterCCallable("preprocessCore","plmrr_fit", (DL_FUNC)&plmrr_fit); 
  R_RegisterCCallable("preprocessCore","plmrr_wfit", (DL_FUNC)&plmrr_wfit);

  /* The PLM functions that work with fixed row(probe) effects */
  R_RegisterCCallable("preprocessCore","rlm_fit_anova_given_probe_effects", (DL_FUNC)&rlm_fit_anova_given_probe_effects);
  R_RegisterCCallable("preprocessCore","rlm_compute_se_anova_given_probe_effects", (DL_FUNC)&rlm_compute_se_anova_given_probe_effects);
  R_RegisterCCallable("preprocessCore","rlm_wfit_anova_given_probe_effects", (DL_FUNC)&rlm_wfit_anova_given_probe_effects);
 

  /* RMA background correction */
  R_RegisterCCallable("preprocessCore","rma_bg_adjust", (DL_FUNC)&rma_bg_adjust);
  R_RegisterCCallable("preprocessCore","rma_bg_parameters", (DL_FUNC)&rma_bg_parameters);
  R_RegisterCCallable("preprocessCore","rma_bg_correct", (DL_FUNC)&rma_bg_correct);


  /* R_subColSummary functions */
  
  R_RegisterCCallable("preprocessCore","R_subColSummarize_avg_log", (DL_FUNC)&R_subColSummarize_avg_log);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_log_avg", (DL_FUNC)&R_subColSummarize_log_avg);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_avg", (DL_FUNC)&R_subColSummarize_avg);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_biweight_log", (DL_FUNC)&R_subColSummarize_biweight_log);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_biweight", (DL_FUNC)&R_subColSummarize_biweight);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_median_log", (DL_FUNC)&R_subColSummarize_median_log);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_log_median", (DL_FUNC)&R_subColSummarize_log_median);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_median",(DL_FUNC)&R_subColSummarize_median);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_medianpolish_log",(DL_FUNC)&R_subColSummarize_medianpolish_log);
  R_RegisterCCallable("preprocessCore","R_subColSummarize_medianpolish",(DL_FUNC)&R_subColSummarize_medianpolish);
  

}
