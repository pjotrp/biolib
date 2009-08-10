%module libsequence

%include ../../libsequence.i

%inline %{

double Dereference( double *x, int i ){
    return x[i];
}

%}
