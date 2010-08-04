

%{
  // include the following block literally into mapping file
  #include <bam.h>
  #include <sam.h>
%}

%include typemaps.i

%typemap(argout) bam1_t *b {
  // happy
}
%typemap(in,numinputs=0) bam1_t *b(bam1_t bam1temp) {
    $1 = &bam1temp;
}

int samread(samfile_t *fp, bam1_t *b);

%ignore samread;
%include <bam.h>
%include <sam.h> 



