#ifndef PSI_FNS_H
#define PSI_FNS_H

double psi_huber(double u, double k,int deriv);
double psi_fair(double u, double k,int deriv);
double psi_cauchy(double u, double k,int deriv);
double psi_GemanMcClure(double u, double k,int deriv);
double psi_Welsch(double u, double k,int deriv);
double psi_Tukey(double u, double k,int deriv);
double psi_Andrews(double u, double k,int deriv);

typedef double (*pt2psi)(double , double , int);

pt2psi PsiFunc(int code);
int psi_code(char *Name);


#endif
