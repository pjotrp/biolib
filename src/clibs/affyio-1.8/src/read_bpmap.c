/****************************************************************
 **
 ** File: read_bpmap.c
 **
 ** Implementation by: B. M. Bolstad
 **
 ** Copyright (C) B. M. Bolstad 2006-2007
 **
 ** A parser designed to read bpmap files into an R List structure
 **
 ** History
 ** Mar 11, 2006 - Initial version
 ** Mar 12, 2006 - add additional support for versions 2 and 3
 ** May 31, 2006 - Fix some compiler warnings
 ** June 12, 2006 - fix naming vector length issue.
 ** June 12, 2007 - much wailing and grinding of teeth, but finally a fix for reading version number right.
 ** Aug 25, 2007 - Move file reading functions to centralized location
 ** Mar 14, 2008 - Fix reading of version number for big endian platforms
 **
 *******************************************************************/

#include <R.h>
#include <Rdefines.h>

#include "stdlib.h"
#include "stdio.h"

#include "fread_functions.h"



/****************************************************************
 **
 **
 **
 **
 ** Note BPMAP files are stored in big endian format
 **
 *******************************************************************/



/*************************************************************************
 **
 ** Code for reading from the big endian binary files, doing bit flipping if
 ** necessary (on little-endian machines)
 **
 **
 ************************************************************************/



static void swap_float_4(float *tnf4)              /* 4 byte floating point numbers */
{
  int tni = (int)(*tnf4);
  
  tni=(((tni>>24)&0xff) | ((tni&0xff)<<24) |
       ((tni>>8)&0xff00) | ((tni&0xff00)<<8));

  *tnf4 = (float)tni; 

}





static SEXP ReadBPMAPHeader(FILE *infile){
 
  
  SEXP Header;
  SEXP tmpSXP;


  char *Magicnumber = R_alloc(8,sizeof(char));
  float version_number = 0.0;
  int version_number_int;
  unsigned int unsigned_version_number_int;


  unsigned int n_seq;
  static double new_version_number;



  fread_be_char(Magicnumber,8,infile);

  if (strncmp(Magicnumber,"PHT7",4) !=0){
    error("Based on the magic number which was %s, this does not appear to be a BPMAP file",Magicnumber);
  }


  /* version number is a little bit funky 
     need to do some funny things to coax it
     into the right format
  */

 
  /* cast to integer, swap bytes, cast to float */ 
  /* fread_be_float32(&version_number,1,infile); */
  fread_float32(&version_number,1,infile);
  swap_float_4(&version_number);

  new_version_number = (double)version_number;
  /*  // Rprintf("A %f\n",version_number);*/ 

  if ((version_number <=0.5) || (version_number > 3.5)){
    /* //  Rprintf("Rereading\n"); */
    fseek(infile,-sizeof(float),SEEK_CUR);
    fread_be_uint32(&unsigned_version_number_int,1,infile);
    memcpy(&version_number,&unsigned_version_number_int, sizeof(float));
    new_version_number = (double)version_number;
  }

  fread_be_uint32(&n_seq,1,infile);
  
  PROTECT(Header=allocVector(VECSXP,3));
  
  PROTECT(tmpSXP=allocVector(STRSXP,1));
  SET_STRING_ELT(tmpSXP,0,mkChar(Magicnumber));
  SET_VECTOR_ELT(Header,0,tmpSXP);
  UNPROTECT(1);
  

  PROTECT(tmpSXP=allocVector(REALSXP,1));
  REAL(tmpSXP)[0] = (double)new_version_number;
  SET_VECTOR_ELT(Header,1,tmpSXP);
  UNPROTECT(1);

  
  PROTECT(tmpSXP=allocVector(INTSXP,1));
  INTEGER(tmpSXP)[0] = (int)n_seq;
  SET_VECTOR_ELT(Header,2,tmpSXP);
  UNPROTECT(1);

  PROTECT(tmpSXP=allocVector(STRSXP,3));
  SET_STRING_ELT(tmpSXP,0,mkChar("magic.number"));
  SET_STRING_ELT(tmpSXP,1,mkChar("version"));
  SET_STRING_ELT(tmpSXP,2,mkChar("n.seq"));
  setAttrib(Header,R_NamesSymbol,tmpSXP);
  UNPROTECT(2);
  
  /* Rprintf("D %f %f\n",version_number,new_version_number);  */
  return Header;
    
}



static SEXP ReadBPMAPSeqDescription(FILE *infile, float version, int nseq){


  SEXP SequenceDescriptionList;

  SEXP CurSequenceDescription = R_NilValue;
  SEXP tmpSXP,tmpSXP2;
    


  int i,j;

  unsigned int seq_name_length;

  char *seq_name;
  
  unsigned int probe_mapping_type;
  unsigned int seq_file_offset;
  
  unsigned int n_probes;
  
  unsigned int group_name_length;
  char *group_name;
  
  unsigned int version_number_length;
  char *version_number;

  unsigned int number_parameters;

  unsigned int param_length;
  char *param_name;

  /* Rprintf("%f %d\n",version,nseq); */

  PROTECT(SequenceDescriptionList=allocVector(VECSXP,(int)nseq));

  for (i=0; i < nseq; i++){
    fread_be_uint32(&seq_name_length,1,infile);
    seq_name = (char *)Calloc(seq_name_length+1,char);
    fread_be_char(seq_name,seq_name_length,infile);
    
 

    if (version == 3.00){
      PROTECT(CurSequenceDescription=allocVector(VECSXP,8)); 
      PROTECT(tmpSXP=allocVector(STRSXP,7));
      SET_STRING_ELT(tmpSXP,0,mkChar("Name"));
      SET_STRING_ELT(tmpSXP,1,mkChar("ProbeMappingType"));
      SET_STRING_ELT(tmpSXP,2,mkChar("SequenceFileOffset"));
      SET_STRING_ELT(tmpSXP,3,mkChar("n.probepairs"));
      SET_STRING_ELT(tmpSXP,4,mkChar("GroupName"));
      SET_STRING_ELT(tmpSXP,5,mkChar("VersionNumber"));
      SET_STRING_ELT(tmpSXP,6,mkChar("NumberOfParameters"));
      SET_STRING_ELT(tmpSXP,7,mkChar("Parameters"));
      setAttrib(CurSequenceDescription,R_NamesSymbol,tmpSXP);
      UNPROTECT(1);
    } else if (version == 2.00){
      PROTECT(CurSequenceDescription=allocVector(VECSXP,6));
      PROTECT(tmpSXP=allocVector(STRSXP,6));
      SET_STRING_ELT(tmpSXP,0,mkChar("Name")); 
      SET_STRING_ELT(tmpSXP,1,mkChar("n.probepairs"));
      SET_STRING_ELT(tmpSXP,2,mkChar("GroupName"));
      SET_STRING_ELT(tmpSXP,3,mkChar("VersionNumber"));
      SET_STRING_ELT(tmpSXP,4,mkChar("NumberOfParameters"));
      SET_STRING_ELT(tmpSXP,5,mkChar("Parameters"));
      setAttrib(CurSequenceDescription,R_NamesSymbol,tmpSXP);
      UNPROTECT(1);
    } else if (version == 1.00){
      PROTECT(CurSequenceDescription=allocVector(VECSXP,2));
      PROTECT(tmpSXP=allocVector(STRSXP,2));
      SET_STRING_ELT(tmpSXP,0,mkChar("Name"));
      SET_STRING_ELT(tmpSXP,1,mkChar("n.probepairs"));
      setAttrib(CurSequenceDescription,R_NamesSymbol,tmpSXP);
      UNPROTECT(1);

    }
      
    PROTECT(tmpSXP=allocVector(STRSXP,1));
    SET_STRING_ELT(tmpSXP,0,mkChar(seq_name));
    SET_VECTOR_ELT(CurSequenceDescription,0,tmpSXP);
    UNPROTECT(1);
    Free(seq_name);

    
    if (version == 1.0){
      fread_be_uint32(&n_probes,1,infile);
      PROTECT(tmpSXP=allocVector(INTSXP,1));
      INTEGER(tmpSXP)[0] = n_probes;
      SET_VECTOR_ELT(CurSequenceDescription,1,tmpSXP);
      UNPROTECT(1);
    } else if (version ==2.0){
      fread_be_uint32(&n_probes,1,infile);
      PROTECT(tmpSXP=allocVector(INTSXP,1));
      INTEGER(tmpSXP)[0] = n_probes;
      SET_VECTOR_ELT(CurSequenceDescription,1,tmpSXP);
      UNPROTECT(1);
      
      
      

      fread_be_uint32(&group_name_length,1,infile);
      group_name = (char *)Calloc(group_name_length+1,char);
      fread_be_char(group_name,group_name_length,infile);
      
      PROTECT(tmpSXP=allocVector(STRSXP,1));
      SET_STRING_ELT(tmpSXP,0,mkChar(group_name));
      SET_VECTOR_ELT(CurSequenceDescription,2,tmpSXP);
      UNPROTECT(1);
      Free(group_name);
      

      fread_be_uint32(&version_number_length,1,infile);
      version_number = (char *)Calloc(version_number_length+1,char);
      fread_be_char(version_number,version_number_length,infile);
      
      PROTECT(tmpSXP=allocVector(STRSXP,1));
      SET_STRING_ELT(tmpSXP,0,mkChar(version_number));
      SET_VECTOR_ELT(CurSequenceDescription,3,tmpSXP);
      UNPROTECT(1);
      Free(version_number);


      fread_be_uint32(&number_parameters,1,infile);
      PROTECT(tmpSXP=allocVector(INTSXP,1));
      INTEGER(tmpSXP)[0] = number_parameters;
      SET_VECTOR_ELT(CurSequenceDescription,4,tmpSXP);
      UNPROTECT(1);

      PROTECT(tmpSXP=allocVector(VECSXP,number_parameters));
      

      for (j=0; j < number_parameters; j++){
	PROTECT(tmpSXP2 = allocVector(STRSXP,2));
	fread_be_uint32(&param_length,1,infile);
	param_name = (char *)Calloc(param_length+1,char);
	fread_be_char(param_name,param_length,infile);
	SET_STRING_ELT(tmpSXP2,0,mkChar(param_name));
	Free(param_name);
	fread_be_uint32(&param_length,1,infile);
	param_name = (char *)Calloc(param_length+1,char);
	fread_be_char(param_name,param_length,infile);
	SET_STRING_ELT(tmpSXP2,1,mkChar(param_name));
	Free(param_name);
		
	SET_VECTOR_ELT(tmpSXP,j,tmpSXP2);
	UNPROTECT(1);
      }
      SET_VECTOR_ELT(CurSequenceDescription,5,tmpSXP);
      UNPROTECT(1);     
   


    } else if (version ==3.0){  
      fread_be_uint32(&probe_mapping_type,1,infile);
      PROTECT(tmpSXP=allocVector(INTSXP,1));
      INTEGER(tmpSXP)[0] = probe_mapping_type;
      SET_VECTOR_ELT(CurSequenceDescription,1,tmpSXP);
      UNPROTECT(1);

      fread_be_uint32(&seq_file_offset,1,infile);
      PROTECT(tmpSXP=allocVector(INTSXP,1));
      INTEGER(tmpSXP)[0] = seq_file_offset;
      SET_VECTOR_ELT(CurSequenceDescription,2,tmpSXP);
      UNPROTECT(1);
      
      fread_be_uint32(&n_probes,1,infile);
      PROTECT(tmpSXP=allocVector(INTSXP,1));
      INTEGER(tmpSXP)[0] = n_probes;
      SET_VECTOR_ELT(CurSequenceDescription,3,tmpSXP);
      UNPROTECT(1);

      fread_be_uint32(&group_name_length,1,infile);
      group_name = (char *)Calloc(group_name_length+1,char);
      fread_be_char(group_name,group_name_length,infile);
      
      PROTECT(tmpSXP=allocVector(STRSXP,1));
      SET_STRING_ELT(tmpSXP,0,mkChar(group_name));
      SET_VECTOR_ELT(CurSequenceDescription,4,tmpSXP);
      UNPROTECT(1);
      Free(group_name);
      
      fread_be_uint32(&version_number_length,1,infile);
      version_number = (char *)Calloc(version_number_length+1,char);
      fread_be_char(version_number,version_number_length,infile);
      
      PROTECT(tmpSXP=allocVector(STRSXP,1));
      SET_STRING_ELT(tmpSXP,0,mkChar(version_number));
      SET_VECTOR_ELT(CurSequenceDescription,5,tmpSXP);
      UNPROTECT(1);
      Free(version_number);

      fread_be_uint32(&number_parameters,1,infile);
      PROTECT(tmpSXP=allocVector(INTSXP,1));
      INTEGER(tmpSXP)[0] = number_parameters;
      SET_VECTOR_ELT(CurSequenceDescription,6,tmpSXP);
      UNPROTECT(1);



      PROTECT(tmpSXP=allocVector(VECSXP,number_parameters));
      

      for (j=0; j < number_parameters; j++){
	PROTECT(tmpSXP2 = allocVector(STRSXP,2));
	fread_be_uint32(&param_length,1,infile);
	param_name = (char *)Calloc(param_length+1,char);
	fread_be_char(param_name,param_length,infile);
	SET_STRING_ELT(tmpSXP2,0,mkChar(param_name));
	Free(param_name);
	fread_be_uint32(&param_length,1,infile);
	param_name = (char *)Calloc(param_length+1,char);
	fread_be_char(param_name,param_length,infile);
	SET_STRING_ELT(tmpSXP2,1,mkChar(param_name));
	Free(param_name);
		
	SET_VECTOR_ELT(tmpSXP,j,tmpSXP2);
	UNPROTECT(1);
      }
      SET_VECTOR_ELT(CurSequenceDescription,7,tmpSXP);
      UNPROTECT(1);     
    }
    
    SET_VECTOR_ELT(SequenceDescriptionList,i,CurSequenceDescription);
    UNPROTECT(1);
    
  }
  
  UNPROTECT(1);
  return SequenceDescriptionList;

}



static void packedSeqTobaseStr(unsigned char probeseq[7], char *dest){

  unsigned char currentchar;
  
  unsigned char firsttwobits;
  unsigned char secondtwobits;
  unsigned char thirdtwobits;
  unsigned char fourthtwobits;

  int i;


  /* Rprintf("\n\n\n\n\n"); */

  
  for (i =0; i < 6;i++){
    currentchar = probeseq[i];
    
    /* extract first two bits */
    firsttwobits = (currentchar & 192);
    secondtwobits = (currentchar & 48);
    thirdtwobits  = (currentchar & 12); 
    fourthtwobits  = (currentchar & 3);


    
    firsttwobits = firsttwobits >> 6;
    secondtwobits = secondtwobits >> 4;
    thirdtwobits =  thirdtwobits >> 2;
    
    /*    Rprintf("%x %x %x %x\n",firsttwobits,secondtwobits,thirdtwobits,fourthtwobits); */

    

    
    if (firsttwobits == 0){
      dest[4*i +0]='A';
    }
    if (firsttwobits == 1){
      dest[4*i +0]='C';
    }
    if (firsttwobits == 2){
      dest[4*i +0]='G';
    }
    if (firsttwobits == 3){
      dest[4*i +0]='T';
    }
  
    if (secondtwobits == 0){
      dest[4*i +1]='A';
    }
    if (secondtwobits == 1){
      dest[4*i +1]='C';
    }
    if (secondtwobits == 2){
      dest[4*i +1]='G';
    }
    if (secondtwobits == 3){
      dest[4*i +1]='T';
    }

    if (thirdtwobits == 0){
      dest[4*i +2]='A';
    }
    if (thirdtwobits == 1){
      dest[4*i +2]='C';
    }
    if (thirdtwobits == 2){
      dest[4*i +2]='G';
    }
    if (thirdtwobits == 3){
      dest[4*i +2]='T';
    }
    
    if (fourthtwobits == 0){
      dest[4*i +3]='A';
    }
    if (fourthtwobits == 1){
      dest[4*i +3]='C';
    }
    if (fourthtwobits == 2){
      dest[4*i +3]='G';
    }
    if (fourthtwobits == 3){
      dest[4*i +3]='T';
    }

    /* Rprintf("%c%c%c%c\n",dest[4*i],dest[4*i +1],dest[4*i +2], dest[4*i +3]); */
  }

  currentchar = probeseq[6];
  
  /* extract first two bits */
    
  firsttwobits = (currentchar & 192);
  firsttwobits = firsttwobits >> 6;
  if (firsttwobits == 0){
    dest[24]='A';
  }
  if (firsttwobits == 1){
    dest[24]='C';
  }
  if (firsttwobits == 2){
    dest[24]='G';
  }
  if (firsttwobits == 3){
    dest[24]='T';
  }
}








static SEXP readBPMAPSeqIdPositionInfo(FILE *infile, float version, int nseq, SEXP seqDesc){


  SEXP SeqIdPositionInfoList;
  SEXP curSeqIdPositionInfo;
  SEXP PositionInfo= R_NilValue;
  SEXP PositionInfoRowNames;


  SEXP tmpSEXP;

  SEXP xPM= R_NilValue,yPM= R_NilValue,xMM= R_NilValue,yMM= R_NilValue;
  SEXP PMprobeLength= R_NilValue;
  SEXP probeSeqString= R_NilValue;
  SEXP MatchScore= R_NilValue;
  SEXP PMposition= R_NilValue;
  SEXP Strand= R_NilValue;

  char buf[10];

  char *dest;


  int nprobes=0;
  int probe_mapping_type=0;
  int i,j;


  unsigned int SeqId;

  unsigned int x;
  unsigned int y;
  
  unsigned int x_mm;
  unsigned int y_mm;

  unsigned char probelength;

  unsigned char probeseq[7];

  float matchScore;
  int matchScore_int;

  unsigned int positionPM;
  unsigned char strand;

  
  PROTECT(SeqIdPositionInfoList = allocVector(VECSXP,nseq));
  
  for (i =0; i < nseq; i++){
    fread_be_uint32(&SeqId,1,infile);
    /*Rprintf("Seq id:%u\n",SeqId);*/
    
    PROTECT(curSeqIdPositionInfo = allocVector(VECSXP,2));


    PROTECT(tmpSEXP=allocVector(INTSXP,1));
    INTEGER(tmpSEXP)[0] = (int)SeqId;    
    SET_VECTOR_ELT(curSeqIdPositionInfo,0,tmpSEXP);
    UNPROTECT(1);

    
    PROTECT(tmpSEXP=allocVector(STRSXP,2));
    SET_STRING_ELT(tmpSEXP,0,mkChar("Header"));
    SET_STRING_ELT(tmpSEXP,1,mkChar("PositionInformation"));
    setAttrib(curSeqIdPositionInfo,R_NamesSymbol,tmpSEXP);
    UNPROTECT(1);
      


    if ((version == 1.0) || (version == 2.0)){
      nprobes = INTEGER(VECTOR_ELT(VECTOR_ELT(seqDesc,i),1))[0];
      /* Rprintf("nprobes: %d\n",nprobes); */
      probe_mapping_type = 0; /* PM/MM tiling */
      
      PROTECT(PositionInfo = allocVector(VECSXP,9));
      PROTECT(xPM = allocVector(INTSXP,nprobes));
      PROTECT(yPM = allocVector(INTSXP,nprobes));
      PROTECT(xMM = allocVector(INTSXP,nprobes));
      PROTECT(yMM = allocVector(INTSXP,nprobes));
      PROTECT(PMprobeLength = allocVector(INTSXP,nprobes));
      PROTECT(probeSeqString = allocVector(STRSXP,nprobes));
      PROTECT(MatchScore = allocVector(REALSXP,nprobes));
      PROTECT(PMposition = allocVector(INTSXP,nprobes));
      PROTECT(Strand = allocVector(STRSXP,nprobes));
      
      SET_VECTOR_ELT(PositionInfo,0,xPM);
      SET_VECTOR_ELT(PositionInfo,1,yPM);
      SET_VECTOR_ELT(PositionInfo,2,xMM);
      SET_VECTOR_ELT(PositionInfo,3,yMM);
      SET_VECTOR_ELT(PositionInfo,4,PMprobeLength);
      SET_VECTOR_ELT(PositionInfo,5,probeSeqString);
      SET_VECTOR_ELT(PositionInfo,6,MatchScore);
      SET_VECTOR_ELT(PositionInfo,7,PMposition);
      SET_VECTOR_ELT(PositionInfo,8,Strand);
      UNPROTECT(9);

      setAttrib(PositionInfo,R_ClassSymbol,mkString("data.frame"));

      PROTECT(PositionInfoRowNames = allocVector(STRSXP,nprobes));
      for (j=0; j < nprobes; j++){
	sprintf(buf, "%d", j+1);
	SET_STRING_ELT(PositionInfoRowNames,j,mkChar(buf));
      }
      setAttrib(PositionInfo, R_RowNamesSymbol, PositionInfoRowNames);
      UNPROTECT(1);

      PROTECT(tmpSEXP = allocVector(STRSXP,9));
      SET_STRING_ELT(tmpSEXP,0,mkChar("x"));
      SET_STRING_ELT(tmpSEXP,1,mkChar("y"));
      SET_STRING_ELT(tmpSEXP,2,mkChar("x.mm"));
      SET_STRING_ELT(tmpSEXP,3,mkChar("y.mm"));
      SET_STRING_ELT(tmpSEXP,4,mkChar("PMLength"));
      SET_STRING_ELT(tmpSEXP,5,mkChar("ProbeSeq"));
      SET_STRING_ELT(tmpSEXP,6,mkChar("MatchScore"));
      SET_STRING_ELT(tmpSEXP,7,mkChar("PMPosition"));
      SET_STRING_ELT(tmpSEXP,8,mkChar("TargetStrand"));

      setAttrib(PositionInfo,R_NamesSymbol,tmpSEXP);
      UNPROTECT(1);

    } else if (version == 3.0){
      nprobes = INTEGER(VECTOR_ELT(VECTOR_ELT(seqDesc,i),3))[0];
      probe_mapping_type = INTEGER(VECTOR_ELT(VECTOR_ELT(seqDesc,i),1))[0];


      if (probe_mapping_type == 0){
	PROTECT(PositionInfo = allocVector(VECSXP,9));
	PROTECT(xPM = allocVector(INTSXP,nprobes));
	PROTECT(yPM = allocVector(INTSXP,nprobes));
	PROTECT(xMM = allocVector(INTSXP,nprobes));
	PROTECT(yMM = allocVector(INTSXP,nprobes));
	PROTECT(PMprobeLength = allocVector(INTSXP,nprobes));
	PROTECT(probeSeqString = allocVector(STRSXP,nprobes));
	PROTECT(MatchScore = allocVector(REALSXP,nprobes));
	PROTECT(PMposition = allocVector(INTSXP,nprobes));
	PROTECT(Strand = allocVector(STRSXP,nprobes));
	
	SET_VECTOR_ELT(PositionInfo,0,xPM);
	SET_VECTOR_ELT(PositionInfo,1,yPM);
	SET_VECTOR_ELT(PositionInfo,2,xMM);
	SET_VECTOR_ELT(PositionInfo,3,yMM);
	SET_VECTOR_ELT(PositionInfo,4,PMprobeLength);
	SET_VECTOR_ELT(PositionInfo,5,probeSeqString);
	SET_VECTOR_ELT(PositionInfo,6,MatchScore);
	SET_VECTOR_ELT(PositionInfo,7,PMposition);
	SET_VECTOR_ELT(PositionInfo,8,Strand);
	UNPROTECT(9);

	setAttrib(PositionInfo,R_ClassSymbol,mkString("data.frame"));
	
	PROTECT(PositionInfoRowNames = allocVector(STRSXP,nprobes));
	for (j=0; j < nprobes; j++){
	  sprintf(buf, "%d", j+1);
	  SET_VECTOR_ELT(PositionInfoRowNames,j,mkChar(buf));
	}
	setAttrib(PositionInfo, R_RowNamesSymbol, PositionInfoRowNames);
	UNPROTECT(1);
	
	PROTECT(tmpSEXP = allocVector(STRSXP,9));
	SET_STRING_ELT(tmpSEXP,0,mkChar("x"));
	SET_STRING_ELT(tmpSEXP,1,mkChar("y"));
	SET_STRING_ELT(tmpSEXP,2,mkChar("x.mm"));
	SET_STRING_ELT(tmpSEXP,3,mkChar("y.mm"));
	SET_STRING_ELT(tmpSEXP,4,mkChar("PMLength"));
	SET_STRING_ELT(tmpSEXP,5,mkChar("ProbeSeq"));
	SET_STRING_ELT(tmpSEXP,6,mkChar("MatchScore"));
	SET_STRING_ELT(tmpSEXP,7,mkChar("PMPosition"));
	SET_STRING_ELT(tmpSEXP,8,mkChar("TargetStrand"));
	
	setAttrib(PositionInfo,R_NamesSymbol,tmpSEXP);
	UNPROTECT(1);
      } else {

	PROTECT(PositionInfo = allocVector(VECSXP,7));
	PROTECT(xPM = allocVector(INTSXP,nprobes));
	PROTECT(yPM = allocVector(INTSXP,nprobes));
	PROTECT(PMprobeLength = allocVector(INTSXP,nprobes));
	PROTECT(probeSeqString = allocVector(STRSXP,nprobes));
	PROTECT(MatchScore = allocVector(REALSXP,nprobes));
	PROTECT(PMposition = allocVector(INTSXP,nprobes));
	PROTECT(Strand = allocVector(STRSXP,nprobes));
	
	SET_VECTOR_ELT(PositionInfo,0,xPM);
	SET_VECTOR_ELT(PositionInfo,1,yPM);
	SET_VECTOR_ELT(PositionInfo,2,PMprobeLength);
	SET_VECTOR_ELT(PositionInfo,3,probeSeqString);
	SET_VECTOR_ELT(PositionInfo,4,MatchScore);
	SET_VECTOR_ELT(PositionInfo,5,PMposition);
	SET_VECTOR_ELT(PositionInfo,6,Strand);
	UNPROTECT(7);

	setAttrib(PositionInfo,R_ClassSymbol,mkString("data.frame"));
	
	PROTECT(PositionInfoRowNames = allocVector(STRSXP,nprobes));
	for (j=0; j < nprobes; j++){
	  sprintf(buf, "%d", j+1);
	  SET_STRING_ELT(PositionInfoRowNames,j,mkChar(buf));
	}
	setAttrib(PositionInfo, R_RowNamesSymbol, PositionInfoRowNames);
	UNPROTECT(1);
	
	PROTECT(tmpSEXP = allocVector(STRSXP,7));
	SET_STRING_ELT(tmpSEXP,0,mkChar("x"));
	SET_STRING_ELT(tmpSEXP,1,mkChar("y"));
	SET_STRING_ELT(tmpSEXP,2,mkChar("PMLength"));
	SET_STRING_ELT(tmpSEXP,3,mkChar("ProbeSeq"));
	SET_STRING_ELT(tmpSEXP,4,mkChar("MatchScore"));
	SET_STRING_ELT(tmpSEXP,5,mkChar("PMPosition"));
	SET_STRING_ELT(tmpSEXP,6,mkChar("TargetStrand"));
	
	setAttrib(PositionInfo,R_NamesSymbol,tmpSEXP);
	UNPROTECT(1);
      }


    }
    
    



    for (j=0; j < nprobes; j++){
      fread_be_uint32(&x,1,infile);
      fread_be_uint32(&y,1,infile);
      /* Rprintf("x y :%u %u\n",x,y); */

      if (probe_mapping_type == 0){
	fread_be_uint32(&x_mm,1,infile);
	fread_be_uint32(&y_mm,1,infile);
      }

      /* Rprintf("mm x y :%u %u\n",x_mm,y_mm); */
      
      INTEGER(xPM)[j] = x;
      INTEGER(yPM)[j] = y;

      if (probe_mapping_type == 0){
	INTEGER(xMM)[j] = x_mm;
	INTEGER(yMM)[j] = y_mm;
      }
      fread_be_uchar(&probelength,1,infile);
      /* Rprintf("probelength : %d\n",(int)probelength);*/
      
      INTEGER(PMprobeLength)[j] = probelength;
      

      fread_be_uchar(probeseq,7,infile);
      /* Rprintf("probeseq : %s\n",probeseq); */



      dest = (char *)Calloc(25+1,char);
      packedSeqTobaseStr(probeseq,dest);

      SET_STRING_ELT(probeSeqString,j,mkChar(dest));
      Free(dest);



      
      /* matchScore is treated same as version number in header */
#ifdef WORDS_BIGENDIAN
      /* swap, cast to integer, swap bytes and cast back to float */
      fread_be_float32(&matchScore,1,infile);
      swap_float_4(&matchScore);
      matchScore_int = (int)matchScore;
      
      
      matchScore_int=(((matchScore_int>>24)&0xff) | ((matchScore_int&0xff)<<24) |
		      ((matchScore_int>>8)&0xff00) | ((matchScore_int&0xff00)<<8));
      matchScore = (float)matchScore_int;
      
#else
      /* cast to integer, swap bytes, cast to float */ 
      fread_float32(&matchScore,1,infile);
      matchScore_int = (int)matchScore;
      matchScore_int=(((matchScore_int>>24)&0xff) | ((matchScore_int&0xff)<<24) |
		      ((matchScore_int>>8)&0xff00) | ((matchScore_int&0xff00)<<8));
      matchScore = (float)matchScore_int;
#endif
      /* Rprintf("matchScore : %f\n",matchScore); */
      
      REAL(MatchScore)[j] = matchScore;


      
      fread_be_uint32(&positionPM,1,infile);
      /* Rprintf("positionPM : %u\n",positionPM);*/
      INTEGER(PMposition)[j] = positionPM;
      
      
      fread_be_uchar(&strand,1,infile);
      /* Rprintf("strand: %d\n",(int)strand);*/

      if ((int)strand ==1){
	SET_STRING_ELT(Strand,j,mkChar("F"));
      } else {
	SET_STRING_ELT(Strand,j,mkChar("R"));
      }

    
    }

    SET_VECTOR_ELT(curSeqIdPositionInfo,1,PositionInfo);
    UNPROTECT(1);

    SET_VECTOR_ELT(SeqIdPositionInfoList,i,curSeqIdPositionInfo);
    UNPROTECT(1);
  }

  
  UNPROTECT(1);
  return SeqIdPositionInfoList;
    
}






SEXP ReadBPMAPFileIntoRList(SEXP filename){



  SEXP bpmapRlist;

  SEXP bpmapHeader;
  SEXP bpmapSeqDesc;

  SEXP tmpSXP;

  FILE *infile;
 

  int n_seq;
  float version;


  const char *cur_file_name;
  cur_file_name = CHAR(VECTOR_ELT(filename,0));
  


  if ((infile = fopen(cur_file_name, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
    }
  

      
  /*
    first element is header, second item is sequence descriptions
    third item is sequence header/position information
    
  */
  PROTECT(bpmapRlist  = allocVector(VECSXP,3));


  PROTECT(bpmapHeader = ReadBPMAPHeader(infile));
  SET_VECTOR_ELT(bpmapRlist,0,bpmapHeader);
  version = REAL(VECTOR_ELT(bpmapHeader,1))[0];
  n_seq = INTEGER(VECTOR_ELT(bpmapHeader,2))[0];
  UNPROTECT(1);
  
  /*  Rprintf("version nseq: %f %d\n", version, n_seq); */


  PROTECT(bpmapSeqDesc = ReadBPMAPSeqDescription(infile,version,n_seq));
  SET_VECTOR_ELT(bpmapRlist,1,bpmapSeqDesc);
  SET_VECTOR_ELT(bpmapRlist,2,readBPMAPSeqIdPositionInfo(infile,version,n_seq,bpmapSeqDesc));
  UNPROTECT(1);

  PROTECT(tmpSXP=allocVector(STRSXP,3));
  SET_STRING_ELT(tmpSXP,0,mkChar("Header"));
  SET_STRING_ELT(tmpSXP,1,mkChar("SequenceDescription"));
  SET_STRING_ELT(tmpSXP,2,mkChar("SeqHead.PosInfo"));
  setAttrib(bpmapRlist,R_NamesSymbol,tmpSXP);
  UNPROTECT(1);
  
  UNPROTECT(1);
  return bpmapRlist;


}

