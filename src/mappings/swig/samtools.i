%{
  // include the following block literally into mapping file
  #include <bam.h>
  #include <sam.h>

  bam1_t *new_bam() {
    return bam_init1();
  }

  void free_bam(bam1_t *bbuf) {
    bam_destroy1(bbuf);
  }

  void bam1_t_datalist_get(char *datalist, bam1_t *b) {
    datalist = (char *)b->data;
  }

%}

%include <stdint.i>
%include <bam.h>
%include <sam.h> 

%apply char *OUTPUT { char *datalist };
%typemap(argout) (char *datalist, bam1_t *b) {
  int asize = $2->data_len;
  $result = rb_str_new($2->data,asize);
}

bam1_t *new_bam();
void free_bam(bam1_t *bbuf);
void bam1_t_datalist_get(char *datalist, bam1_t *b);



