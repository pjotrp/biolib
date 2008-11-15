#ifndef _FREAD_FUNCTIONS_HEADER
#define _FREAD_FUNCTIONS_HEADER



#include "stdlib.h"
#include "stdio.h"

#define HAVE_ZLIB 1

#if defined(HAVE_ZLIB)
#include <zlib.h>
#endif



size_t fread_int32(int *destination, int n, FILE *instream);
size_t fread_uint32(unsigned int *destination, int n, FILE *instream);
size_t fread_int16(short *destination, int n, FILE *instream);
size_t fread_uint16(unsigned short *destination, int n, FILE *instream);
size_t fread_float32(float *destination, int n, FILE *instream);
size_t fread_char(char *destination, int n, FILE *instream);
size_t fread_uchar(unsigned char *destination, int n, FILE *instream);
size_t fread_double64(double *destination, int n, FILE *instream);


size_t fread_be_int32(int *destination, int n, FILE *instream);
size_t fread_be_uint32(unsigned int *destination, int n, FILE *instream);
size_t fread_be_int16(short *destination, int n, FILE *instream);
size_t fread_be_uint16(unsigned short *destination, int n, FILE *instream);
size_t fread_be_float32(float *destination, int n, FILE *instream);
size_t fread_be_char(char *destination, int n, FILE *instream);
size_t fread_be_uchar(unsigned char *destination, int n, FILE *instream);
size_t fread_be_double64(double *destination, int n, FILE *instream);

size_t fread_be_wchar(wchar_t *destination, int n, FILE *instream);

#if defined(HAVE_ZLIB)
size_t gzread_int32(int *destination, int n, gzFile *instream);
size_t gzread_uint32(unsigned int *destination, int n, gzFile *instream);
size_t gzread_int16(short *destination, int n, gzFile *instream);
size_t gzread_uint16(unsigned short *destination, int n, gzFile *instream);
size_t gzread_float32(float *destination, int n, gzFile *instream);
size_t gzread_char(char *destination, int n, gzFile *instream);
size_t gzread_uchar(unsigned char *destination, int n, gzFile *instream);
size_t gzread_double64(double *destination, int n, gzFile *instream);

size_t gzread_be_int32(int *destination, int n, gzFile *instream);
size_t gzread_be_uint32(unsigned int *destination, int n, gzFile *instream);
size_t gzread_be_int16(short *destination, int n, gzFile *instream);
size_t gzread_be_uint16(unsigned short *destination, int n, gzFile *instream);
size_t gzread_be_float32(float *destination, int n, gzFile *instream);
size_t gzread_be_char(char *destination, int n, gzFile *instream);
size_t gzread_be_uchar(unsigned char *destination, int n, gzFile *instream);
size_t gzread_be_double64(double *destination, int n, gzFile *instream);

#endif


#endif
