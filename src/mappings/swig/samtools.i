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

%ignore bam_strmap_init;
%ignore bam_strmap_put;
%ignore bam_strmap_get;
%ignore bam_strmap_dup;
%ignore bam_strmap_destroy;
%ignore bam_nt16_nt4_table;
%ignore sam_header_parse_rg;

%include <stdint.i>
%include <bam.h>
%include <sam.h> 

%apply char *OUTPUT { char *datalist };
%typemap(argout) (char *datalist, bam1_t *b) {
  int asize = $2->data_len;
  // $result = rb_str_new($2->data,asize);
  char *carray = $2->data;
  $result = SWIG_FromCharPtrAndSize(carray, asize);
}

bam1_t *new_bam();
void free_bam(bam1_t *bbuf);
void bam1_t_datalist_get(char *datalist, bam1_t *b);



