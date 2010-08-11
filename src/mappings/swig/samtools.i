%{
  #include <stdint.h>
  typedef __off64_t off64_t;

  // include the following block literally into mapping file
  #include <bam.h>
  #include <sam.h>

  bam1_t *bl_bam_init1() {
    return bam_init1();
  }

  void bl_bam_destroy1(bam1_t *bbuf) {
    bam_destroy1(bbuf);
  }

  bam1_t *bl_bam_copy1(bam1_t *bdst, const bam1_t *bsrc) {
    return bam_copy1(bdst,bsrc);
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
  char *carray = (char *)$2->data;
  %set_output(SWIG_FromCharPtrAndSize(carray, asize));
}

#undef bam_init1
#undef bam_destroy1
%rename(bam_init1) bl_bam_init1;
%rename(bam_destroy1) bl_bam_destroy1;

bam1_t *bl_bam_init1();
void bl_bam_destroy1(bam1_t *bbuf);
void bam1_t_datalist_get(char *datalist, bam1_t *b);
