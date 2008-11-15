

#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include "stdlib.h"
#include "stdio.h"
#include "fread_functions.h"

#define HAVE_ZLIB 1

#if defined(HAVE_ZLIB)
#include <zlib.h>
#endif


/*************************************************************************
 **
 ** Code for reading from the binary files, doing bit flipping if
 ** necessary (on big-endian machines)
 **
 **
 ************************************************************************/


size_t fread_int32(int *destination, int n, FILE *instream){

  size_t result;
  
  result = fread(destination,sizeof(int),n,instream);

#ifdef WORDS_BIGENDIAN 
  while( n-- > 0 ){
  /* bit flip since all Affymetrix binary files are little endian */
    
    *destination=(((*destination>>24)&0xff) | ((*destination&0xff)<<24) |
		  ((*destination>>8)&0xff00) | ((*destination&0xff00)<<8));  
    destination++;
  }
#endif
  return result;
}



size_t fread_uint32(unsigned int *destination, int n, FILE *instream){


  size_t result;

  result = fread(destination,sizeof(unsigned int),n,instream);

  
#ifdef WORDS_BIGENDIAN
  while( n-- > 0 ){
    /* bit flip since all Affymetrix binary files are little endian */
    *destination=(((*destination>>24)&0xff) | ((*destination&0xff)<<24) |
		  ((*destination>>8)&0xff00) | ((*destination&0xff00)<<8));  
    destination++;
  } 
#endif
  return result;
}



size_t fread_int16(short *destination, int n, FILE *instream){
   size_t result;

   result = fread(destination,sizeof(short),n,instream);

#ifdef WORDS_BIGENDIAN
   while( n-- > 0 ){
     /* bit flip since all Affymetrix binary files are little endian */
     *destination=(((*destination>>8)&0xff) | ((*destination&0xff)<<8));  
     destination++;
   }
#endif
   return result;

}


size_t fread_uint16(unsigned short *destination, int n, FILE *instream){
   size_t result;

   result = fread(destination,sizeof(unsigned short),n,instream);

#ifdef WORDS_BIGENDIAN
   while( n-- > 0 ){
     /* bit flip since all Affymetrix binary files are little endian */
     *destination=(((*destination>>8)&0xff) | ((*destination&0xff)<<8));
     destination++;
   }
#endif
   return result;

}





static void swap_float_4(float *tnf4)              /* 4 byte floating point numbers */
{
  unsigned char *cptr,tmp;
  
  cptr = (unsigned char *)tnf4;
  tmp = cptr[0];
  cptr[0] = cptr[3];
  cptr[3] =tmp;
  tmp = cptr[1];
  cptr[1] = cptr[2];
  cptr[2] = tmp;
  
}


size_t fread_float32(float *destination, int n, FILE *instream){

  size_t result;

  
  result = fread(destination,sizeof(float),n,instream);

#ifdef WORDS_BIGENDIAN 
  while( n-- > 0 ){
    swap_float_4(destination);
    destination++;
  }
#endif
  
  return result;
}

size_t fread_char(char *destination, int n, FILE *instream){

  size_t result;
  
  result = fread(destination,sizeof(char),n,instream);
  
#ifdef WORDS_BIGENDIAN 
  /* Probably don't need to do anything for characters */

#endif

  return result;

}


size_t fread_uchar(unsigned char *destination, int n, FILE *instream){


  size_t result;

  result = fread(destination,sizeof(unsigned char),n,instream);

#ifdef WORDS_BIGENDIAN
  /* Probably don't need to do anything for characters */
  /* destination = ~destination; */
#endif

  return result;

}




static void swap_float_8(double *tnf8)              /* 8 byte floating point numbers */
{
  unsigned char *cptr,tmp;

  cptr = (unsigned char *)tnf8;
  tmp = cptr[0];
  cptr[0] = cptr[7];
  cptr[7] = tmp;
  tmp = cptr[1];
  cptr[1] = cptr[6];
  cptr[6] = tmp;
  tmp = cptr[2];
  cptr[2] = cptr[5];
  cptr[5] =tmp;
  tmp = cptr[3];
  cptr[3] = cptr[4];
  cptr[4] = tmp; 
}





size_t fread_double64(double *destination, int n, FILE *instream){

  size_t result;

  
  result = fread(destination,sizeof(double),n,instream);

#ifdef WORDS_BIGENDIAN 
  while( n-- > 0 ){
    swap_float_8(destination);
    destination++;
  }
#endif
  
  return result;
}

/*************************************************************************
 **
 ** Code for big endian data reading from the binary files, doing bit flipping if
 ** necessary (on little-endian machines)
 **
 **
 ************************************************************************/

size_t fread_be_int32(int *destination, int n, FILE *instream){

  size_t result;

  result = fread(destination,sizeof(int),n,instream);

#ifndef WORDS_BIGENDIAN
  while (n-- > 0){
    /* bit flip since on a little endian machine */

    *destination=(((*destination>>24)&0xff) | ((*destination&0xff)<<24) |
                  ((*destination>>8)&0xff00) | ((*destination&0xff00)<<8));
    destination++;
  }
#endif
  return result;
}



size_t fread_be_uint32(unsigned int *destination, int n, FILE *instream){


  size_t result;

  result = fread(destination,sizeof(unsigned int),n,instream);


#ifndef WORDS_BIGENDIAN
  while (n-- > 0){
    /* bit flip since all Affymetrix binary files are little endian */
    *destination=(((*destination>>24)&0xff) | ((*destination&0xff)<<24) |
                  ((*destination>>8)&0xff00) | ((*destination&0xff00)<<8));
    destination++;
  }

#endif
  return result;
}


size_t fread_be_int16(short *destination, int n, FILE *instream){
   size_t result;

   result = fread(destination,sizeof(short),n,instream);

#ifndef WORDS_BIGENDIAN
   while (n-- > 0){
     /* bit flip since all Affymetrix binary files are little endian */
     *destination=(((*destination>>8)&0xff) | ((*destination&0xff)<<8));
     destination++;
  }
#endif
   return result;

}




size_t fread_be_uint16(unsigned short *destination, int n, FILE *instream){
   size_t result;

   result = fread(destination,sizeof(unsigned short),n,instream);

#ifndef WORDS_BIGENDIAN
   while( n-- > 0 ){
     /* bit flip since all Affymetrix binary files are little endian */
     *destination=(((*destination>>8)&0xff) | ((*destination&0xff)<<8));
     destination++;
   }
#endif
   return result;

}




static void swap_uint_32(unsigned int *tni4)              /* 4 byte integer numbers */
{
  
  *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
       ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));
  

}





size_t fread_be_float32(float *destination, int n, FILE *instream){

  size_t result;

  

  result = fread(destination,sizeof(float),n,instream);

#ifndef WORDS_BIGENDIAN
  while( n-- > 0 ) {
    swap_float_4(destination);
    destination++;
  }
#endif

  return result;
}




size_t fread_be_char(char *destination, int n, FILE *instream){

 
  size_t result;

  result = fread(destination,sizeof(char),n,instream);

#ifndef WORDS_BIGENDIAN
  /* Probably don't need to do anything for characters */

#endif

  return result;

}

size_t fread_be_uchar(unsigned char *destination, int n, FILE *instream){

 
  size_t result;

  result = fread(destination,sizeof(unsigned char),n,instream);

#ifndef WORDS_BIGENDIAN
  /* Probably don't need to do anything for characters */
  /* destination = ~destination; */
#endif

  return result;

}



size_t fread_be_wchar(wchar_t *destination, int n, FILE *instream){

  size_t result;

  result = fread(destination, sizeof(wchar_t), n, instream);

  return result;
  
}


size_t fread_be_double64(double *destination, int n, FILE *instream){

  size_t result;

  
  result = fread(destination,sizeof(double),n,instream);

#ifndef WORDS_BIGENDIAN 
  while( n-- > 0 ){
    swap_float_8(destination);
    destination++;
  }
#endif
  
  return result;
}

#if defined(HAVE_ZLIB)




/*************************************************************************
 **
 ** Code for reading from the gzipped binary files, doing bit flipping if
 ** necessary (on big-endian machines)
 **
 **
 ************************************************************************/


size_t gzread_int32(int *destination, int n, gzFile *instream){

  size_t result;
  
  result = gzread(instream,destination,sizeof(int)*n); 

  //int gzread  (gzFile file, voidp buf, unsigned int len);



#ifdef WORDS_BIGENDIAN 
  while( n-- > 0 ){
  /* bit flip since all Affymetrix binary files are little endian */
    
    *destination=(((*destination>>24)&0xff) | ((*destination&0xff)<<24) |
		  ((*destination>>8)&0xff00) | ((*destination&0xff00)<<8));  
    destination++;
  }
#endif
  return result;
}



size_t gzread_uint32(unsigned int *destination, int n, gzFile *instream){


  size_t result;

  result = gzread(instream,destination,sizeof(unsigned int)*n); 

  
#ifdef WORDS_BIGENDIAN
  while( n-- > 0 ){
    /* bit flip since all Affymetrix binary files are little endian */
    *destination=(((*destination>>24)&0xff) | ((*destination&0xff)<<24) |
		  ((*destination>>8)&0xff00) | ((*destination&0xff00)<<8));  
    destination++;
  } 
#endif
  return result;
}



size_t gzread_int16(short *destination, int n, gzFile *instream){
   size_t result;

   result = gzread(instream,destination,sizeof(short)*n);

#ifdef WORDS_BIGENDIAN
   while( n-- > 0 ){
     /* bit flip since all Affymetrix binary files are little endian */
     *destination=(((*destination>>8)&0xff) | ((*destination&0xff)<<8));  
     destination++;
   }
#endif
   return result;
}




size_t gzread_uint16(unsigned short *destination, int n, gzFile *instream){
   size_t result;

   result = gzread(instream,destination,sizeof(unsigned short)*n);

#ifdef WORDS_BIGENDIAN
   while( n-- > 0 ){
     /* bit flip since all Affymetrix binary files are little endian */
     *destination=(((*destination>>8)&0xff) | ((*destination&0xff)<<8));  
     destination++;
   }
#endif
   return result;
}





size_t gzread_float32(float *destination, int n, gzFile *instream){

  size_t result;

  
  result =  gzread(instream,destination,sizeof(float)*n); 

#ifdef WORDS_BIGENDIAN 
  while( n-- > 0 ){
    swap_float_4(destination);
    destination++;
  }
#endif
  
  return result;
}

size_t gzread_char(char *destination, int n, gzFile *instream){

  size_t result;
  
  result = gzread(instream,destination,sizeof(char)*n); 
  
#ifdef WORDS_BIGENDIAN 
  /* Probably don't need to do anything for characters */

#endif

  return result;

}


size_t gzread_uchar(unsigned char *destination, int n, gzFile *instream){

  size_t result;
  
  result = gzread(instream,destination,sizeof(unsigned char)*n); 
  
#ifdef WORDS_BIGENDIAN 
  /* Probably don't need to do anything for characters */

#endif

  return result;

}




size_t gzread_double64(double *destination, int n, gzFile *instream){

  size_t result;
  
  result = gzread(instream, destination,sizeof(double)*n);

#ifdef WORDS_BIGENDIAN 
  while( n-- > 0 ){
    swap_float_8(destination);
    destination++;
  }
#endif
  
  return result;
}




/*************************************************************************
 **
 ** Code for reading from the gzipped binary files written in BE format, doing bit flipping if
 ** necessary (on big-endian machines)
 **
 **
 ************************************************************************/


size_t gzread_be_int32(int *destination, int n, gzFile *instream){

  size_t result;
  
  result = gzread(instream,destination,sizeof(int)*n); 

  //int gzread  (gzFile file, voidp buf, unsigned int len);



#ifndef WORDS_BIGENDIAN 
  while( n-- > 0 ){
  /* bit flip since all Affymetrix binary files are little endian */
    
    *destination=(((*destination>>24)&0xff) | ((*destination&0xff)<<24) |
		  ((*destination>>8)&0xff00) | ((*destination&0xff00)<<8));  
    destination++;
  }
#endif
  return result;
}



size_t gzread_be_uint32(unsigned int *destination, int n, gzFile *instream){


  size_t result;

  result = gzread(instream,destination,sizeof(unsigned int)*n); 

  
#ifndef WORDS_BIGENDIAN
  while( n-- > 0 ){
    /* bit flip since all Affymetrix binary files are little endian */
    *destination=(((*destination>>24)&0xff) | ((*destination&0xff)<<24) |
		  ((*destination>>8)&0xff00) | ((*destination&0xff00)<<8));  
    destination++;
  } 
#endif
  return result;
}




size_t gzread_be_int16(short *destination, int n, gzFile *instream){
   size_t result;

   result = gzread(instream,destination,sizeof(short)*n);

#ifndef WORDS_BIGENDIAN
   while( n-- > 0 ){
     /* bit flip since all Affymetrix binary files are little endian */
     *destination=(((*destination>>8)&0xff) | ((*destination&0xff)<<8));  
     destination++;
   }
#endif
   return result;
}


size_t gzread_be_uint16(unsigned short *destination, int n, gzFile *instream){
   size_t result;

   result = gzread(instream,destination,sizeof(unsigned short)*n);

#ifndef WORDS_BIGENDIAN
   while( n-- > 0 ){
     /* bit flip since all Affymetrix binary files are little endian */
     *destination=(((*destination>>8)&0xff) | ((*destination&0xff)<<8));  
     destination++;
   }
#endif
   return result;
}




size_t gzread_be_float32(float *destination, int n, gzFile *instream){

  size_t result;

  
  result =  gzread(instream,destination,sizeof(float)*n); 

#ifndef WORDS_BIGENDIAN 
  while( n-- > 0 ){
    swap_float_4(destination);
    destination++;
  }
#endif
  
  return result;
}


size_t gzread_be_char(char *destination, int n, gzFile *instream){

  size_t result;
  
  result = gzread(instream,destination,sizeof(char)*n); 
  
#ifndef WORDS_BIGENDIAN 
  /* Probably don't need to do anything for characters */

#endif

  return result;

}



size_t gzread_be_uchar(unsigned char *destination, int n, gzFile *instream){

  size_t result;
  
  result = gzread(instream,destination,sizeof(unsigned char)*n); 
  
#ifndef WORDS_BIGENDIAN 
  /* Probably don't need to do anything for characters */

#endif

  return result;

}


size_t gzread_be_double64(double *destination, int n, gzFile *instream){

  size_t result;
  
  result = gzread(instream, destination,sizeof(double)*n);

#ifndef WORDS_BIGENDIAN 
  while( n-- > 0 ){
    swap_float_8(destination);
    destination++;
  }
#endif
  
  return result;
}








#endif


void test_parsers_le(){
  FILE* infile;
  int i;

  unsigned char my_uc;
  char my_c;
  
  unsigned short my_us;
  short my_s;
  
  unsigned int my_ui;
  int my_i;

  float my_f;
  
  double my_d;
  
  if ((infile = fopen("LittleEndianTest.bin", "rb")) == NULL)
    {
      printf("Unable to open the file\n");
      return ;
    }
  
  for (i = 0; i < 255; i++){
    fread_uchar(&my_uc,1, infile);
    printf("Was  : %d should be %d\n",my_uc,i);
  }
  
  for (i = -128; i < 127; i++){
    fread_char(&my_c,1, infile);  
    printf("Was  : %d should be %d\n",my_c,i);
  }
  
  for (i =0; i < 15; i++){
    fread_uint16(&my_us,1,infile);
    printf("Was  : %d \n", my_us);
  } 
  
  for (i=0; i < 15; i++){
    fread_int16(&my_s,1,infile);
    printf("Was  : %d \n", my_s);
  }

  for (i=0; i < 31; i++){
    fread_uint32(&my_ui,1,infile);
    printf("uint32 Was  : %d \n", my_ui);
  }
  
  
  for (i=0; i < 31; i++){
    fread_int32(&my_i,1, infile);
    printf("int32 Was  : %d \n", my_i);
  }

  
  for (i = 0; i < 25; i++){
    fread_float32(&my_f,1,infile);   
    printf("float32 Was  : %e \n", my_f);
  }
  fread_float32(&my_f,1,infile);
  printf("PI float32 Was  : %f \n", my_f);

  
  for (i = 0; i < 25; i++){
    fread_double64(&my_d,1,infile);
    printf("double64 Was  : %le \n", my_d);
  }
  fread_double64(&my_d,1,infile);
  printf("exp(1) double64 Was  : %f \n", my_d);
}



void test_parsers_be(){
  FILE* infile;
  int i;

  unsigned char my_uc;
  char my_c;
  
  unsigned short my_us;
  short my_s;
  
  unsigned int my_ui;
  int my_i;

  float my_f;
  
  double my_d;
  
  if ((infile = fopen("BigEndianTest.bin", "rb")) == NULL)
    {
      printf("Unable to open the file\n");
      return ;
    }
  
  for (i = 0; i < 255; i++){
    fread_be_uchar(&my_uc,1, infile);
    printf("Was  : %d should be %d\n",my_uc,i);
  }
  
  for (i = -128; i < 127; i++){
    fread_be_char(&my_c,1, infile);  
    printf("Was  : %d should be %d\n",my_c,i);
  }
  
  for (i =0; i < 15; i++){
    fread_be_uint16(&my_us,1,infile);
    printf("Was  : %d \n", my_us);
  } 
  
  for (i=0; i < 15; i++){
    fread_be_int16(&my_s,1,infile);
    printf("Was  : %d \n", my_s);
  }

  for (i=0; i < 31; i++){
    fread_be_uint32(&my_ui,1,infile);
    printf("uint32 Was  : %d \n", my_ui);
  }
  
  
  for (i=0; i < 31; i++){
    fread_be_int32(&my_i,1, infile);
    printf("int32 Was  : %d \n", my_i);
  }

  
  for (i = 0; i < 25; i++){
    fread_be_float32(&my_f,1,infile);   
    printf("float32 Was  : %e \n", my_f);
  }
  fread_be_float32(&my_f,1,infile);
  printf("PI float32 Was  : %f \n", my_f);

  
  for (i = 0; i < 25; i++){
    fread_be_double64(&my_d,1,infile);
    printf("double64 Was  : %le \n", my_d);
  }
  fread_be_double64(&my_d,1,infile);
  printf("exp(1) double64 Was  : %f \n", my_d);
}

