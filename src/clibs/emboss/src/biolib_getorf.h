#pragma once

#include <ajax.h>

#ifdef __cplusplus
extern "C" {
#endif

  struct ORFstruct {
    AjPSeq seq;
    int frame;
    unsigned int start, stop;
  };

  typedef struct ORFstruct ORFrec;

// ORF *biolib_getorf(AjPSeq seq, AjPTrn table, unsigned int minsize);

#ifdef __cplusplus
}
#endif
