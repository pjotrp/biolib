

%{
  // include the following block literally into mapping file
  #include <bam.h>
  #include <sam.h>

  bam1_t *new_bam() {
    return ((bam1_t*)calloc(1, sizeof(bam1_t)));
  }

  void bam1_t_datalist_get(char *datalist, bam1_t *b) {
    datalist = (char *)b->data;
  }

%}

%include <bam.h>
%include <sam.h> 

%apply char *OUTPUT { char *datalist };
%typemap(argout) (char *datalist, bam1_t *b) {
  int asize = $2->data_len;
  // $result = rb_ary_new();
  // for (i=0; i<asize; i++)
  //   rb_ary_push($result,INT2CHAR($1[i]));
  $result = rb_str_new($1,asize);
}



bam1_t *new_bam();
void bam1_t_datalist_get(char *datalist, bam1_t *b);



