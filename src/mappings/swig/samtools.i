

%{
  // include the following block literally into mapping file
  #include <bam.h>
  #include <sam.h>
%}



/*
int samread(samfile_t *fp, bam1_t *OUTPUT);
%ignore samread;
*/
%include <bam.h>
%include "typemaps.i"
%apply bam1_t *OUTPUT { bam1_t *b };
int samread(samfile_t *fp, bam1_t *b);
/* %include <sam.h> */



