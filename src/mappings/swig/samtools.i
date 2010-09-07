%{
  #include <stdint.h>
  #ifdef APPLE
    typedef __off64_t off64_t;
  #endif

  // include the following block literally into mapping file
  #include <bam.h>
  #include <sam.h>
  #include <faidx.h>

  // Rename defines and static functions
  bam1_t *bl_bam_init1() { return bam_init1(); }
  void bl_bam_destroy1(bam1_t *bbuf) { bam_destroy1(bbuf); }
  bam1_t *bl_bam_copy1(bam1_t *bdst, const bam1_t *bsrc) { return bam_copy1(bdst,bsrc); }
  bam1_t *bl_bam_dup1(const bam1_t *src) { return bam_dup1(src); }

  // Special functions
  void bam1_t_datalist_get(char *datalist, bam1_t *b) {
    datalist = (char *)b->data;
  }
  samfile_t *samopen_header(const char *fn, const char *mode, bam_header_t *header) {
    return samopen(fn,mode,header);
  }
  samfile_t *samopen_listfn(const char *fn, const char *mode, const char *listfn) {
    return samopen(fn,mode,listfn);
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
%include <faidx.h> 

%apply char *OUTPUT { char *datalist };
%typemap(argout) (char *datalist, bam1_t *b) {
  int asize = $2->data_len;
  char *carray = (char *)$2->data;
  %set_output(SWIG_FromCharPtrAndSize(carray, asize));
}

#undef bam_init1
#undef bam_destroy1
#undef bam_copy1
#undef bam_dup1
%rename(bam_init1) bl_bam_init1;
%rename(bam_destroy1) bl_bam_destroy1;
%rename(bam_copy1) bl_bam_copy1;
%rename(bam_dup1) bl_bam_dup1;

bam1_t *bl_bam_init1();
void bl_bam_destroy1(bam1_t *bbuf);
bam1_t *bl_bam_copy1(bam1_t *bdst, const bam1_t *bsrc);
bam1_t *bl_bam_dup1(const bam1_t *src);
/* Helper functions */
void bam1_t_datalist_get(char *datalist, bam1_t *b);
samfile_t *samopen_listfn(const char *fn, const char *mode, const char *listfn);
samfile_t *samopen_header(const char *fn, const char *mode, bam_header_t *header);
