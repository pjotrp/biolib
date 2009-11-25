# EMBOSS methods
#

%{
  #include <ajax.h>
  #include <ajseq.h>
  #include <ajtranslate.h>
%}

%include <ajax.h>
%include <ajarch.h>
%include <ajseq.h>
# %include <ajseqdata.h>
# %include <ajtranslate.h>

AjPTrn ajTrnNewI (ajint trnFileNameInt);
AjPSeq ajTrnSeqOrig (const AjPTrn trnObj, const AjPSeq seq, ajint frame);

