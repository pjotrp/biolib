

%{
  // include the following block literally into mapping file
  #include <bam.h>
  #include <sam.h>

  bam1_t *new_bam() {
    return ((bam1_t*)calloc(1, sizeof(bam1_t)));
  }
%}

%include typemaps.i

/*
%typemap(argout, fragment="output_helper") bam1_t *b {
  // happy
  VALUE bam1 = SWIG_NewPointerObj((bam1_t *)memcpy((bam1_t *)malloc(sizeof(bam1_t)),arg2,sizeof(bam1_t)), SWIGTYPE_p_bam1_t, SWIG_POINTER_OWN |  0 );

  // $result = output_helper($result, bam1);
  $result = bam1;
}
%typemap(in,numinputs=0) bam1_t *b(bam1_t bam1temp) {
  $1 = &bam1temp;
}

*/

bam1_t *new_bam();

// int samread(samfile_t *fp, bam1_t *b);
// bam1_t samread2(samfile_t *fp, bam1_t *b);

// %ignore samread;

%include <bam.h>
%include <sam.h> 



