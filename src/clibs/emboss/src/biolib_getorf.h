#pragma once

#include <ajax.h>

#ifdef __cplusplus
  extern "C" {
#endif

void getorf_FindORFs(const AjPSeq seq, ajint len, const AjPTrn trnTable,
			    ajuint minsize, ajuint maxsize, AjPSeqout seqout, 
			    AjBool sense, AjBool circular, ajint find, 
			    ajint *orf_no, AjBool methionine, ajint around);


#ifdef __cplusplus
  }
#endif
