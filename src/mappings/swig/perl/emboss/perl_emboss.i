%module emboss

%{
  #define OP_NOT SWIG_EMBOSS_OP_NOT 
  #define OP_REF SWIG_EMBOSS_OP_REF
  #define OP_REVERSE SWIG_EMBOSS_OP_REVERSE
  #define OP_ONCE SWIG_EMBOSS_OP_ONCE
  #define const
%}

%include ../../emboss.i
