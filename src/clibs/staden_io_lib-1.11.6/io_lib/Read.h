/*
 * Copyright (c) Medical Research Council 1994. All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * this copyright and notice appears in all copies.
 *
 * This file was written by James Bonfield, Simon Dear, Rodger Staden,
 * as part of the Staden Package at the MRC Laboratory of Molecular
 * Biology, Hills Road, Cambridge, CB2 2QH, United Kingdom.
 *
 * MRC disclaims all warranties with regard to this software.
 *
 */

#ifndef _Read_h_
#define _Read_h_

/* 
 * Title:	Read
 *
 * File: 	Read.h
 * Purpose:	Read data type
 * Last update:	June  14 1994
 */

/*! \defgroup staden Staden io_lib */

/*! \file Read.h 
These functions read trace files into a Read structure. A variety of formats
are supported including ABI, ALF and SCF. (Note that the first two are only
supported when the library is used as part of the Staden Package.)
Additionally, support for reading the plain (old) staden format files and
Experiment files is included. Compressed trace files may also be read.
Decompression is performed using either gzip -d or uncompress and is written to
a temporary file for further processing. The temporary file is then read and
removed.

When reading an experiment file the trace file referenced by the LN and LT line
types is read. The QL, QR (left and right quality clips), SL and SR (left and
right vector clips) are taken from the Experiment file to produce the cutoff
information held within the Read structure. The orig_trace field of the Read
structure will then contain the pointer to the experiment file structure and
the orig_trace_format field will be set to TT_EXP.

The functions allocate a Read structure which is returned. To deallocate this
structure use the read_deallocate() function.

read_reading() reads a trace from the specified filename and format. Formats
available are TT_SCF, TT_ABI, TT_ALF, TT_PLN, TT_EXPand TT_ANY. Specifying
format TT_ANY will attempt to automatically detect the corret format type by
analysing the trace file for magic numbers and composition. The format field of
the structure can then be used to determine the real trace type.

fread_reading() reads a trace from the specified file pointer. The filename
argument is used for setting the trace_name field of the resulting structure,
and for error messages. Otherwise the function is identical to the
read_reading() function.

The Read data type is designed so that it can hold a varying degree of
information about sequences, yet have a single set of calls to access the data.

There are plenty of assumptions around that both the number of bases and the
number of points will fit into an int_2, a short.

This module encodes the `Read' sequence data structure.

A `Read' contains information about bases and traces which are laid out along a
single dimension of points. The number of points in a paricular sequence is
given by `getNPoints', and these are numbered 0..getNPoints-1. At each point
there are four trace readings, one for each base.

The number of bases is `getNBases' which are numbered 0..N-1.  Bases are
represented by `char's. Every base is located at a particular point.

The behaviour of these routines is undefined if given NULLRead or an undefined
sequence.

*/

#include "io_lib/os.h"
#include "io_lib/scf.h"
#include "io_lib/mFILE.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The autoconf setup doesn't use options.mk as the Makefile is rebuilt.
 * I haven't worked out how to do the analogous via autoconf, so for now
 * I take the easy approach and hard-code all formats to be enabled
 */
#ifdef HAVE_CONFIG_H
#include "io_lib_config.h"
#define IOLIB_ABI
#define IOLIB_SCF
#define IOLIB_ALF
#define IOLIB_PLN
#define IOLIB_CTF
#define IOLIB_EXP
#define IOLIB_SFF
#endif

/* Only add ZTR support if we've got ZLIB installed */
#ifdef HAVE_ZLIB
#  ifndef IOLIB_ZTR
#    define IOLIB_ZTR
#  endif
#endif

/*
 *-----------------------------------------------------------------------------
 * Macros
 *-----------------------------------------------------------------------------
 */

#define NULLRead     ((Read *)NULL)

/* Trace file formats */
#define TT_ERR -1
#define TT_UNK 0
#define TT_SCF 1
#define TT_ABI 2
#define TT_ALF 3
#define TT_PLN 4
#define TT_EXP 5
#define TT_CTF 6
#define TT_ZTR 7
#define TT_ZTR1 8
#define TT_ZTR2 9
#define TT_ZTR3 10
#define TT_BIO 11
#define TT_SFF 12
#define TT_ANY TT_UNK
/// ANYTR is specifically any *trace* type and not EXP or PLN format 
#define TT_ANYTR 13

/// \cond SKIP
#define READ_BASES	(1<<0)
#define READ_SAMPLES	(1<<1)
#define READ_COMMENTS	(1<<2)
#define READ_ALL	(READ_BASES | READ_SAMPLES | READ_COMMENTS)

/*
 *-----------------------------------------------------------------------------
 * Structures and typedefs
 *-----------------------------------------------------------------------------
 */

/// \endcond
/// for trace heights 
typedef uint_2 TRACE;        

/*! Read compound structure used for reading and writing trace files */
typedef struct
{
    /// Trace file format
    int		format;	           
    /// Trace file name 
    char       *trace_name;  

    /// No. of points of data
    int         NPoints;     
    /// No. of bases 
    int         NBases;      

    /// Trace: Array of length `NPoints'
    TRACE      *traceA;      
    /// Trace: Array of length `NPoints'
    TRACE      *traceC;      
    /// Trace: Array of length `NPoints'
    TRACE      *traceG;  
    /// Trace: Array of length `NPoints'
    TRACE      *traceT; 
    /// The maximal value in any trace 
    TRACE       maxTraceVal; 
    /// The zero offset for TRACE values
    int         baseline;    

    /// Bases: Array of length `NBases' 
    char       *base;        
    /// Array of length `NBases' 
    uint_2     *basePos;     

    /// Cutoffs: Number of unwanted bases 
    int         leftCutoff;  
    /// First unwanted base at right end
    int         rightCutoff; 

    /// Miscellaneous Sequence Information: e.g. comments
    char       *info;        

    /// Probability information: Array of length 'NBases' 
    char       *prob_A;      
    /// Probability information: Array of length 'NBases' 
    char       *prob_C;      
    /// Probability information: Array of length 'NBases' 
    char       *prob_G;      
    /// Probability information: Array of length 'NBases' 
    char       *prob_T;      

    /// The original input format data, or NULL if inapplicable 
    int orig_trace_format;
    void (*orig_trace_free)(void *ptr);
    void *orig_trace;

    /// Seq id, NULL for unknown. Malloced data.  Owned and freed by io_lib. 
    char       *ident;	     

    /// Pyrosequencing "peaks" (more like spikes). NULL if not used: Number of "flows" 
    int          nflows;     
    /// Bases flowed across 
    char        *flow_order; 
    /// Processed to be 1 base unit oriented 
    float       *flow;       
    /// Unprocessed data 
    unsigned int*flow_raw;   

    /// The 'private data' block and size from SCF, 
    void *private_data;	     
    ///         NULL & 0 if not present.            
    int private_size;        
} Read;

/// \cond SKIP

/*
 *-----------------------------------------------------------------------------
 * Function prototypes
 *-----------------------------------------------------------------------------
 */


/* ----- Main I/O routines ----- */

/*
 * Read a sequence from a file "fn" of format "format". If "format" is 0
 * (TT_ANY), we automatically determine the correct format.
 *
 * Returns:
 *   Read *   for success
 *   NULLRead for failure
 */
Read *read_reading(char *fn, int format);
Read *fread_reading(FILE *fp, char *fn, int format);
Read *mfread_reading(mFILE *fp, char *fn, int format);


/*
 * Write a sequence to a file "fn" of format "format". If "format" is 0,
 * we choose our favourite - SCF.
 *
 * Returns:
 *   0 for success
 *  -1 for failure
 */
int write_reading(char *fn, Read *read, int format);
int fwrite_reading(FILE *fp, Read *read, int format);
int mfwrite_reading(mFILE *fp, Read *read, int format);


/* ----- Utility routines ----- */

/*
 * Allocate a new sequence, with the given sizes.
 * Returns:
 *   "Read *" for success
 *   "NULLRead" for failure
 */
Read *read_allocate(int num_points, int num_bases);


/*
 * Duplicates the read structure and optionally gives it a new filename.
 * The following fields are not duplicated:
 *    
 *  int  orig_trace_format;
 *  void (*orig_trace_free)(void *ptr);
 *  void *orig_trace;
 *  char *ident;
 *
 * Returns:
 *   "Read *" for success
 *   "NULLRead" for failure
 */
Read* read_dup( Read* src, const char* new_name );


/// \endcond

/*!
 * Free memory allocated to a sequence by read_allocate().
 */
void read_deallocate(Read *read);

/// \cond SKIP
/* unix specific file deletion routine */

int remove_file(char *fn);

Read *read_abi(char *fn);
Read *fread_abi(FILE *fp);
Read *mfread_abi(mFILE *fp);
int write_abi(char *fn, Read *read);
int fwrite_abi(FILE *fp, Read *read);
int mfwrite_abi(mFILE *fp, Read *read);

int write_alf(char *fn, Read *read);
int fwrite_alf(FILE *fp, Read *read);
int mfwrite_alf(mFILE *fp, Read *read);
Read *read_alf(char *fn);
Read *fread_alf(FILE *fp);
Read *mfread_alf(mFILE *fp);

int write_pln(char *fn, Read *read);
int fwrite_pln(FILE *fp, Read *read);
int mfwrite_pln(mFILE *fp, Read *read);
Read *read_pln(char *fn);
Read *fread_pln(FILE *fp);
Read *mfread_pln(mFILE *fp);

Read *read_ctf(char *fn);
Read *fread_ctf(FILE *fp);
Read *mfread_ctf(mFILE *fp);
int write_ctf(char *fn, Read *read);
int fwrite_ctf(FILE *fp, Read *read);
int mfwrite_ctf(mFILE *fp, Read *read);

int read_sections(int sec);

#include "io_lib/translate.h"
#include "io_lib/compress.h"

#ifdef __cplusplus
}
#endif

/// \endcond
/*@}*/

#endif /* _Read_h_ */
