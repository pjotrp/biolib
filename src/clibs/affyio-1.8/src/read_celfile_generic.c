/*************************************************************
 **
 ** file: read_celfile_generic.c
 **
 ** Written by B. M. Bolstad <bmb@bmbolstad.com>
 **
 ** Aim is to read in Affymetrix CEL files in the
 ** "Command Console Generic Data" File Format
 ** This format is sometimes known as the Calvin format
 **
 ** As with other file format functionality in affyio
 ** gzipped files are accepted.
 **
 ** The implementation here is based upon openly available 
 ** file format information. The code here is not dependent or based
 ** in anyway on that in the Fusion SDK.
 **
 **
 ** History
 ** Sept 3, 2007 -Initial version
 ** Sept 9, 2007 - fix compiler warnings
 ** Oct 11, 2007 - fix missing DatHeader problem
 ** Feb 11, 2008 - add #include for inttypes.h in situations that stdint.h might not exist
 ** Feb 13, 2008 - fix problems with generic_get_detailed_header_info(), gzgeneric_get_detailed_header_info()
 **
 *************************************************************/
#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#ifdef HAVE_STDINT_H
#include <stdint.h>
#elif HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#include <wchar.h>

#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#include "read_generic.h"
#include "read_celfile_generic.h"
#include "read_abatch.h"

int isGenericCelFile(const char *filename){

  FILE *infile;
  generic_file_header file_header;
  generic_data_header data_header;
  
  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }

  if (!read_generic_file_header(&file_header,infile)){
    fclose(infile);
    return 0;
  }

  if (!read_generic_data_header(&data_header,infile)){
    Free_generic_data_header(&data_header);
    fclose(infile);
    return 0;
  }
  
  if (strcmp(data_header.data_type_id.value, "affymetrix-calvin-intensity") !=0){
    Free_generic_data_header(&data_header);
 


   fclose(infile);
    return 0;
  }
  Free_generic_data_header(&data_header);
  
  fclose(infile);
  return 1;
}



char *generic_get_header_info(const char *filename, int *dim1, int *dim2){

  FILE *infile;
  generic_file_header file_header;
  generic_data_header data_header;

  char *cdfName = 0;

  nvt_triplet *triplet;
  AffyMIMEtypes cur_mime_type;

  int size;

  wchar_t *wchartemp=0;
  
  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }
  
  read_generic_file_header(&file_header,infile);
  read_generic_data_header(&data_header,infile);

  /*  affymetrix-array-type  text/plainText/plain String is HG-U133_Plus_2
      Now Trying it again. But using exposed function
      Its a Text/plain string value is HG-U133_Plus_2 with size 14
      affymetrix-cel-cols  text/x-calvin-integer-32Its a int32_t  value is 1164
      Now Trying it again. But using exposed function
      Its a int32_t  value is 1164
      affymetrix-cel-rows  text/x-calvin-integer-32Its a int32_t  value is 1164
  */

  triplet =  find_nvt(&data_header,"affymetrix-array-type");
  
  cur_mime_type = determine_MIMETYPE(*triplet);

  wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
  cdfName = Calloc(size + 1, char);
  wcstombs(cdfName, wchartemp, size);
  Free(wchartemp);

  triplet =  find_nvt(&data_header,"affymetrix-cel-cols");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, dim1, &size);
  
  triplet =  find_nvt(&data_header,"affymetrix-cel-rows");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, dim2, &size);
  
  Free_generic_data_header(&data_header);
  fclose(infile);

  return cdfName;
 
}




void generic_get_detailed_header_info(const char *filename, detailed_header_info *header_info){
  
  FILE *infile;
  generic_file_header file_header;
  generic_data_header data_header;
  nvt_triplet *triplet;
  AffyMIMEtypes cur_mime_type;
  int size;

  int algorithm_paramsize = 0;
  float tempfloat;

  wchar_t *wchartemp=0;
  char *chartemp=0;
  
  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
    }
  
  read_generic_file_header(&file_header,infile);
  read_generic_data_header(&data_header,infile);
  
  triplet =  find_nvt(&data_header,"affymetrix-array-type");

  cur_mime_type = determine_MIMETYPE(*triplet);

  wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
  header_info->cdfName = Calloc(size + 1, char);
  wcstombs(header_info->cdfName, wchartemp, size);
  Free(wchartemp);

  triplet =  find_nvt(&data_header,"affymetrix-cel-cols");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &(header_info->cols), &size);
  
  triplet =  find_nvt(&data_header,"affymetrix-cel-rows");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &(header_info->rows), &size);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridULX"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerULx = (int)(tempfloat +0.5);

  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridULY"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerULy = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridURX"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerURx = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridURY"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerURy = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridLLX"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerLLx = (int)(tempfloat +0.5);

  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridLLY"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerLLy = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridLRX"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerLRx = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridLRY"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerLRy = (int)(tempfloat +0.5);
  
    
  triplet =  find_nvt(&data_header,"affymetrix-dat-header");
  
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
    header_info->DatHeader = Calloc(size + 1, char);
    wcstombs(header_info->DatHeader, wchartemp, size);
    Free(wchartemp);
  } else {
    header_info->DatHeader = Calloc(2, char);
  }



  triplet =  find_nvt(&data_header,"affymetrix-algorithm-name");
  cur_mime_type = determine_MIMETYPE(*triplet);

  wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
  header_info->Algorithm = Calloc(size + 1, char);
  wcstombs(header_info->Algorithm, wchartemp, size);
  Free(wchartemp);
  


  //  "Percentile:75;CellMargin:2;OutlierHigh:1.500;OutlierLow:1.004;AlgVersion:6.0;FixedCellSize:TRUE;FullFeatureWidth:7;FullFeatureHeight:7;IgnoreOutliersInShiftRows:FALSE;FeatureExtraction:TRUE;PoolWidthExtenstion:2;PoolHeightExtension:2;UseSubgrids:FALSE;RandomizePixels:FALSE;ErrorBasis:StdvMean;StdMult:1.00000"

  algorithm_paramsize = 0;
  
  header_info->AlgorithmParameters = Calloc(11, char);
  strncpy(header_info->AlgorithmParameters,"Percentile:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-Percentile");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 11, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"CellMargin:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-CellMargin"); 
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 12, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"OutlierHigh:",12);
  algorithm_paramsize+=12;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-OutlierHigh");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 11, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"OutlierLow:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-OutlierLow");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 11, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"AlgVersion:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-AlgVersion");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 14, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"FixedCellSize:",14);
  algorithm_paramsize+=14;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-FixedCellSize");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 17, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"FullFeatureWidth:",17);
  algorithm_paramsize+=17;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-FullFeatureWidth");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
     Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 18, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"FullFeatureHeight:",18);
  algorithm_paramsize+=18;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-FullFeatureHeight");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 26, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"IgnoreOutliersInShiftRows:",26);
  algorithm_paramsize+=26;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-IgnoreOutliersInShiftRows");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }



  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 18, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"FeatureExtraction:",18);
  algorithm_paramsize+=18;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-FeatureExtraction");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }



  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 20, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"PoolWidthExtenstion:",20);
  algorithm_paramsize+=20;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-PoolWidthExtenstion");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 20, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"PoolHeightExtension:",20);
  algorithm_paramsize+=20;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-PoolHeightExtension");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }


  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 12, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"UseSubgrids:",12);
  algorithm_paramsize+=12;
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-UseSubgrids");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }


  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 16, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"RandomizePixels:",16);
  algorithm_paramsize+=16;
    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-RandomizePixels");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }



  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 11, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"ErrorBasis:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-ErrorBasis");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 8, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"StdMult:",8);
  algorithm_paramsize+=8;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-StdMult");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }


  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
  header_info->AlgorithmParameters[algorithm_paramsize] ='\0';
  

  Free_generic_data_header(&data_header);
  fclose(infile);



}




int check_generic_cel_file(const char *filename, const char *ref_cdfName, int ref_dim_1, int ref_dim_2){

  char *cdfName =0;
  int dim1, dim2;


  FILE *infile;
  generic_file_header file_header;
  generic_data_header data_header;
  
  nvt_triplet *triplet;
  AffyMIMEtypes cur_mime_type;
  
  int size;

  wchar_t *wchartemp=0;
  

  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }

  read_generic_file_header(&file_header,infile);
  read_generic_data_header(&data_header,infile);
  

   triplet =  find_nvt(&data_header,"affymetrix-array-type");
  
  cur_mime_type = determine_MIMETYPE(*triplet);

  wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
  cdfName = Calloc(size + 1, char);
  wcstombs(cdfName, wchartemp, size);
  Free(wchartemp);

  triplet =  find_nvt(&data_header,"affymetrix-cel-cols");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &dim1, &size);
  
  triplet =  find_nvt(&data_header,"affymetrix-cel-rows");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &dim2, &size);
  
  Free_generic_data_header(&data_header);
  
  if ((dim1 != ref_dim_1) || (dim2 != ref_dim_2)){
    error("Cel file %s does not seem to have the correct dimensions",filename);
  }
  
  if (strncasecmp(cdfName,ref_cdfName,strlen(ref_cdfName)) != 0){
    error("Cel file %s does not seem to be of %s type",filename,ref_cdfName);
  }

  Free(cdfName);


  fclose(infile);
  return 0;
}




/***************************************************************
 **
 ** static int read_binarycel_file_intensities(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows)
 **
 ** 
 ** This function reads binary cel file intensities into the data matrix
 **
 **************************************************************/

int read_genericcel_file_intensities(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows){

  int i=0, j=0;
  int cur_index;
  
  int fread_err=0;
  
  FILE *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;


  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      return 0;
    }
  

  
  read_generic_file_header(&my_header, infile);
  read_generic_data_header(&my_data_header, infile);
  read_generic_data_group(&my_data_group,infile);

  read_generic_data_set(&my_data_set,infile); 
  read_generic_data_set_rows(&my_data_set,infile); 

  for (i =0; i < my_data_set.nrows; i++){
    intensity[chip_num*my_data_set.nrows + i] = (double)(((float *)my_data_set.Data[0])[i]);
  }
  
  fclose(infile);
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);




  return(0);
}





int read_genericcel_file_stddev(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows){

  int i=0, j=0;
  int cur_index;
  
  int fread_err=0;
  
  FILE *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;


  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      return 0;
    }
  

  
  read_generic_file_header(&my_header, infile);
  read_generic_data_header(&my_data_header, infile);
  read_generic_data_group(&my_data_group,infile);

  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  read_generic_data_set(&my_data_set,infile); 
  read_generic_data_set_rows(&my_data_set,infile); 
  for (i =0; i < my_data_set.nrows; i++){
    intensity[chip_num*my_data_set.nrows + i] = (double)(((float *)my_data_set.Data[0])[i]);
  }
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);

  fclose(infile);


  return(0);





}



int read_genericcel_file_npixels(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows){

  int i=0, j=0;
  int cur_index;
  
  int fread_err=0;
  
  FILE *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;


  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      return 0;
    }
  

  
  read_generic_file_header(&my_header, infile);
  read_generic_data_header(&my_data_header, infile);
  read_generic_data_group(&my_data_group,infile);

  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
  

  read_generic_data_set(&my_data_set,infile); 
  read_generic_data_set_rows(&my_data_set,infile); 
  for (i =0; i < my_data_set.nrows; i++){
    intensity[chip_num*my_data_set.nrows + i] = (double)(((short *)my_data_set.Data[0])[i]);
  }
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);

  fclose(infile);


  return(0);




}




void generic_get_masks_outliers(const char *filename, int *nmasks, short **masks_x, short **masks_y, int *noutliers, short **outliers_x, short **outliers_y){




  int i=0, j=0;
  int cur_index;
  
  int fread_err=0;
  
  FILE *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;


  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      
    }
  

  
  read_generic_file_header(&my_header, infile);
  read_generic_data_header(&my_data_header, infile);
  read_generic_data_group(&my_data_group,infile);

  /* passing the intensities */
  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  /* passing by the stddev */
  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
  
  /* passing by the npixels */
  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  /* Now lets go for the "Outlier" */
  read_generic_data_set(&my_data_set,infile); 
   
  
  *noutliers = my_data_set.nrows;

  *outliers_x = Calloc(my_data_set.nrows,short); 
  *outliers_y = Calloc(my_data_set.nrows,short);
  
  read_generic_data_set_rows(&my_data_set,infile); 
  
  for (i=0; i < my_data_set.nrows; i++){
    (*outliers_x)[i] = ((short *)my_data_set.Data[0])[i];
    (*outliers_y)[i] = ((short *)my_data_set.Data[1])[i];
  }
  
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);

  /* Now lets go for the "Mask" */
  read_generic_data_set(&my_data_set,infile); 
   
  *nmasks = my_data_set.nrows;

  *masks_x = Calloc(my_data_set.nrows,short); 
  *masks_y = Calloc(my_data_set.nrows,short);
  
  
  read_generic_data_set_rows(&my_data_set,infile); 
  for (i=0; i < my_data_set.nrows; i++){
    (*outliers_x)[i] = ((short *)my_data_set.Data[0])[i];
    (*outliers_y)[i] = ((short *)my_data_set.Data[1])[i];
  }
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);

  fclose(infile);
  
}





void generic_apply_masks(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows, int rm_mask, int rm_outliers){


  int i=0, j=0;
  int cur_index;
  
  short cur_x, cur_y;


  int fread_err=0;
  int nrows;
  int size;

  FILE *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;
  nvt_triplet *triplet;
  AffyMIMEtypes cur_mime_type;

  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      
    }
 

  
  read_generic_file_header(&my_header, infile);
  read_generic_data_header(&my_data_header, infile);
  read_generic_data_group(&my_data_group,infile);

    
  triplet =  find_nvt(&my_data_header,"affymetrix-cel-rows");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &nrows, &size);
  


  /* passing the intensities */
  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  /* passing by the stddev */
  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
  
  /* passing by the npixels */
  read_generic_data_set(&my_data_set,infile); 
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  /* Now lets go for the "Outlier" */
  read_generic_data_set(&my_data_set,infile); 
  
  if (rm_outliers){
    read_generic_data_set_rows(&my_data_set,infile); 
    for (i=0; i < my_data_set.nrows; i++){
      cur_x = ((short *)my_data_set.Data[0])[i];
      cur_y = ((short *)my_data_set.Data[1])[i];
      cur_index = (int)cur_x + nrows*(int)cur_y; 
      intensity[chip_num*rows + cur_index] =  R_NaN;
    }
  }
  
  fseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);

  /* Now lets go for the "Mask" */
  read_generic_data_set(&my_data_set,infile); 
  if (rm_mask){
    read_generic_data_set_rows(&my_data_set,infile); 
    for (i=0; i < my_data_set.nrows; i++){
      cur_x = ((short *)my_data_set.Data[0])[i];
      cur_y = ((short *)my_data_set.Data[1])[i];
      cur_index = (int)cur_x + nrows*(int)cur_y; 
      intensity[chip_num*rows + cur_index] =  R_NaN;
    }
  }
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);

  fclose(infile);
  
}

/*******************************************************************************************************
 *******************************************************************************************************
 **
 ** Code below supports gzipped command console format CEL files
 **
 *******************************************************************************************************
 *******************************************************************************************************/


int isgzGenericCelFile(const char *filename){

  gzFile *infile;
  generic_file_header file_header;
  generic_data_header data_header;
  
  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }

  if (!gzread_generic_file_header(&file_header,infile)){
    gzclose(infile);
    return 0;
  }

  if (!gzread_generic_data_header(&data_header,infile)){
    Free_generic_data_header(&data_header);
    gzclose(infile);
    return 0;
  }
  
  if (strcmp(data_header.data_type_id.value, "affymetrix-calvin-intensity") !=0){
    Free_generic_data_header(&data_header);
 


   gzclose(infile);
    return 0;
  }
  Free_generic_data_header(&data_header);
  
  gzclose(infile);
  return 1;
}



char *gzgeneric_get_header_info(const char *filename, int *dim1, int *dim2){

  gzFile *infile;
  generic_file_header file_header;
  generic_data_header data_header;

  char *cdfName = 0;

  nvt_triplet *triplet;
  AffyMIMEtypes cur_mime_type;

  int size;

  wchar_t *wchartemp=0;
  
  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }
  
  gzread_generic_file_header(&file_header,infile);
  gzread_generic_data_header(&data_header,infile);

  /*  affymetrix-array-type  text/plainText/plain String is HG-U133_Plus_2
      Now Trying it again. But using exposed function
      Its a Text/plain string value is HG-U133_Plus_2 with size 14
      affymetrix-cel-cols  text/x-calvin-integer-32Its a int32_t  value is 1164
      Now Trying it again. But using exposed function
      Its a int32_t  value is 1164
      affymetrix-cel-rows  text/x-calvin-integer-32Its a int32_t  value is 1164
  */

  triplet =  find_nvt(&data_header,"affymetrix-array-type");
  
  cur_mime_type = determine_MIMETYPE(*triplet);

  wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
  cdfName = Calloc(size + 1, char);
  wcstombs(cdfName, wchartemp, size);
  Free(wchartemp);

  triplet =  find_nvt(&data_header,"affymetrix-cel-cols");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, dim1, &size);
  
  triplet =  find_nvt(&data_header,"affymetrix-cel-rows");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, dim2, &size);
  
  Free_generic_data_header(&data_header);
  gzclose(infile);

  return cdfName;
 
}




void gzgeneric_get_detailed_header_info(const char *filename, detailed_header_info *header_info){
  
  gzFile *infile;
  generic_file_header file_header;
  generic_data_header data_header;
  nvt_triplet *triplet;
  AffyMIMEtypes cur_mime_type;
  int size;

  int algorithm_paramsize = 0;
  float tempfloat;

  wchar_t *wchartemp = 0;
  char *chartemp = 0;
  
  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
    }
  
  gzread_generic_file_header(&file_header,infile);
  gzread_generic_data_header(&data_header,infile);
  
  triplet =  find_nvt(&data_header,"affymetrix-array-type");

  cur_mime_type = determine_MIMETYPE(*triplet);

  wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
  header_info->cdfName = Calloc(size + 1, char);
  wcstombs(header_info->cdfName, wchartemp, size);
  Free(wchartemp);

  triplet =  find_nvt(&data_header,"affymetrix-cel-cols");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &(header_info->cols), &size);
  
  triplet =  find_nvt(&data_header,"affymetrix-cel-rows");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &(header_info->rows), &size);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridULX"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerULx = (int)(tempfloat +0.5);

  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridULY"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerULy = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridURX"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerURx = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridURY"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerURy = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridLLX"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerLLx = (int)(tempfloat +0.5);

  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridLLY"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerLLy = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridLRX"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerLRx = (int)(tempfloat +0.5);
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-GridLRY"); 
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &tempfloat, &size);
  header_info->GridCornerLRy = (int)(tempfloat +0.5);
  
    
  triplet =  find_nvt(&data_header,"affymetrix-dat-header");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
    header_info->DatHeader = Calloc(size + 1, char);
    wcstombs(header_info->DatHeader, wchartemp, size);
    Free(wchartemp);
  } else {
    header_info->DatHeader = Calloc(2, char);
  }



  triplet =  find_nvt(&data_header,"affymetrix-algorithm-name");
  cur_mime_type = determine_MIMETYPE(*triplet);

  wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
  header_info->Algorithm = Calloc(size + 1, char);
  wcstombs(header_info->Algorithm, wchartemp, size);
  Free(wchartemp);
  


  //  "Percentile:75;CellMargin:2;OutlierHigh:1.500;OutlierLow:1.004;AlgVersion:6.0;FixedCellSize:TRUE;FullFeatureWidth:7;FullFeatureHeight:7;IgnoreOutliersInShiftRows:FALSE;FeatureExtraction:TRUE;PoolWidthExtenstion:2;PoolHeightExtension:2;UseSubgrids:FALSE;RandomizePixels:FALSE;ErrorBasis:StdvMean;StdMult:1.00000"

  algorithm_paramsize = 0;
  
  header_info->AlgorithmParameters = Calloc(11, char);
  strncpy(header_info->AlgorithmParameters,"Percentile:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-Percentile");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 11, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"CellMargin:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-CellMargin"); 
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 12, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"OutlierHigh:",12);
  algorithm_paramsize+=12;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-OutlierHigh");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 11, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"OutlierLow:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-OutlierLow");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 11, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"AlgVersion:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-AlgVersion");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 14, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"FixedCellSize:",14);
  algorithm_paramsize+=14;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-FixedCellSize");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 17, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"FullFeatureWidth:",17);
  algorithm_paramsize+=17;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-FullFeatureWidth");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
     Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 18, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"FullFeatureHeight:",18);
  algorithm_paramsize+=18;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-FullFeatureHeight");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }
  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 26, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"IgnoreOutliersInShiftRows:",26);
  algorithm_paramsize+=26;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-IgnoreOutliersInShiftRows");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }



  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 18, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"FeatureExtraction:",18);
  algorithm_paramsize+=18;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-FeatureExtraction");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }



  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 20, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"PoolWidthExtenstion:",20);
  algorithm_paramsize+=20;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-PoolWidthExtenstion");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 20, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"PoolHeightExtension:",20);
  algorithm_paramsize+=20;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-PoolHeightExtension");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }


  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 12, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"UseSubgrids:",12);
  algorithm_paramsize+=12;
  
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-UseSubgrids");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }


  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 16, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"RandomizePixels:",16);
  algorithm_paramsize+=16;
    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-RandomizePixels");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }



  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 11, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"ErrorBasis:",11);
  algorithm_paramsize+=11;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-ErrorBasis");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }

  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 8, char);
  strncpy(&header_info->AlgorithmParameters[algorithm_paramsize],"StdMult:",8);
  algorithm_paramsize+=8;

    
  triplet =  find_nvt(&data_header,"affymetrix-algorithm-param-StdMult");
  if (triplet != NULL){
    cur_mime_type = determine_MIMETYPE(*triplet);
    
    chartemp = decode_MIME_value_toASCII(*triplet,cur_mime_type, chartemp, &size);
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + size +1, char);
    strncpy(&header_info->AlgorithmParameters[algorithm_paramsize], chartemp, size);
    algorithm_paramsize+= size +1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
    Free(chartemp);
  } else {
    header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
    algorithm_paramsize+= 1;
    header_info->AlgorithmParameters[algorithm_paramsize-1]=';';
  }


  
  header_info->AlgorithmParameters = Realloc(header_info->AlgorithmParameters, algorithm_paramsize + 1, char);
  header_info->AlgorithmParameters[algorithm_paramsize] ='\0';

  Free_generic_data_header(&data_header);
  gzclose(infile);
}








int check_gzgeneric_cel_file(const char *filename, const char *ref_cdfName, int ref_dim_1, int ref_dim_2){

  char *cdfName =0;
  int dim1, dim2;


  gzFile *infile;
  generic_file_header file_header;
  generic_data_header data_header;
  
  nvt_triplet *triplet;
  AffyMIMEtypes cur_mime_type;
  
  int size;

  wchar_t *wchartemp=0;
  

  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }

  gzread_generic_file_header(&file_header,infile);
  gzread_generic_data_header(&data_header,infile);
  

  triplet =  find_nvt(&data_header,"affymetrix-array-type");
  
  cur_mime_type = determine_MIMETYPE(*triplet);

  wchartemp = decode_MIME_value(*triplet,cur_mime_type, wchartemp, &size);
  cdfName = Calloc(size + 1, char);
  wcstombs(cdfName, wchartemp, size);
  Free(wchartemp);

  triplet =  find_nvt(&data_header,"affymetrix-cel-cols");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &dim1, &size);
  
  triplet =  find_nvt(&data_header,"affymetrix-cel-rows");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &dim2, &size);
  
  Free_generic_data_header(&data_header);
  
  if ((dim1 != ref_dim_1) || (dim2 != ref_dim_2)){
    error("Cel file %s does not seem to have the correct dimensions",filename);
  }
  
  if (strncasecmp(cdfName,ref_cdfName,strlen(ref_cdfName)) != 0){
    error("Cel file %s does not seem to be of %s type",filename,ref_cdfName);
  }

  Free(cdfName);


  gzclose(infile);
  return 0;
}






int gzread_genericcel_file_intensities(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows){

  int i=0, j=0;
  int cur_index;
  
  int fread_err=0;
  
  gzFile *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;


  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      return 0;
    }
  

  
  gzread_generic_file_header(&my_header, infile);
  gzread_generic_data_header(&my_data_header, infile);
  gzread_generic_data_group(&my_data_group,infile);

  gzread_generic_data_set(&my_data_set,infile); 
  gzread_generic_data_set_rows(&my_data_set,infile); 

  for (i =0; i < my_data_set.nrows; i++){
    intensity[chip_num*my_data_set.nrows + i] = (double)(((float *)my_data_set.Data[0])[i]);
  }
  
  gzclose(infile);
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);




  return(0);
}






int gzread_genericcel_file_stddev(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows){

  int i=0, j=0;
  int cur_index;
  
  int fread_err=0;
  
  gzFile *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;


  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      return 0;
    }
  

  
  gzread_generic_file_header(&my_header, infile);
  gzread_generic_data_header(&my_data_header, infile);
  gzread_generic_data_group(&my_data_group,infile);

  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  gzread_generic_data_set(&my_data_set,infile); 
  gzread_generic_data_set_rows(&my_data_set,infile); 
  for (i =0; i < my_data_set.nrows; i++){
    intensity[chip_num*my_data_set.nrows + i] = (double)(((float *)my_data_set.Data[0])[i]);
  }
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);

  gzclose(infile);


  return(0);





}



int gzread_genericcel_file_npixels(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows){

  int i=0, j=0;
  int cur_index;
  
  int fread_err=0;
  
  gzFile *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;


  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      return 0;
    }
  

  
  gzread_generic_file_header(&my_header, infile);
  gzread_generic_data_header(&my_data_header, infile);
  gzread_generic_data_group(&my_data_group,infile);

  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
  

  gzread_generic_data_set(&my_data_set,infile); 
  gzread_generic_data_set_rows(&my_data_set,infile); 
  for (i =0; i < my_data_set.nrows; i++){
    intensity[chip_num*my_data_set.nrows + i] = (double)(((short *)my_data_set.Data[0])[i]);
  }
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);

  gzclose(infile);


  return(0);




}







void gzgeneric_get_masks_outliers(const char *filename, int *nmasks, short **masks_x, short **masks_y, int *noutliers, short **outliers_x, short **outliers_y){




  int i=0, j=0;
  int cur_index;
  
  int fread_err=0;
  
  gzFile *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;


  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      
    }
  

  
  gzread_generic_file_header(&my_header, infile);
  gzread_generic_data_header(&my_data_header, infile);
  gzread_generic_data_group(&my_data_group,infile);

  /* passing the intensities */
  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  /* passing by the stddev */
  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
  
  /* passing by the npixels */
  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  /* Now lets go for the "Outlier" */
  gzread_generic_data_set(&my_data_set,infile); 
   
  
  *noutliers = my_data_set.nrows;

  *outliers_x = Calloc(my_data_set.nrows,short); 
  *outliers_y = Calloc(my_data_set.nrows,short);
  
  gzread_generic_data_set_rows(&my_data_set,infile); 
  
  for (i=0; i < my_data_set.nrows; i++){
    (*outliers_x)[i] = ((short *)my_data_set.Data[0])[i];
    (*outliers_y)[i] = ((short *)my_data_set.Data[1])[i];
  }
  
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);

  /* Now lets go for the "Mask" */
  gzread_generic_data_set(&my_data_set,infile); 
   
  *nmasks = my_data_set.nrows;

  *masks_x = Calloc(my_data_set.nrows,short); 
  *masks_y = Calloc(my_data_set.nrows,short);
  
  
  gzread_generic_data_set_rows(&my_data_set,infile); 
  for (i=0; i < my_data_set.nrows; i++){
    (*outliers_x)[i] = ((short *)my_data_set.Data[0])[i];
    (*outliers_y)[i] = ((short *)my_data_set.Data[1])[i];
  }
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);

  gzclose(infile);
  
}





void gzgeneric_apply_masks(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows, int rm_mask, int rm_outliers){


  int i=0, j=0;
  int cur_index;
  
  short cur_x, cur_y;


  int fread_err=0;
  int nrows;
  int size;

  gzFile *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;
  nvt_triplet *triplet;
  AffyMIMEtypes cur_mime_type;

  if ((infile = gzopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",filename);
      
    }
 

  
  gzread_generic_file_header(&my_header, infile);
  gzread_generic_data_header(&my_data_header, infile);
  gzread_generic_data_group(&my_data_group,infile);

    
  triplet =  find_nvt(&my_data_header,"affymetrix-cel-rows");
  cur_mime_type = determine_MIMETYPE(*triplet);
  decode_MIME_value(*triplet,cur_mime_type, &nrows, &size);
  


  /* passing the intensities */
  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  /* passing by the stddev */
  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
  
  /* passing by the npixels */
  gzread_generic_data_set(&my_data_set,infile); 
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);
 
  /* Now lets go for the "Outlier" */
  gzread_generic_data_set(&my_data_set,infile); 
  
  if (rm_outliers){
    gzread_generic_data_set_rows(&my_data_set,infile); 
    for (i=0; i < my_data_set.nrows; i++){
      cur_x = ((short *)my_data_set.Data[0])[i];
      cur_y = ((short *)my_data_set.Data[1])[i];
      cur_index = (int)cur_x + nrows*(int)cur_y; 
      intensity[chip_num*rows + cur_index] =  R_NaN;
    }
  }
  
  gzseek(infile, my_data_set.file_pos_last, SEEK_SET); 
  Free_generic_data_set(&my_data_set);

  /* Now lets go for the "Mask" */
  gzread_generic_data_set(&my_data_set,infile); 
  if (rm_mask){
    gzread_generic_data_set_rows(&my_data_set,infile); 
    for (i=0; i < my_data_set.nrows; i++){
      cur_x = ((short *)my_data_set.Data[0])[i];
      cur_y = ((short *)my_data_set.Data[1])[i];
      cur_index = (int)cur_x + nrows*(int)cur_y; 
      intensity[chip_num*rows + cur_index] =  R_NaN;
    }
  }
  Free_generic_data_set(&my_data_set);
  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);
  
  gzclose(infile);
  
}



