
%{
  #include <bam.h>
  #include <sam.h>
%}

// %include "typemaps.i"
// %apply double *OUTPUT { bam1_t *b };

%include <bam.h>
%include <sam.h>
