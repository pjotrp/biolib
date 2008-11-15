/*************************************************************
 **
 ** file: read_generic.c
 **
 ** Written by B. M. Bolstad <bmb@bmbolstad.com>
 **
 ** Aim is to read in Affymetrix files in the
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
 ** Aug 25, 2007 - Initial version
 ** Sep 9, 2007  - fix some compiler warnings.
 ** Oct 25, 2007 - fix error in decode_UINT8_t
 ** Jan 28, 2008 - fix read_generic_data_group/gzread_generic_data_group. Change bitwise OR (|) to logical OR (||)
 ** Feb 11, 2008 - add #include for inttypes.h in situations that stdint.h might not exist
 ** Feb 13, 2008 - add decode_MIME_value_toASCII which takes any MIME and attempts to convert to a string
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


#include "fread_functions.h"

#include "read_generic.h"


static void Free_ASTRING(ASTRING *string){
  Free(string->value);
  string->len =0;
}


static void Free_AWSTRING(AWSTRING *string){
  Free(string->value);
  string->len =0;


}


static void Free_nvt_triplet(nvt_triplet *triplet){
  Free_AWSTRING(&(triplet->name));
  Free_ASTRING(&(triplet->value));
  Free_AWSTRING(&(triplet->type));
}


static void Free_nvts_triplet(col_nvts_triplet *triplet){
  Free_AWSTRING(&(triplet->name));

}





void Free_generic_data_header(generic_data_header *header){
  
  int i;
  generic_data_header *temp;

  Free_ASTRING(&(header->data_type_id));
  Free_ASTRING(&(header->unique_file_id));
  Free_AWSTRING(&(header->Date_time));
  Free_AWSTRING(&(header->locale));
  
  for (i =0; i <  header->n_name_type_value; i++){
    Free_nvt_triplet(&(header->name_type_value[i]));
  }
  Free(header->name_type_value);
    
  for (i=0; i < (header->n_parent_headers); i++){
    temp = (generic_data_header *)header->parent_headers[i];
    Free_generic_data_header(temp);
    Free(temp);
  }
  if (header->parent_headers != 0)
    Free(header->parent_headers);


}


void Free_generic_data_group(generic_data_group *data_group){


  Free_AWSTRING(&(data_group->data_group_name));

}


void Free_generic_data_set(generic_data_set *data_set){

  int i;

  Free_AWSTRING(&(data_set->data_set_name));

  for (i =0; i <  data_set->n_name_type_value; i++){
    Free_nvt_triplet(&(data_set->name_type_value[i]));
  }
  Free(data_set->name_type_value);

  for (i=0; i < data_set->ncols; i++){
    Free_nvts_triplet(&(data_set->col_name_type_value[i]));
  }
  Free(data_set->col_name_type_value);

  for (i= 0; i < data_set->ncols; i++){
    Free(data_set->Data[i]);
  }
  Free(data_set->Data);

  
}
  

static int fread_ASTRING(ASTRING *destination, FILE *instream){

  fread_be_int32(&(destination->len),1,instream);
  if (destination->len > 0){
    destination->value = Calloc(destination->len+1,char);
    fread_be_char(destination->value,destination->len,instream);
  } else {
    destination->value = 0;
  }
  return 1;
}



static int fread_AWSTRING(AWSTRING *destination, FILE *instream){

  uint16_t temp;   /* Affy file wchar_t are 16 bits, the platform may have  32 bit wchar_t (notatbly linux) */

  int i;

  fread_be_int32(&(destination->len),1,instream);
  if ((destination->len) > 0){
    destination->value = Calloc(destination->len+1,wchar_t);
  
    for (i=0; i < destination->len; i++){
      fread_be_uint16(&temp,1,instream);
      destination->value[i] = (wchar_t)temp;
    }
  } else {
    destination->value = 0;
  }
  
  return 1;
}


static int fread_nvt_triplet(nvt_triplet *destination, FILE *instream){

  if (!(fread_AWSTRING(&(destination->name),instream)) ||
      !(fread_ASTRING(&(destination->value),instream)) ||
      !fread_AWSTRING(&(destination->type),instream)){
    return 0;
  }
  return 1;
}


static int fread_nvts_triplet(col_nvts_triplet *destination, FILE *instream){

  if (!(fread_AWSTRING(&(destination->name),instream)) ||
      !(fread_be_uchar(&(destination->type), 1, instream)) ||
      !(fread_be_int32(&(destination->size), 1, instream))){
    return 0;
  }
  return 1;
}


/* The Value is MIME text/ASCII */

static char *decode_ASCII(ASTRING value){
  
  char *return_value;

  return_value = Calloc(value.len+1,char);
  
  memcpy(return_value, value.value, value.len);


  return return_value;
}



/* The value is MIME text/plain which means wchar (16bit) string */


static wchar_t *decode_TEXT(ASTRING value){

  int i;

  uint32_t len = value.len/ sizeof(uint16_t);
  wchar_t* return_value = Calloc(len+1,wchar_t);
  ASTRING temp;
  uint16_t *contents;

  temp.len = value.len;
  temp.value = Calloc(value.len, char);
  memcpy(temp.value, value.value,value.len);
  
  contents = (uint16_t *)temp.value;
  
  for (i=0; i < len; i++){
#ifndef WORD_BIGENDIAN 
    contents[i]=(((contents[i]>>8)&0xff) | ((contents[i]&0xff)<<8));
#endif
    return_value[i] = contents[i];
  }
  Free_ASTRING(&temp);

  return return_value;
}


static int8_t decode_INT8_t(ASTRING value){

  int8_t contents;
  
  memcpy(&contents,value.value, sizeof(int8_t));

  //#ifndef WORD_BIGENDIAN 
  //  contents=(((contents[i]>>8)&0xff) | ((contents[i]&0xff)<<8));//
  //#endif 


  return contents;

}


static uint8_t decode_UINT8_t(ASTRING value){

  uint8_t contents;
  
  memcpy(&contents,value.value, sizeof(uint8_t));

  //#ifndef WORD_BIGENDIAN 
  //contents=(((contents[i]>>8)&0xff) | ((contents[i]&0xff)<<8));
  //#endif 
  return contents;

}


static int16_t decode_INT16_t(ASTRING value){

  int16_t contents;
  
  memcpy(&contents,value.value, sizeof(int16_t));

#ifndef WORD_BIGENDIAN 
  contents=(((contents>>8)&0xff) | ((contents&0xff)<<8));
#endif 


  return contents;

}


static uint16_t decode_UINT16_t(ASTRING value){

  uint16_t contents;
  
  memcpy(&contents,value.value, sizeof(uint16_t));

#ifndef WORD_BIGENDIAN 
  contents=(((contents>>8)&0xff) | ((contents&0xff)<<8));
#endif 
  return contents;

}




static int32_t decode_INT32_t(ASTRING value){

  int32_t contents;
  
  memcpy(&contents,value.value, sizeof(int32_t));

#ifndef WORD_BIGENDIAN 
  contents=(((contents>>24)&0xff) | ((contents&0xff)<<24) |
		((contents>>8)&0xff00) | ((contents&0xff00)<<8));  
#endif 


  return contents;

}

static int32_t decode_UINT32_t(ASTRING value){

  uint32_t contents;
  
  memcpy(&contents,value.value, sizeof(uint32_t));

#ifndef WORD_BIGENDIAN 
  contents=(((contents>>24)&0xff) | ((contents&0xff)<<24) |
		((contents>>8)&0xff00) | ((contents&0xff00)<<8));  
#endif 


  return contents;

}

static float decode_float32(ASTRING value){


  uint32_t contents;
  float returnvalue;

  memcpy(&contents,value.value, sizeof(uint32_t));

#ifndef WORD_BIGENDIAN 
  contents=(((contents>>24)&0xff) | ((contents&0xff)<<24) |
	    ((contents>>8)&0xff00) | ((contents&0xff00)<<8));  
#endif 

  memcpy(&returnvalue,&contents, sizeof(uint32_t));
  
  return returnvalue;


}




AffyMIMEtypes determine_MIMETYPE(nvt_triplet triplet){                      
  if (!wcscmp(triplet.type.value,L"text/x-calvin-float")){
    return FLOAT32;
  }
  
  if (!wcscmp(triplet.type.value,L"text/plain")){
    return PLAINTEXT;
  }
  if (!wcscmp(triplet.type.value,L"text/ascii")){
    return ASCIITEXT;
  }
  if (!wcscmp(triplet.type.value,L"text/x-calvin-integer-32")){
    return INT32;
  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-integer-16")){
    return INT16;
  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-unsigned-integer-32")){
    return UINT32;
  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-unsigned-integer-16")){
    return INT16;
  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-integer-8")){
    return INT8;
  }
  if (!wcscmp(triplet.type.value,L"text/x-calvin-unsigned-integer-8")){
    return UINT8;
  }
  Rprintf("read_generic.c: Unknown MIME type encountered\n");
 
}






void *decode_MIME_value(nvt_triplet triplet, AffyMIMEtypes mimetype, void *result, int *size){

  char *temp;
  wchar_t *temp2;

  if (mimetype == ASCIITEXT){
    temp = decode_ASCII(triplet.value);
    *size = strlen(temp);
    result = temp;
    return temp;
  }

  if (mimetype == PLAINTEXT){
    temp2 = decode_TEXT(triplet.value);
    *size = wcslen(temp2);
    result = temp2;
    return temp2;
  }

  if (mimetype == UINT8){
    *size =1;
    *(uint8_t *)result = decode_UINT8_t(triplet.value);
  }
  
  if (mimetype == INT8){ 
    *size =1;
    *(int8_t *)result = decode_INT8_t(triplet.value);
  }
  
  if (mimetype == UINT16){ 
    *size =1;
    *(uint16_t *)result = decode_UINT16_t(triplet.value);
  }
  
  if (mimetype == INT16){ 
    *size =1;
    *(int16_t *)result = decode_INT16_t(triplet.value);
  }
 
  if (mimetype == UINT32){ 
    *size =1;
    *(uint32_t *)result = decode_UINT32_t(triplet.value);
  }
  
  if (mimetype == INT32){ 
    *size =1;
    *(int32_t *)result = decode_INT32_t(triplet.value);
  }
 
  if (mimetype == FLOAT32){ 
    *size =1;
    *(float *)result = decode_float32(triplet.value);
  }
  return 0;
}



char *decode_MIME_value_toASCII(nvt_triplet triplet, AffyMIMEtypes mimetype, void *result, int *size){

  char *temp;
  wchar_t *temp2;
 

  float temp_float;
  uint8_t temp_uint8;
  uint16_t temp_uint16;
  uint32_t temp_uint32;
  int8_t temp_int8;
  int16_t temp_int16;
  int32_t temp_int32;

  

  if (mimetype == ASCIITEXT){
    temp = decode_ASCII(triplet.value);
    *size = strlen(temp);
    result = temp;
    return temp;
  }

  if (mimetype == PLAINTEXT){
    temp2 = decode_TEXT(triplet.value);
    temp = Calloc(triplet.value.len/2 +1, char);
    wcstombs(temp,temp2,triplet.value.len/2 + 1);
    *size = strlen(temp);
    result = temp;
    return temp;
  }


  /* 64 here is a bit hackish */
  temp = Calloc(64,char);
  if (mimetype == UINT8){
    temp_uint8 = decode_UINT8_t(triplet.value);
    sprintf(temp,"%u",temp_uint8);
    *size = strlen(temp);
    result = temp;
    return temp;
  }
  
  if (mimetype == INT8){ 
    temp_int8 = decode_INT8_t(triplet.value);
    sprintf(temp,"%d",temp_int8);
    *size = strlen(temp);
    result = temp;
    return temp;
  }
  
  if (mimetype == UINT16){ 
    temp_uint16 = decode_UINT16_t(triplet.value);
    sprintf(temp,"%u",temp_uint16);
    *size = strlen(temp);
    result = temp;
    return temp;
  }
  
  if (mimetype == INT16){ 
    temp_int16 = decode_INT16_t(triplet.value);
    sprintf(temp,"%d",temp_int16);
    *size = strlen(temp);
    result = temp;
    return temp;
  }
 
  if (mimetype == UINT32){ 
    temp_uint32 = decode_UINT32_t(triplet.value);
    sprintf(temp,"%u",temp_uint32);
    *size = strlen(temp);
    result = temp;
    return temp;
  }
  
  if (mimetype == INT32){ 
    temp_int32 = decode_INT32_t(triplet.value);
    sprintf(temp,"%d",temp_int32);
    *size = strlen(temp);
    result = temp;
    return temp;
  }
 
  if (mimetype == FLOAT32){ 
    temp_float = decode_float32(triplet.value);
    sprintf(temp,"%f",temp_float);
    *size = strlen(temp);
    result = temp;
    return temp;
  }
  return 0;
}





















nvt_triplet* find_nvt(generic_data_header *data_header,char *name){

  nvt_triplet* returnvalue = 0;

  wchar_t *wname;
  int i;
  
  int len = strlen(name);
  


  wname = Calloc(len+1, wchar_t);


  mbstowcs(wname, name, len);

  for (i =0; i < data_header->n_name_type_value; i++){
    if (wcscmp(wname, data_header->name_type_value[i].name.value) == 0){
      returnvalue = &(data_header->name_type_value[i]);
      break;
    }
  }
  
  if (returnvalue == 0){
    for (i =0; i < data_header->n_parent_headers; i++){
      returnvalue = find_nvt((generic_data_header *)(data_header->parent_headers)[i],name);
      if (returnvalue !=0){
	break;
      }
    }
  }
  
  Free(wname);
  return returnvalue;
}



int read_generic_file_header(generic_file_header* file_header, FILE *instream){

  if (!fread_be_uchar(&(file_header->magic_number),1,instream)){
    return 0;
  }
  if (file_header->magic_number != 59){
    return 0;
  }
  
  if (!fread_be_uchar(&(file_header->version),1,instream)){
    return 0;
  }

  if (file_header->version != 1){
    return 0;
  }
  
  if (!fread_be_int32(&(file_header->n_data_groups),1,instream) ||
      !fread_be_uint32(&(file_header->first_group_file_pos),1,instream)){
    return 0;
  }

  return 1;
}





int read_generic_data_header(generic_data_header *data_header, FILE *instream){
  
  int i;
  generic_data_header *temp_header;
  

  if (!fread_ASTRING(&(data_header->data_type_id), instream) ||
      !fread_ASTRING(&(data_header->unique_file_id), instream) ||
      !fread_AWSTRING(&(data_header->Date_time), instream) ||
      !fread_AWSTRING(&(data_header->locale),instream)){
    return 0;
  }

  if (!fread_be_int32(&(data_header->n_name_type_value),1,instream)){
    return 0;
  }
  
  data_header->name_type_value = Calloc(data_header->n_name_type_value, nvt_triplet);

  for (i =0; i < data_header->n_name_type_value; i++){
    if (!fread_nvt_triplet(&data_header->name_type_value[i],instream)){
      return 0;
    }
  }
  
  if (!fread_be_int32(&(data_header->n_parent_headers),1,instream)){
    return 0;
  }
  
  if (data_header->n_parent_headers > 0){
    data_header->parent_headers = Calloc(data_header->n_parent_headers,void *);
  } else {
    data_header->parent_headers = 0;
  }
  for (i =0; i < data_header->n_parent_headers; i++){
    temp_header = (generic_data_header *)Calloc(1,generic_data_header);
    if (!read_generic_data_header(temp_header,instream)){
      return 0;
    }
    data_header->parent_headers[i] = temp_header;
  }
  return 1;
}



int read_generic_data_group(generic_data_group *data_group, FILE *instream){
  
  if (!fread_be_uint32(&(data_group->file_position_nextgroup),1,instream) ||
      !fread_be_uint32(&(data_group->file_position_first_data),1,instream) ||
      !fread_be_int32(&(data_group->n_data_sets),1,instream) ||
      !fread_AWSTRING(&(data_group->data_group_name), instream)){
    return 0;
  }
  return 1;

}



int read_generic_data_set(generic_data_set *data_set, FILE *instream){

  int i;

  if (!fread_be_uint32(&(data_set->file_pos_first),1,instream) ||
      !fread_be_uint32(&(data_set->file_pos_last),1,instream) ||
      !fread_AWSTRING(&(data_set->data_set_name), instream) ||
      !fread_be_int32(&(data_set->n_name_type_value),1,instream)){
    return 0;
  }
  
    
  data_set->name_type_value = Calloc(data_set->n_name_type_value, nvt_triplet);

  for (i =0; i < data_set->n_name_type_value; i++){
    if (!fread_nvt_triplet(&data_set->name_type_value[i],instream)){
      return 0;
    }
  }

  if (!fread_be_uint32(&(data_set->ncols),1,instream)){
    return 0;
  }
  
  data_set->col_name_type_value = Calloc(data_set->ncols,col_nvts_triplet);

  for (i =0; i < data_set->ncols; i++){
    if (!fread_nvts_triplet(&data_set->col_name_type_value[i], instream)){
      return 0;
    }
  }

  if (!fread_be_uint32(&(data_set->nrows),1,instream)){
    return 0;
  }

  data_set->Data = Calloc(data_set->ncols, void *);

  for (i=0; i < data_set->ncols; i++){
    switch(data_set->col_name_type_value[i].type){
    case 0: data_set->Data[i] = Calloc(data_set->nrows,char);
      break;
    case 1: data_set->Data[i] = Calloc(data_set->nrows,unsigned char);
      break;
    case 2: data_set->Data[i] = Calloc(data_set->nrows,short);
      break;
    case 3: data_set->Data[i] = Calloc(data_set->nrows,unsigned short);
      break;
    case 4: data_set->Data[i] = Calloc(data_set->nrows,int);
      break;
    case 5: data_set->Data[i] = Calloc(data_set->nrows,unsigned int);
      break;
    case 6: data_set->Data[i] = Calloc(data_set->nrows,float);
      break;
    case 7: data_set->Data[i] = Calloc(data_set->nrows,double);
      break;
    case 8: data_set->Data[i] = Calloc(data_set->nrows,ASTRING);
      break;
    case 9: data_set->Data[i] = Calloc(data_set->nrows,AWSTRING);
      break;
    }
    
  }
  return 1;
}


int read_generic_data_set_rows(generic_data_set *data_set, FILE *instream){

  int i,j;
  
  for (i=0; i < data_set->nrows; i++){
    for (j=0; j < data_set->ncols; j++){
      switch(data_set->col_name_type_value[j].type){
      case 0: 
	if (!fread_be_char(&((char *)data_set->Data[j])[i],1,instream)){
	  return 0;
	} 
	break;
      case 1: 
	if (!fread_be_uchar(&((unsigned char *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 2: 	
	if (!fread_be_int16(&((short *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 3:
 	if (!fread_be_uint16(&((unsigned short *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 4:
 	if (!fread_be_int32(&((int32_t *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 5: 	
	if (!fread_be_uint32(&((uint32_t *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 6: 	
	if (!fread_be_float32(&((float *)data_set->Data[j])[i],1,instream)){
	  return 0;
	} 
	break;
      case 7: 	
	if (!fread_be_double64(&((double *)data_set->Data[j])[i],1,instream)){
	  return 0;
	} 
	break;
      case 8: 	
	if (!fread_ASTRING(&((ASTRING *)data_set->Data[j])[i], instream)){
	  return 0;
	} 
	break;
      case 9: 	
	if (!fread_AWSTRING(&((AWSTRING *)data_set->Data[j])[i], instream)){
	  return 0;
	};
	break;
      }
    }
  }
  return 1;
}




/*****************************************************************************
 **
 **
 ** Functionality for reading a generic format file which has been gzipped
 **
 **
 *****************************************************************************/



static int gzread_ASTRING(ASTRING *destination, gzFile *instream){

  gzread_be_int32(&(destination->len),1,instream);
  if (destination->len > 0){
    destination->value = Calloc(destination->len+1,char);
    gzread_be_char(destination->value,destination->len,instream);
  } else {
    destination->value = 0;
  }
  return 1;
}



static int gzread_AWSTRING(AWSTRING *destination, gzFile *instream){

  uint16_t temp;   /* Affy file wchar_t are 16 bits, the platform may have  32 bit wchar_t (notatbly linux) */

  int i;

  gzread_be_int32(&(destination->len),1,instream);
  if ((destination->len) > 0){
    destination->value = Calloc(destination->len+1,wchar_t);
  
    for (i=0; i < destination->len; i++){
      gzread_be_uint16(&temp,1,instream);
      destination->value[i] = (wchar_t)temp;
    }
  } else {
    destination->value = 0;
  }
  
  return 1;
}


static int gzread_nvt_triplet(nvt_triplet *destination, gzFile *instream){

  if (!(gzread_AWSTRING(&(destination->name),instream)) ||
      !(gzread_ASTRING(&(destination->value),instream)) ||
      !(gzread_AWSTRING(&(destination->type),instream))){
    return 0;
  }
  return 1;
}



static int gzread_nvts_triplet(col_nvts_triplet *destination, gzFile *instream){

  if (!(gzread_AWSTRING(&(destination->name),instream)) ||
      !(gzread_be_uchar(&(destination->type), 1, instream)) ||
      !(gzread_be_int32(&(destination->size), 1, instream))){
    return 0;
  }
  return 1;
}


int gzread_generic_file_header(generic_file_header* file_header, gzFile *instream){

  if (!gzread_be_uchar(&(file_header->magic_number),1,instream)){
    return 0;
  }
  if (file_header->magic_number != 59){
    return 0;
  }
  
  if (!gzread_be_uchar(&(file_header->version),1,instream)){
    return 0;
  }

  if (file_header->version != 1){
    return 0;
  }
  
  if (!gzread_be_int32(&(file_header->n_data_groups),1,instream) ||
      !gzread_be_uint32(&(file_header->first_group_file_pos),1,instream)){
    return 0;
  }

  return 1;
}




int gzread_generic_data_header(generic_data_header *data_header, gzFile *instream){
  
  int i;

  if (!gzread_ASTRING(&(data_header->data_type_id), instream) ||
      !gzread_ASTRING(&(data_header->unique_file_id), instream) ||
      !gzread_AWSTRING(&(data_header->Date_time), instream) ||
      !gzread_AWSTRING(&(data_header->locale),instream)){
    return 0;
  }

  if (!gzread_be_int32(&(data_header->n_name_type_value),1,instream)){
    return 0;
  }
  
  data_header->name_type_value = Calloc(data_header->n_name_type_value, nvt_triplet);

  for (i =0; i < data_header->n_name_type_value; i++){
    if (!gzread_nvt_triplet(&data_header->name_type_value[i],instream)){
      return 0;
    }
  }
  
  if (!gzread_be_int32(&(data_header->n_parent_headers),1,instream)){
    return 0;
  }
  
  data_header->parent_headers = Calloc(data_header->n_parent_headers,void *);

  for (i =0; i < data_header->n_parent_headers; i++){
    data_header->parent_headers[i] = (generic_data_header *)Calloc(1,generic_data_header);
    if (!gzread_generic_data_header((generic_data_header *)data_header->parent_headers[i],instream)){
      return 0;
    }
  }
  return 1;
}





int gzread_generic_data_group(generic_data_group *data_group, gzFile *instream){
  
  if (!gzread_be_uint32(&(data_group->file_position_nextgroup),1,instream) ||
      !gzread_be_uint32(&(data_group->file_position_first_data),1,instream) ||
      !gzread_be_int32(&(data_group->n_data_sets),1,instream) ||
      !gzread_AWSTRING(&(data_group->data_group_name), instream)){
    return 0;
  }
  return 1;

}





int gzread_generic_data_set(generic_data_set *data_set, gzFile *instream){

  int i;

  if (!gzread_be_uint32(&(data_set->file_pos_first),1,instream) ||
      !gzread_be_uint32(&(data_set->file_pos_last),1,instream) ||
      !gzread_AWSTRING(&(data_set->data_set_name), instream) ||
      !gzread_be_int32(&(data_set->n_name_type_value),1,instream)){
    return 0;
  }
  
    
  data_set->name_type_value = Calloc(data_set->n_name_type_value, nvt_triplet);

  for (i =0; i < data_set->n_name_type_value; i++){
    if (!gzread_nvt_triplet(&data_set->name_type_value[i],instream)){
      return 0;
    }
  }

  if (!gzread_be_uint32(&(data_set->ncols),1,instream)){
    return 0;
  }
  
  data_set->col_name_type_value = Calloc(data_set->ncols,col_nvts_triplet);

  for (i =0; i < data_set->ncols; i++){
    if (!gzread_nvts_triplet(&data_set->col_name_type_value[i], instream)){
      return 0;
    }
  }

  if (!gzread_be_uint32(&(data_set->nrows),1,instream)){
    return 0;
  }

  data_set->Data = Calloc(data_set->ncols, void *);

  for (i=0; i < data_set->ncols; i++){
    switch(data_set->col_name_type_value[i].type){
    case 0: data_set->Data[i] = Calloc(data_set->nrows,char);
      break;
    case 1: data_set->Data[i] = Calloc(data_set->nrows,unsigned char);
      break;
    case 2: data_set->Data[i] = Calloc(data_set->nrows,short);
      break;
    case 3: data_set->Data[i] = Calloc(data_set->nrows,unsigned short);
      break;
    case 4: data_set->Data[i] = Calloc(data_set->nrows,int);
      break;
    case 5: data_set->Data[i] = Calloc(data_set->nrows,unsigned int);
      break;
    case 6: data_set->Data[i] = Calloc(data_set->nrows,float);
      break;
    case 7: data_set->Data[i] = Calloc(data_set->nrows,double);
      break;
    case 8: data_set->Data[i] = Calloc(data_set->nrows,ASTRING);
      break;
    case 9: data_set->Data[i] = Calloc(data_set->nrows,AWSTRING);
      break;
    }
    
  }
  return 1;
}




int gzread_generic_data_set_rows(generic_data_set *data_set, gzFile *instream){

  int i,j;
  
  for (i=0; i < data_set->nrows; i++){
    for (j=0; j < data_set->ncols; j++){
      switch(data_set->col_name_type_value[j].type){
      case 0: 
	if (!gzread_be_char(&((char *)data_set->Data[j])[i],1,instream)){
	  return 0;
	} 
	break;
      case 1: 
	if (!gzread_be_uchar(&((unsigned char *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 2: 	
	if (!gzread_be_int16(&((short *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 3:
 	if (!gzread_be_uint16(&((unsigned short *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 4:
 	if (!gzread_be_int32(&((int32_t *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 5: 	
	if (!gzread_be_uint32(&((uint32_t *)data_set->Data[j])[i],1,instream)){
	  return 0;
	}  
	break;
      case 6: 	
	if (!gzread_be_float32(&((float *)data_set->Data[j])[i],1,instream)){
	  return 0;
	} 
	break;
      case 7: 	
	if (!gzread_be_double64(&((double *)data_set->Data[j])[i],1,instream)){
	  return 0;
	} 
	break;
      case 8: 	
	if (!gzread_ASTRING(&((ASTRING *)data_set->Data[j])[i], instream)){
	  return 0;
	} 
	break;
      case 9: 	
	if (!gzread_AWSTRING(&((AWSTRING *)data_set->Data[j])[i], instream)){
	  return 0;
	};
	break;
      }
    }
  }
  return 1;
}






/*****************************************************************************
 **
 ** TESTING FUNCTIONS
 **
 **
 **
 **
 ** The following functions are for testing purposes only they print contents
 **  of the  generic format file to the screen
 **
 ******************************************************************************/


static void print_file_header(generic_file_header header){
  Rprintf("%d\n",header.magic_number);
  Rprintf("%d\n",header.version);
  Rprintf("%d\n",header.n_data_groups);
  Rprintf("%d\n",header.first_group_file_pos);
}


static void print_ASTRING(ASTRING string){ 
  if (string.len > 0){
    Rprintf("%s",string.value);
  }
}


static void print_AWSTRING(AWSTRING string){
  if (string.len > 0){
    char *temp = Calloc(string.len+1,char);
    wcstombs(temp, string.value, string.len);
    
    Rprintf("%s",temp);
    
    
    Free(temp);
  }
}

static void print_decode_nvt_triplet(nvt_triplet triplet){
  
  wchar_t *temp;
  char *temp2;
  //  char Buffer[10000];
  int size;

  int temp32;
  float tempfloat;


  //  Rprintf("Size is %d\n",triplet.value.len); 
  if (!wcscmp(triplet.type.value,L"text/x-calvin-float")){
    Rprintf("Its a float  value is %f\n",decode_float32(triplet.value));

    Rprintf("Now Trying it again. But using exposed function\n");
    decode_MIME_value(triplet, determine_MIMETYPE(triplet),&tempfloat,&size);
    Rprintf("Its a float  value is %f\n",temp32);
  }
    
  if (!wcscmp(triplet.type.value,L"text/ascii")){
    temp2 = decode_ASCII(triplet.value);
    Rprintf("Its a Ascii String  value is %s\n",temp2);
    Free(temp2);

    Rprintf("Now Trying it again. But using exposed function\n");
    temp2 = decode_MIME_value(triplet, determine_MIMETYPE(triplet),temp2,&size);
    Rprintf("Its a Ascii String  value is %s with size %d\n",temp2, size);
    Free(temp2);
  }
  
  if (!wcscmp(triplet.type.value,L"text/plain")){
    temp = decode_TEXT(triplet.value);
    temp2 = Calloc(triplet.value.len/2 +1, char);
    wcstombs(temp2,temp,triplet.value.len/2 + 1);
    Rprintf("Text/plain String is %s\n",temp2);
    Free(temp);
    Free(temp2);

    Rprintf("Now Trying it again. But using exposed function\n");
    
    temp = (wchar_t *)decode_MIME_value(triplet, determine_MIMETYPE(triplet),temp,&size);
    temp2 = Calloc(size +1, char);
    wcstombs(temp2,temp,size);
    Rprintf("Its a Text/plain string value is %s with size %d\n",temp2, size);
    Free(temp2);
    Free(temp);
  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-integer-32")){
    Rprintf("Its a int32_t  value is %d\n",decode_INT32_t(triplet.value));

    Rprintf("Now Trying it again. But using exposed function\n");
    
    decode_MIME_value(triplet, determine_MIMETYPE(triplet),&temp32,&size);
    Rprintf("Its a int32_t  value is %d\n",temp32);

  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-integer-16")){
    Rprintf("Its a int16_t  value is %d\n",decode_INT16_t(triplet.value));
  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-unsigned-integer-32")){
    Rprintf("Its a uint32_t  value is %d\n",decode_UINT32_t(triplet.value));
  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-unsigned-integer-16")){
    Rprintf("Its a uint16_t  value is %d\n",decode_UINT16_t(triplet.value));
  }

  if (!wcscmp(triplet.type.value,L"text/x-calvin-integer-8")){
    Rprintf("Its a int8_t  value is %d\n",decode_UINT8_t(triplet.value));
  }
  if (!wcscmp(triplet.type.value,L"text/x-calvin-unsigned-integer-8")){
    Rprintf("Its a uint8_t  value is %d\n",decode_UINT8_t(triplet.value));
  }
	
  




}


static void print_nvt_triplet(nvt_triplet triplet){

  print_AWSTRING(triplet.name);
  Rprintf("  ");
  // print_ASTRING(triplet.value);
  //Rprintf("  ");
  print_AWSTRING(triplet.type);
  //Rprintf("\n"); 
  print_decode_nvt_triplet(triplet);
}

static void print_col_nvts_triplet(col_nvts_triplet triplet){

  print_AWSTRING(triplet.name);
  Rprintf("  %d   %d", triplet.type, triplet.size);
  Rprintf("\n");
}

static void print_generic_header(generic_data_header header){

  int i;

  print_ASTRING(header.data_type_id);
  Rprintf("\n");
  print_ASTRING(header.unique_file_id);
  Rprintf("\n");
  print_AWSTRING(header.Date_time);
  Rprintf("\n");
  print_AWSTRING(header.locale);
  Rprintf("\n");
  Rprintf("%d\n", header.n_name_type_value);

  for (i=0; i < header.n_name_type_value; i++){
    print_nvt_triplet(header.name_type_value[i]);
   
  }

  Rprintf("%d\n",header.n_parent_headers);
  if (header.n_parent_headers > 0){
    Rprintf("Printing Parental Headers\n");
    for (i =0; i < header.n_parent_headers; i++){
      print_generic_header(*(generic_data_header *)header.parent_headers[i]);
    }
  }
}


static void print_generic_data_group(generic_data_group data_group){
  
  Rprintf("%d\n",data_group.file_position_nextgroup);
  Rprintf("%d\n",data_group.file_position_first_data);
  Rprintf("%d\n",data_group.n_data_sets);
  print_AWSTRING(data_group.data_group_name);
  Rprintf("\n");
}


static void print_generic_data_set(generic_data_set data_set){
  int i;

  Rprintf("%d\n%d\n",data_set.file_pos_first,data_set.file_pos_last);

  print_AWSTRING(data_set.data_set_name);
  Rprintf("\n");
  printf("%d\n",data_set.n_name_type_value);

  for (i=0; i < data_set.n_name_type_value; i++){
    print_nvt_triplet(data_set.name_type_value[i]);
  }
  
  printf("%d\n",data_set.ncols);
  
  for (i=0; i < data_set.ncols; i++){
    print_col_nvts_triplet(data_set.col_name_type_value[i]);
  }
  Rprintf("%d\n",data_set.nrows);
}



SEXP Read_Generic(SEXP filename){

  int i,j;

  SEXP return_value = R_NilValue;

  FILE *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;

  const char *cur_file_name = CHAR(VECTOR_ELT(filename,0));

  /* Pass through all the header information */
  
  if ((infile = fopen(cur_file_name, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",cur_file_name);
      return 0;
    }
  

  
  read_generic_file_header(&my_header, infile);
  read_generic_data_header(&my_data_header, infile);
  read_generic_data_group(&my_data_group,infile);
  // read_generic_data_set(&my_data_set,infile); 
  //read_generic_data_set_rows(&my_data_set,infile); 
  
  print_file_header(my_header);
  print_generic_header(my_data_header);
  print_generic_data_group(my_data_group);
  for (j=0; j < my_data_group.n_data_sets; j++){
    read_generic_data_set(&my_data_set,infile); 
    print_generic_data_set(my_data_set);
    read_generic_data_set_rows(&my_data_set,infile); 
    for (i =0; i < 1  ; i++){
      //printf("%f\n",((float *)my_data_set.Data[0])[i]);
    }
    // Free_generic_data_set(&my_data_set);
    fseek(infile, my_data_set.file_pos_last, SEEK_SET);
    Free_generic_data_set(&my_data_set);
  }

  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);


  return return_value;

}


SEXP gzRead_Generic(SEXP filename){

  int i,j;

  SEXP return_value = R_NilValue;

  gzFile *infile;

  generic_file_header my_header;
  generic_data_header my_data_header;
  generic_data_group my_data_group;

  generic_data_set my_data_set;

  const char *cur_file_name = CHAR(VECTOR_ELT(filename,0));

  /* Pass through all the header information */
  
  if ((infile = gzopen(cur_file_name, "rb")) == NULL)
    {
      error("Unable to open the file %s\n",cur_file_name);
      return 0;
    }
  

  
  gzread_generic_file_header(&my_header, infile);
  gzread_generic_data_header(&my_data_header, infile);
  gzread_generic_data_group(&my_data_group,infile);
  // read_generic_data_set(&my_data_set,infile); 
  //read_generic_data_set_rows(&my_data_set,infile); 
  
  print_file_header(my_header);
  print_generic_header(my_data_header);
  print_generic_data_group(my_data_group);
  for (j=0; j < my_data_group.n_data_sets; j++){
    gzread_generic_data_set(&my_data_set,infile); 
    print_generic_data_set(my_data_set);
    gzread_generic_data_set_rows(&my_data_set,infile); 
    for (i =0; i < 1  ; i++){
      //printf("%f\n",((float *)my_data_set.Data[0])[i]);
    }
    // Free_generic_data_set(&my_data_set);
    gzseek(infile, my_data_set.file_pos_last, SEEK_SET);
    Free_generic_data_set(&my_data_set);
  }

  Free_generic_data_header(&my_data_header);
  Free_generic_data_group(&my_data_group);


  return return_value;

}
