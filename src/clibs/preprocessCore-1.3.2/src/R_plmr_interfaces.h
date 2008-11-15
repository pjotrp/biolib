#ifndef R_PLMR_INTERFACES_H
#define R_PLMR_INTERFACES_H


SEXP R_plmr_model(SEXP Y, SEXP PsiCode, SEXP PsiK);
SEXP R_wplmr_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Weights);

SEXP R_plmrr_model(SEXP Y, SEXP PsiCode, SEXP PsiK);
SEXP R_plmrc_model(SEXP Y, SEXP PsiCode, SEXP PsiK);

SEXP R_wplmrr_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Weights);
SEXP R_wplmrc_model(SEXP Y, SEXP PsiCode, SEXP PsiK, SEXP Weights);


#endif
