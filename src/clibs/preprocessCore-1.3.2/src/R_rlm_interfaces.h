#ifndef R_RLM_INTERFACES_H
#define R_RLM_INTERFACES_H


SEXP R_rlm_rma_default_model(SEXP Y, SEXP PsiCode, SEXP PsiK);
SEXP R_wrlm_rma_default_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Weights);
SEXP R_medianpolish_rma_default_model(SEXP Y);
SEXP R_rlm_rma_given_probe_effects(SEXP Y, SEXP probe_effects, SEXP PsiCode, SEXP PsiK);
SEXP R_wrlm_rma_given_probe_effects(SEXP Y, SEXP probe_effects, SEXP PsiCode, SEXP PsiK, SEXP Weights);

#endif
