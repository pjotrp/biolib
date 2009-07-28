%module bpptest
%{
#include "IOSequenceFactory.h"
using namespace bpp;
%}
#include "ioseq"
%include "Alphabet.i"

class IOSequenceFactory
{
    static const string FASTA_FORMAT;  
    static const string MASE_FORMAT;  
    static const string CLUSTAL_FORMAT;  
    static const string DCSE_FORMAT;  
    static const string PHYLIP_FORMAT_INTERLEAVED;  
    static const string PHYLIP_FORMAT_SEQUENTIAL;  
    static const string PAML_FORMAT_INTERLEAVED;  
    static const string PAML_FORMAT_SEQUENTIAL;  

    IOSequenceFactory();
    virtual ~IOSequenceFactory();
    virtual ISequence * createReader(const string & format) throw (Exception);
    virtual OSequence * createWriter(const string & format) throw (Exception);
};
