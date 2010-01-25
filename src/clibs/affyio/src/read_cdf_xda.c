/****************************************************************
 **
 ** File: read_cdf_xda.c
 **
 ** Implementation by: B. M. Bolstad <bmb@bmbolstad.com>
 **
 ** A parser designed to read the binary format cdf files.
 ** Sometimes called the xda format.
 **
 ** Implemented based on documentation available from Affymetrix
 **
 ** Implementation begun 2005.
 **
 ** Modification Dates
 ** Feb 4 - Initial version
 ** Feb 5 - A bunch of hacks for SNP chips.
 ** Apr 20
 ** Aug 16, 2005 - Fix potential big endian bug
 ** Sep 22, 2005 - Fix some signed/unsigned bugs
 ** Dec 1, 2005 - Comment cleaning
 ** Feb 28, 2006 - replace C++ comments with ANSI comments for older compilers
 ** May 31, 2006 - fix some compiler warnings
 ** Aug 23, 2006 - fix a potential (but at current time non-existant) problem
 **                when there are 0 qcunits or 0 units
 ** Aug 25, 2007 - Move file reading functions to centralized location
 ** Oct 27, 2007 - When building a cdfenv set NON identified values to NA (mostly affects MM for PM only arrays)
 ** Nov 12, 2008 - Fix crash 
 ** Jan 15, 2008 - Fix VECTOR_ELT/STRING_ELT issues
 **
 ****************************************************************/

/** --- includes --- */
#include <R.h>
#include <Rdefines.h>

#include "stdlib.h"
#include "stdio.h"
#include "fread_functions.h"
#include <ctype.h>

/* #define READ_CDF_DEBUG */
						  /* #define READ_CDF_DEBUG_SNP */
#define READ_CDF_NOSNP



/************************************************************************
 **
 ** Structures for holding the CDF file information. Basically 
 ** header/general information that appears at the start of the CDF file
 **
 ************************************************************************/

typedef struct {
  int magicnumber;
  int version_number;
  unsigned short rows,cols;
  int n_units,n_qc_units;
  int len_ref_seq;
  int i;
  char *ref_seq;
} cdf_xda_header;


/****************************************************************************
 **
 ** The following two structures store QC units and QC unit probe information
 **
 **  QC information, repeated for each QC unit:
 ** Type - unsigned short
 ** Number of probes - integer
 **
 ** Probe information, repeated for each probe in the QC unit:
 ** X coordinate - unsigned short
 ** Y coordinate - unsigned short
 ** Probe length - unsigned char
 ** Perfect match flag - unsigned char
 ** Background probe flag - unsigned char
 **
 ****************************************************************************/
 

typedef struct{
  unsigned short x;
  unsigned short y;
  unsigned char probelength;
  unsigned char pmflag;
  unsigned char bgprobeflag;

} cdf_qc_probe;

typedef struct{
  unsigned short type;
  unsigned int n_probes;

  cdf_qc_probe *qc_probes;
  
} cdf_qc_unit;


/****************************************************************************
 **
 ** The following three structures store information for units (sometimes called
 ** probesets), blocks (of which there are one or more within a unit) and cells 
 ** sometimes called probe of which there are one or more within each block
 ** 
 **
 ** Unit information, repeated for each unit:
 **
 ** UnitType - unsigned short (1 - expression, 2 - genotyping, 3 - CustomSeq, 3 - tag)
 ** Direction - unsigned char
 ** Number of atoms - integer
 ** Number of blocks - integer (always 1 for expression units)
 ** Number of cells - integer
 ** Unit number (probe set number) - integer
 ** Number of cells per atom - unsigned char
 ** 
 **
 **
 ** Block information, repeated for each block in the unit:
 ** 
 ** Number of atoms - integer
 ** Number of cells - integer
 ** Number of cells per atom - unsigned char
 ** Direction - unsigned char
 ** The position of the first atom - integer
 ** <unused integer value> - integer
 ** The block name - char[64]
 **
 **
 ** 
 ** Cell information, repeated for each cell in the block:
 ** 
 ** Atom number - integer
 ** X coordinate - unsigned short
 ** Y coordinate - unsigned short
 ** Index position (relative to sequence for resequencing units, for expression and mapping units this value is just the atom number) - integer
 ** Base of probe at substitution position - char
 ** Base of target at interrogation position - char
 **
 **
 ****************************************************************************/
 

typedef struct{
  int atomnumber;
  unsigned short x;
  unsigned short y;
  int indexpos;
  char pbase;
  char tbase;
} cdf_unit_cell;


typedef struct{
  int natoms;
  int ncells;
  unsigned char ncellperatom;
  unsigned char direction;
  int firstatom;
  int unused;         /* in the docs this is called "unused" but by the looks of it it is actually the lastatom */
  char blockname[64];

  cdf_unit_cell  *unit_cells;

} cdf_unit_block;


typedef struct{
  unsigned short unittype;
  unsigned char direction;
  int natoms;
  int nblocks;
  int ncells;
  int unitnumber;
  unsigned char ncellperatom;

  cdf_unit_block *unit_block;
  
} cdf_unit;


/****************************************************************************
 **
 ** A data structure for holding CDF information read from a xda format cdf file
 **
 ** note that this structure reads in everything including things that might not
 ** be of any subsequent use.
 **
 ****************************************************************************/



typedef struct {
  
  cdf_xda_header header;  /* Header information */
  char **probesetnames;   /* Names of probesets */
  
  int *qc_start;          /* These are used for random access */
  int *units_start;
  
  cdf_qc_unit *qc_units;
  cdf_unit *units;


} cdf_xda;












/*************************************************************************
 **
 ** int read_cdf_qcunit(cdf_qc_unit *my_unit,int filelocation,FILE *instream)
 **
 ** cdf_qc_unit *my_unit - preallocated space to store qc unit information
 ** int filelocation - indexing/location information used to read information
 **                    from file
 ** FILE *instream - a pre-opened file to read from
 **
 ** reads a specificed qc_unit from the file. Allocates space for the cdf_qc_probes
 ** and also reads them in
 **
 ** 
 *************************************************************************/

int read_cdf_qcunit(cdf_qc_unit *my_unit,int filelocation,FILE *instream){
  
  int i;


  fseek(instream,filelocation,SEEK_SET);

  fread_uint16(&(my_unit->type),1,instream);
  fread_uint32(&(my_unit->n_probes),1,instream);


  my_unit->qc_probes = Calloc(my_unit->n_probes,cdf_qc_probe);

  for (i=0; i < my_unit->n_probes; i++){
    fread_uint16(&(my_unit->qc_probes[i].x),1,instream);
    fread_uint16(&(my_unit->qc_probes[i].y),1,instream);
    fread_uchar(&(my_unit->qc_probes[i].probelength),1,instream);
    fread_uchar(&(my_unit->qc_probes[i].pmflag),1,instream);
    fread_uchar(&(my_unit->qc_probes[i].bgprobeflag),1,instream);
    
     }
  return 1;
}

/*************************************************************************
 **
 ** int read_cdf_unit(cdf_unit *my_unit,int filelocation,FILE *instream)
 **
 ** cdf_qc_unit *my_unit - preallocated space to store unit (aka probeset) information
 ** int filelocation - indexing/location information used to read information
 **                    from file
 ** FILE *instream - a pre-opened file to read from
 **
 ** reads a specified probeset into the my_unit, including all blocks and all probes
 ** it is assumed that the unit itself is preallocated. Blocks and probes within
 ** the blocks are allocated by this function.
 ** 
 *************************************************************************/

int read_cdf_unit(cdf_unit *my_unit,int filelocation,FILE *instream){

  int i,j;

  fseek(instream,filelocation,SEEK_SET);

  fread_uint16(&(my_unit->unittype),1,instream);
  fread_uchar(&(my_unit->direction),1,instream);
  

  fread_int32(&(my_unit->natoms),1,instream);
  fread_int32(&(my_unit->nblocks),1,instream);
  fread_int32(&(my_unit->ncells),1,instream);
  fread_int32(&(my_unit->unitnumber),1,instream);
  fread_uchar(&(my_unit->ncellperatom),1,instream);

  my_unit->unit_block = Calloc(my_unit->nblocks,cdf_unit_block);

  for (i=0; i < my_unit->nblocks; i++){
    fread_int32(&(my_unit->unit_block[i].natoms),1,instream);
    fread_int32(&(my_unit->unit_block[i].ncells),1,instream);
    fread_uchar(&(my_unit->unit_block[i].ncellperatom),1,instream);
    fread_uchar(&(my_unit->unit_block[i].direction),1,instream);
    fread_int32(&(my_unit->unit_block[i].firstatom),1,instream);
    fread_int32(&(my_unit->unit_block[i].unused),1,instream);
    fread_char(my_unit->unit_block[i].blockname,64,instream); 

    my_unit->unit_block[i].unit_cells = Calloc(my_unit->unit_block[i].ncells,cdf_unit_cell);

    for (j=0; j < my_unit->unit_block[i].ncells; j++){
      fread_int32(&(my_unit->unit_block[i].unit_cells[j].atomnumber),1,instream);
      fread_uint16(&(my_unit->unit_block[i].unit_cells[j].x),1,instream);
      fread_uint16(&(my_unit->unit_block[i].unit_cells[j].y),1,instream);
      fread_int32(&(my_unit->unit_block[i].unit_cells[j].indexpos),1,instream);
      fread_char(&(my_unit->unit_block[i].unit_cells[j].pbase),1,instream);
      fread_char(&(my_unit->unit_block[i].unit_cells[j].tbase),1,instream);
    }


  }


  return 1;

}

/*************************************************************************
 **
 ** static void dealloc_cdf_xda(cdf_xda *my_cdf)
 **
 ** Deallocates all the previously allocated memory.
 ** 
 *************************************************************************/

static void dealloc_cdf_xda(cdf_xda *my_cdf){

  int i;

  for (i=0; i < my_cdf->header.n_units; i++){
    Free(my_cdf->probesetnames[i]);
  }              
  Free(my_cdf->probesetnames);

  Free(my_cdf->qc_start);
  Free(my_cdf->units_start);

  for (i=0; i < my_cdf->header.n_qc_units; i++){
    Free(my_cdf->qc_units[i].qc_probes);
  }

  Free(my_cdf->qc_units);


  for (i=0; i < my_cdf->header.n_units; i++){
    Free(my_cdf->units[i].unit_block);
  }
  Free(my_cdf->units);
  Free(my_cdf->header.ref_seq);

} 



/*************************************************************
 **
 ** int read_cdf_xda(const char *filename)
 **
 ** filename - Name of the prospective binary cel file
 **
 ** Returns 1 if the file was completely successfully parsed
 ** otherwise 0 (and possible prints a message to screen)
 ** 
 **
 **
 **
 *************************************************************/

static int read_cdf_xda(const char *filename,cdf_xda *my_cdf){

  FILE *infile;

  int i;

  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }

  if (!fread_int32(&my_cdf->header.magicnumber,1,infile)){
    return 0;
  }

  if (!fread_int32(&my_cdf->header.version_number,1,infile)){
    return 0;
  }


  if (my_cdf->header.magicnumber != 67){
    Rprintf("Magic number is not 67. This is probably not a binary cdf file.\n");
    return 0;
  }

  if (my_cdf->header.version_number != 1){
    Rprintf("Don't know if version %d binary cdf files can be handled.\n",my_cdf->header.version_number);
    return 0;
  } 
  if (!fread_uint16(&my_cdf->header.cols,1,infile)){
    return 0;
  }
  if (!fread_uint16(&my_cdf->header.rows,1,infile)){
    return 0;
  }
 
  if (!fread_int32(&my_cdf->header.n_units,1,infile)){
    return 0;
  }

  if (!fread_int32(&my_cdf->header.n_qc_units,1,infile)){
    return 0;
  }

  
  if (!fread_int32(&my_cdf->header.len_ref_seq,1,infile)){
    return 0;
  }
  
  my_cdf->header.ref_seq = Calloc(my_cdf->header.len_ref_seq,char);

  fread_char(my_cdf->header.ref_seq, my_cdf->header.len_ref_seq, infile);
  my_cdf->probesetnames = Calloc(my_cdf->header.n_units,char *);


  for (i =0; i < my_cdf->header.n_units;i++){
    my_cdf->probesetnames[i] = Calloc(64,char);
    if (!fread_char(my_cdf->probesetnames[i], 64, infile)){
      return 0;
    }
  }



  my_cdf->qc_start = Calloc(my_cdf->header.n_qc_units,int);
  my_cdf->units_start = Calloc(my_cdf->header.n_units,int);

  /*** Old code that might fail if there is 0 QCunits or 0 Units
       if (!fread_int32(my_cdf->qc_start,my_cdf->header.n_qc_units,infile) 
       || !fread_int32(my_cdf->units_start,my_cdf->header.n_units,infile)){
       return 0;
       }
  ***/

  if (!fread_int32(my_cdf->qc_start,my_cdf->header.n_qc_units,infile)) {
    if(my_cdf->header.n_qc_units != 0) {
      return 0;
    }
  }

  if(!fread_int32(my_cdf->units_start,my_cdf->header.n_units,infile)) {
    if(my_cdf->header.n_units != 0) {
      return 0;
    }
  }

  /* We will read in all the QC and Standard Units, rather than  
     random accessing what we need */
  my_cdf->qc_units = Calloc(my_cdf->header.n_qc_units,cdf_qc_unit);
  
  
  for (i =0; i < my_cdf->header.n_qc_units; i++){
    if (!read_cdf_qcunit(&my_cdf->qc_units[i],my_cdf->qc_start[i],infile)){
      return 0;
    }
  }
    
  my_cdf->units = Calloc(my_cdf->header.n_units,cdf_unit);


  for (i=0; i < my_cdf->header.n_units; i++){
    if (!read_cdf_unit(&my_cdf->units[i],my_cdf->units_start[i],infile)){
      return 0;
    }
  }
  

#ifdef READ_CDF_DEBUG
   Rprintf("%d %d %d %d  %d\n",my_cdf->header.cols,my_cdf->header.rows,my_cdf->header.n_units,my_cdf->header.n_qc_units,my_cdf->header.len_ref_seq);
  for (i =0; i < my_cdf->header.n_units;i++){
    Rprintf("%s\n",my_cdf->probesetnames[i]);
  }

  for (i =0; i < my_cdf->header.n_qc_units;i++){
    Rprintf("%d\n",my_cdf->qc_start[i]);
  }
  
  for (i =0; i < my_cdf->header.n_qc_units;i++){
    Rprintf("%d\n",my_cdf->units_start[i]);
  }

  Rprintf("%d %d\n",my_cdf->qc_units[0].type,my_cdf->qc_units[0].n_probes);
  
  for (i=0; i < my_cdf->qc_units[0].n_probes; i++){
    Rprintf("%d %d %d %u %d\n",my_cdf->qc_units[0].qc_probes[i].x,my_cdf->qc_units[0].qc_probes[i].y,
	    my_cdf->qc_units[0].qc_probes[i].probelength,
	    my_cdf->qc_units[0].qc_probes[i].pmflag,
	    my_cdf->qc_units[0].qc_probes[i].bgprobeflag);

  }
  

  Rprintf("%u %u %d %d %d %d %u\n",my_cdf->units[0].unittype,my_cdf->units[0].direction,
	  my_cdf->units[0].natoms,
	  my_cdf->units[0].nblocks,
	  my_cdf->units[0].ncells,
	  my_cdf->units[0].unitnumber,
	  my_cdf->units[0].ncellperatom);

    Rprintf("%d %d %u %u %d %d %s\n",my_cdf->units[0].unit_block[0].natoms,my_cdf->units[0].unit_block[0].ncells,
	    my_cdf->units[0].unit_block[0].ncellperatom,
	    my_cdf->units[0].unit_block[0].direction,
	    my_cdf->units[0].unit_block[0].firstatom,
	    my_cdf->units[0].unit_block[0].unused,
	    my_cdf->units[0].unit_block[0].blockname);
    
    for (i=0; i <my_cdf->units[0].unit_block[0].ncells  ; i++){
      Rprintf("%d %u %u %d %c %c\n",
	      my_cdf->units[0].unit_block[0].unit_cells[i].atomnumber,
	      my_cdf->units[0].unit_block[0].unit_cells[i].x,
	      my_cdf->units[0].unit_block[0].unit_cells[i].y,
	      my_cdf->units[0].unit_block[0].unit_cells[i].indexpos,
	      my_cdf->units[0].unit_block[0].unit_cells[i].pbase,
	      my_cdf->units[0].unit_block[0].unit_cells[i].tbase);
    }
#endif
    
  fclose(infile);
  return 1;

  /* fseek() */
}



/*************************************************************
 **
 ** static int check_cdf_xda(const char *filename)
 **
 ** Opens the file give by filename and checks it to see if
 ** it looks like a binary CDF file. returns 0 if
 ** the file looks like it is not a binary CDF aka xda format
 ** cdf file
 **
 **
 *************************************************************/


static int check_cdf_xda(const char *filename){

  FILE *infile;

  
  int magicnumber,version_number;

  if ((infile = fopen(filename, "rb")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }

  if (!fread_int32(&magicnumber,1,infile)){
    error("File corrupt or truncated?");
    return 0;
  }

  if (!fread_int32(&version_number,1,infile)){ 
    error("File corrupt or truncated?");
    return 0;
  }


  if (magicnumber != 67){
    /* error("Magic number is not 67. This is probably not a binary cdf file.\n"); */
    return 0;
  }

  if (version_number != 1){
    /* error("Don't know if version %d binary cdf files can be handled.\n",my_cdf->header.version_number); */
    return 0;
  } 

  return 1;

}



/*************************************************************
 **
 ** static int isPM(char pbase,char tbase)
 **
 ** char pbase - probe base at substitution position
 ** char tbase - target base at substitution position
 **
 ** this function works out whether a probe is a PM or MM
 ** 
 **
 *************************************************************/


static int isPM(char pbase,char tbase){
  /*
  if (Pbase.Cmp(Tbase) == 0){
    *isPM = false;
  } else if (((Pbase.Cmp("A")== 0) && (Tbase.Cmp("T") != 0)) || ((Pbase.Cmp("T")
== 0) && (Tbase.Cmp("A") != 0))){
    *isPM = false;
  } else if (((Pbase.Cmp("C")== 0) && (Tbase.Cmp("G") != 0)) || ((Pbase.Cmp("G")
== 0) && (Tbase.Cmp("C") != 0))){
    *isPM = false;
  } else {
    *isPM = true;
  }
  */

  pbase = toupper(pbase);
  tbase = toupper(tbase);

  if (pbase == tbase){
    return 0;
  } else if ((( pbase == 'A') && (tbase != 'T')) || (( pbase == 'T') && (tbase != 'A'))){
    return 0;
  } else if ((( pbase == 'C') && (tbase != 'G')) || (( pbase == 'G') && (tbase != 'C'))){
    return 0;
  }
  return 1;


}



/*************************************************************
 **
 ** SEXP CheckCDFXDA(SEXP filename)
 ** 
 ** Takes a given file name and returns 1 if it is a xda format CDF file
 ** otherwise it returns 0
 **
 *************************************************************/



SEXP CheckCDFXDA(SEXP filename){
  SEXP tmp;
  int good;
  const char *cur_file_name;
  
  cur_file_name = CHAR(STRING_ELT(filename,0));
  
  good = check_cdf_xda(cur_file_name);
  
  PROTECT(tmp= allocVector(INTSXP,1));

  INTEGER(tmp)[0] = good;

  UNPROTECT(1);
  return tmp;
}






SEXP ReadCDFFile(SEXP filename){
  
  SEXP CDFInfo;
  SEXP Dimensions;
  SEXP LocMap= R_NilValue,tempLocMap;
  SEXP CurLocs;
  SEXP PSnames = R_NilValue,tempPSnames;
  SEXP ColNames;
  SEXP dimnames;

  cdf_xda my_cdf;
  const char *cur_file_name;
  /* char *tmp_name; */

  int i,j,k;
  int cur_blocks,cur_cells, cur_atoms;
  /* int which_probetype; */
  int which_psname=0;

  cdf_unit_cell *current_cell;

  double *curlocs;
  
  /* int nrows, ncols; */

 
  cur_file_name = CHAR(STRING_ELT(filename,0));

  if (!read_cdf_xda(cur_file_name,&my_cdf)){
    error("Problem reading binary cdf file %s. Possibly corrupted or truncated?\n",cur_file_name);
  }
  

  /* We output:
     nrows, ncols in an integer vector, plus a list of probesets PM MM locations (in the BioC style) */
  PROTECT(CDFInfo = allocVector(VECSXP,2));
  PROTECT(Dimensions = allocVector(REALSXP,2));

  if (my_cdf.units[0].unittype ==1){ 
    PROTECT(LocMap = allocVector(VECSXP,my_cdf.header.n_units));
    PROTECT(PSnames = allocVector(STRSXP,my_cdf.header.n_units));
  } else {
    PROTECT(tempLocMap = allocVector(VECSXP,2*my_cdf.header.n_units));
    PROTECT(tempPSnames = allocVector(STRSXP,2*my_cdf.header.n_units));
  }

  NUMERIC_POINTER(Dimensions)[0] = (double)my_cdf.header.rows;
  NUMERIC_POINTER(Dimensions)[1] = (double)my_cdf.header.cols;
  

  for (i=0; i < my_cdf.header.n_units; i++){
#ifdef READ_CDF_DEBUG
    printf("%d\n",i);
#endif
    cur_blocks = my_cdf.units[i].nblocks;

#ifdef READ_CDF_DEBUG
    Rprintf("New Block: ");
#endif
    if (my_cdf.units[i].unittype ==1){
      /* Expression analysis */
      for (j=0; j < cur_blocks; j++){
	
#ifdef READ_CDF_DEBUG
	Rprintf("%s ",my_cdf.units[i].unit_block[j].blockname);
#endif

	cur_cells = my_cdf.units[i].unit_block[j].ncells;
	cur_atoms = my_cdf.units[i].unit_block[j].natoms; 
	
	SET_STRING_ELT(PSnames,i,mkChar(my_cdf.units[i].unit_block[j].blockname));
	
	PROTECT(CurLocs = allocMatrix(REALSXP,cur_atoms,2));
	PROTECT(ColNames = allocVector(STRSXP,2));
	PROTECT(dimnames = allocVector(VECSXP,2));
	SET_STRING_ELT(ColNames,0,mkChar("pm"));
	SET_STRING_ELT(ColNames,1,mkChar("mm"));
	
	curlocs = NUMERIC_POINTER(AS_NUMERIC(CurLocs));
	
        for (k=0; k < cur_atoms*2; k++){
	  curlocs[k] = R_NaN;
	}

	for (k=0; k < cur_cells; k++){
	  current_cell = &(my_cdf.units[i].unit_block[j].unit_cells[k]);
	  
	  if(isPM(current_cell->pbase,current_cell->tbase)){
	    curlocs[current_cell->atomnumber] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1;           /* "y*", sizex, "+x+1"; */
	  } else {
	    curlocs[current_cell->atomnumber+ cur_atoms] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1; 
	  }
	}
	

      
	SET_VECTOR_ELT(dimnames,1,ColNames);
	setAttrib(CurLocs, R_DimNamesSymbol, dimnames);
	SET_VECTOR_ELT(LocMap,i,CurLocs);
	UNPROTECT(3);
      }
    } else if (my_cdf.units[i].unittype == 2){
      /* Genotyping array */

#ifndef READ_CDF_NOSNP
      if (cur_blocks == 1){
	
	cur_cells = my_cdf.units[i].unit_block[0].ncells;
	cur_atoms = my_cdf.units[i].unit_block[0].natoms; 
	
	SET_STRING_ELT(tempPSnames,which_psname,mkChar(my_cdf.units[i].unit_block[0].blockname));
	
	PROTECT(CurLocs = allocMatrix(REALSXP,cur_atoms,2));
	PROTECT(ColNames = allocVector(STRSXP,2));
	PROTECT(dimnames = allocVector(VECSXP,2));
	SET_STRING_ELT(ColNames,0,mkChar("pm"));
	SET_STRING_ELT(ColNames,1,mkChar("mm"));
	
	curlocs = NUMERIC_POINTER(AS_NUMERIC(CurLocs));
	
	for (k=0; k < cur_cells; k++){
	  current_cell = &(my_cdf.units[i].unit_block[0].unit_cells[k]);
	  
	  if(isPM(current_cell->pbase,current_cell->tbase)){
	    curlocs[current_cell->atomnumber] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1;           /* "y*", sizex, "+x+1"; */
	  } else {
	    curlocs[current_cell->atomnumber+ cur_atoms] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1; 
	  }
	}
	

      
	SET_VECTOR_ELT(dimnames,1,ColNames);
	setAttrib(CurLocs, R_DimNamesSymbol, dimnames);
	SET_VECTOR_ELT(tempLocMap,which_psname,CurLocs);
	UNPROTECT(3);
	which_psname++;

      } else if (cur_blocks == 4){
	for (j=0; j < cur_blocks; j++){
#ifdef READ_CDF_DEBUG_SNP
	  Rprintf("%s %s\n",my_cdf.probesetnames[i],my_cdf.units[i].unit_block[j].blockname);
#endif
	}
	
	j = 0;
	cur_cells = my_cdf.units[i].unit_block[0].ncells;
	cur_atoms = my_cdf.units[i].unit_block[0].natoms; 
	if (strlen(my_cdf.units[i].unit_block[j].blockname) == 1){
	  tmp_name = Calloc(strlen(my_cdf.probesetnames[i])+2,char);
	  tmp_name = strcpy(tmp_name,my_cdf.probesetnames[i]);
	  tmp_name = strcat(tmp_name,my_cdf.units[i].unit_block[j].blockname);
	  SET_STRING_ELT(tempPSnames,which_psname,mkChar(tmp_name));
	  Free(tmp_name);
	} else {
	  SET_STRING_ELT(tempPSnames,which_psname,mkChar(my_cdf.units[i].unit_block[0].blockname));
	}

	PROTECT(CurLocs = allocMatrix(REALSXP,2*cur_atoms,2));
	PROTECT(ColNames = allocVector(STRSXP,2));
	PROTECT(dimnames = allocVector(VECSXP,2));
	SET_STRING_ELT(ColNames,0,mkChar("pm"));
	SET_STRING_ELT(ColNames,1,mkChar("mm"));
	
	curlocs = NUMERIC_POINTER(AS_NUMERIC(CurLocs));


	for (k=0; k < cur_cells; k++){
	  current_cell = &(my_cdf.units[i].unit_block[0].unit_cells[k]);
	  /*	  Rprintf("%d %d  %u %u \n",cur_cells, current_cell->atomnumber,current_cell->x,current_cell->y); */
	  if(isPM(current_cell->pbase,current_cell->tbase)){
	    curlocs[current_cell->atomnumber] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1;           /* "y*", sizex, "+x+1"; */
	  } else {
	    curlocs[current_cell->atomnumber+ 2*cur_atoms] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1; 
	  }
	  if (current_cell->x + current_cell->y*(my_cdf.header.rows) + 1 == 370737){
	    Rprintf("%d %c %c",isPM(current_cell->pbase,current_cell->tbase),current_cell->pbase,current_cell->tbase);
	  }
	}

	j=2;
	cur_cells = my_cdf.units[i].unit_block[2].ncells;
	cur_atoms = my_cdf.units[i].unit_block[2].natoms; 
	for (k=0; k < cur_cells; k++){
	  current_cell = &(my_cdf.units[i].unit_block[2].unit_cells[k]);
	  /* Rprintf("half : %d %d  %u %u \n",cur_cells, current_cell->atomnumber,current_cell->x,current_cell->y); */
	  if(isPM(current_cell->pbase,current_cell->tbase)){
	    curlocs[current_cell->atomnumber - (cur_atoms)] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1;           /* "y*", sizex, "+x+1"; */
	  } else {
	    curlocs[current_cell->atomnumber - (cur_atoms)+ 2*cur_atoms] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1; 
	  }
	}
	
	SET_VECTOR_ELT(dimnames,1,ColNames);
	setAttrib(CurLocs, R_DimNamesSymbol, dimnames);
	SET_VECTOR_ELT(tempLocMap,which_psname,CurLocs);	
	UNPROTECT(3);
	which_psname++;





	j = 1;	
	cur_cells = my_cdf.units[i].unit_block[1].ncells;
	cur_atoms = my_cdf.units[i].unit_block[1].natoms; 
	if (strlen(my_cdf.units[i].unit_block[j].blockname) == 1){
	  tmp_name = Calloc(strlen(my_cdf.probesetnames[i])+2,char);
	  tmp_name = strcpy(tmp_name,my_cdf.probesetnames[i]);
	  tmp_name = strcat(tmp_name,my_cdf.units[i].unit_block[j].blockname);
	  SET_STRING_ELT(tempPSnames,which_psname,mkChar(tmp_name));
	  Free(tmp_name);
	} else {
	  SET_STRING_ELT(tempPSnames,which_psname,mkChar(my_cdf.units[i].unit_block[1].blockname));
	}
	PROTECT(CurLocs = allocMatrix(REALSXP,2*cur_atoms,2));
	PROTECT(ColNames = allocVector(STRSXP,2));
	PROTECT(dimnames = allocVector(VECSXP,2));
	SET_STRING_ELT(ColNames,0,mkChar("pm"));
	SET_STRING_ELT(ColNames,1,mkChar("mm"));
	curlocs = NUMERIC_POINTER(AS_NUMERIC(CurLocs));
	
	for (k=0; k < cur_cells; k++){
	  current_cell = &(my_cdf.units[i].unit_block[1].unit_cells[k]);
	  /* Rprintf("Dual : %d %d  %u %u \n",cur_cells, current_cell->atomnumber,current_cell->x,current_cell->y); */
	  if(isPM(current_cell->pbase,current_cell->tbase)){
	    curlocs[current_cell->atomnumber - (cur_atoms)] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1;           /* "y*", sizex, "+x+1"; */
	  } else {
	    curlocs[current_cell->atomnumber - (cur_atoms)+ 2*cur_atoms] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1; 
	  }
	}
		
	j=3;
	cur_cells = my_cdf.units[i].unit_block[3].ncells;
	cur_atoms = my_cdf.units[i].unit_block[3].natoms; 
	for (k=0; k < cur_cells; k++){
	  current_cell = &(my_cdf.units[i].unit_block[3].unit_cells[k]);
	  /* Rprintf("half deux : %d %d  %d %u %u \n",cur_cells, current_cell->atomnumber, cur_atoms,current_cell->x,current_cell->y); */
	  if(isPM(current_cell->pbase,current_cell->tbase)){
	    curlocs[current_cell->atomnumber - (2*cur_atoms)] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1;           /* "y*", sizex, "+x+1"; */
	  } else {
	    curlocs[current_cell->atomnumber] = current_cell->x + current_cell->y*(my_cdf.header.rows) + 1; 
	  }
	}
	
	SET_VECTOR_ELT(dimnames,1,ColNames);
	setAttrib(CurLocs, R_DimNamesSymbol, dimnames);
	SET_VECTOR_ELT(tempLocMap,which_psname,CurLocs);	
	UNPROTECT(3);
	which_psname++;

      } else {
	error("makecdfenv does not currently know how to handle cdf files of this type (genotyping with blocks != 1 or 4.)"); 	
      }
#else
      error("makecdfenv does not currently know how to handle cdf files of this type (genotyping).");
#endif




    } else { 
      error("makecdfenv does not currently know how to handle cdf files of this type (ie not expression or genotyping)"); 
    }

    
#ifdef READ_CDF_DEBUG
    Rprintf("\n");    
#endif
  }

  if (my_cdf.units[0].unittype ==2){
    PROTECT(PSnames = allocVector(STRSXP,which_psname));
    PROTECT(LocMap = allocVector(VECSXP,which_psname));
    for (i =0; i < which_psname; i++){
      SET_STRING_ELT(PSnames,i,mkChar(CHAR(STRING_ELT(tempPSnames,i))));
      SET_VECTOR_ELT(LocMap,i,VECTOR_ELT(tempLocMap,i));
    }
    
  }
#ifdef READ_CDF_DEBUG
  Rprintf("%d \n",which_psname);
#endif
  setAttrib(LocMap,R_NamesSymbol,PSnames);
  SET_VECTOR_ELT(CDFInfo,0,Dimensions);
  SET_VECTOR_ELT(CDFInfo,1,LocMap);
  if (my_cdf.units[0].unittype ==2){
    UNPROTECT(6);
  } else {
    UNPROTECT(4);
  }

  dealloc_cdf_xda(&my_cdf);
  return CDFInfo;

}




/* This function is for reading in the entire binary cdf file and then 
 * returing the structure in a complex list object.
 * The fullstructure argument is expected to be a BOOLEAN. If TRUE the
 * entire contents of the CDF file are returned.
 * If False, a modified CDFENV style structure is returned
 */



SEXP ReadCDFFileIntoRList(SEXP filename,SEXP fullstructure){

  SEXP CDFInfo = R_NilValue;  /* this is the object that will be returned */
  SEXP CDFInfoNames;
  SEXP HEADER;  /* Will store the header information */
  SEXP HEADERNames;
  SEXP Dimensions;
  SEXP DimensionsNames;
  SEXP REFSEQ;  /* Resequencing reference sequence */
  SEXP UNITNAMES;

  SEXP FILEPOSITIONS;
  SEXP FILEPOSITIONSQC;
  SEXP FILEPOSITIONSUNITS;
  SEXP FILEPOSITIONSNames;

  SEXP QCUNITS;
  SEXP QCUNITSsub;
  SEXP QCUNITSsubNames;
  SEXP QCHEADER;
  SEXP QCHEADERNames;
  SEXP QCUNITSProbeInfo;
  SEXP QCUNITSProbeInfoX;
  SEXP QCUNITSProbeInfoY;
  SEXP QCUNITSProbeInfoPL;
  SEXP QCUNITSProbeInfoPMFLAG;
  SEXP QCUNITSProbeInfoBGFLAG;
  SEXP QCUNITSProbeInfoNames;
  SEXP QCUNITSProbeInforow_names;

  SEXP UNITS;
  SEXP tmpUNIT;
  SEXP tmpUNITNames;
  SEXP UNITSHeader;
  SEXP UNITSHeaderNames;
  SEXP tmpUNITSBlock;
  SEXP UNITSBlock;
  SEXP UNITSBlockNames;
  SEXP UNITSBlockHeader;
  SEXP UNITSBlockHeaderNames;
  SEXP UNITSBlockInfo;
  SEXP UNITSBlockInfoNames;
  SEXP UNITSBlockInforow_names;
  SEXP UNITSBlockAtom ;
  SEXP UNITSBlockX;
  SEXP UNITSBlockY;
  SEXP UNITSBlockIndexPos;
  SEXP UNITSBlockPbase;
  SEXP UNITSBlockTbase;
  







  char buf[10];
  int i,j,k;

  cdf_xda my_cdf;
  const char *cur_file_name;
  cur_file_name = CHAR(STRING_ELT(filename,0));

  /* Read in the xda style CDF file into memory */
  if (!read_cdf_xda(cur_file_name,&my_cdf)){
    error("Problem reading binary cdf file %s. Possibly corrupted or truncated?\n",cur_file_name);
  }
  

  if (asInteger(fullstructure)){
    /* return the full structure */
    PROTECT(CDFInfo = allocVector(VECSXP,5));

    PROTECT(CDFInfoNames = allocVector(STRSXP,5));
    SET_STRING_ELT(CDFInfoNames,0,mkChar("Header"));
    SET_STRING_ELT(CDFInfoNames,1,mkChar("UnitNames"));
    SET_STRING_ELT(CDFInfoNames,2,mkChar("FilePositions"));
    SET_STRING_ELT(CDFInfoNames,3,mkChar("QCUnits"));
    SET_STRING_ELT(CDFInfoNames,4,mkChar("Units"));
    setAttrib(CDFInfo,R_NamesSymbol,CDFInfoNames);
    UNPROTECT(1);

    PROTECT(HEADER  = allocVector(VECSXP,2));
    PROTECT(HEADERNames = allocVector(STRSXP,2));
    SET_STRING_ELT(HEADERNames,0,mkChar("Dimensions"));
    SET_STRING_ELT(HEADERNames,1,mkChar("ReseqRefSeq"));
    setAttrib(HEADER,R_NamesSymbol,HEADERNames);
    UNPROTECT(1);

    PROTECT(Dimensions = allocVector(REALSXP,7));
    NUMERIC_POINTER(Dimensions)[0] = (double)my_cdf.header.magicnumber;
    NUMERIC_POINTER(Dimensions)[1] = (double)my_cdf.header.version_number;
    NUMERIC_POINTER(Dimensions)[2] = (double)my_cdf.header.cols;
    NUMERIC_POINTER(Dimensions)[3] = (double)my_cdf.header.rows;
    NUMERIC_POINTER(Dimensions)[4] = (double)my_cdf.header.n_qc_units;
    NUMERIC_POINTER(Dimensions)[5] = (double)my_cdf.header.n_units;
    NUMERIC_POINTER(Dimensions)[6] = (double)my_cdf.header.len_ref_seq;
    
    PROTECT(DimensionsNames = allocVector(STRSXP,7));
    SET_STRING_ELT(DimensionsNames,0,mkChar("MagicNumber"));
    SET_STRING_ELT(DimensionsNames,1,mkChar("VersionNumber"));
    SET_STRING_ELT(DimensionsNames,2,mkChar("Cols"));
    SET_STRING_ELT(DimensionsNames,3,mkChar("Rows"));
    SET_STRING_ELT(DimensionsNames,4,mkChar("n.QCunits"));
    SET_STRING_ELT(DimensionsNames,5,mkChar("n.units"));
    SET_STRING_ELT(DimensionsNames,6,mkChar("LenRefSeq"));
    setAttrib(Dimensions,R_NamesSymbol,DimensionsNames);
    SET_VECTOR_ELT(HEADER,0,Dimensions);
    UNPROTECT(2);
    
    PROTECT(REFSEQ = allocVector(STRSXP,1));
    SET_STRING_ELT(REFSEQ,0,mkChar(my_cdf.header.ref_seq));
    SET_VECTOR_ELT(HEADER,1,REFSEQ);
    UNPROTECT(1);

    SET_VECTOR_ELT(CDFInfo,0,HEADER);
    UNPROTECT(1);
    
    PROTECT(UNITNAMES = allocVector(STRSXP,my_cdf.header.n_units));
    for (i =0; i < my_cdf.header.n_units; i++){
      SET_STRING_ELT(UNITNAMES,i,mkChar(my_cdf.probesetnames[i]));
    }
    SET_VECTOR_ELT(CDFInfo,1,UNITNAMES);
    UNPROTECT(1);

    PROTECT(FILEPOSITIONS  = allocVector(VECSXP,2));
    PROTECT(FILEPOSITIONSQC = allocVector(REALSXP,my_cdf.header.n_qc_units));
    PROTECT(FILEPOSITIONSUNITS = allocVector(REALSXP,my_cdf.header.n_units));
    for (i =0; i < my_cdf.header.n_qc_units; i++){
      NUMERIC_POINTER(FILEPOSITIONSQC)[i] = (double)my_cdf.qc_start[i];
    }
    for (i =0; i < my_cdf.header.n_units; i++){
      NUMERIC_POINTER(FILEPOSITIONSUNITS)[i] = (double)my_cdf.units_start[i];
    }
    SET_VECTOR_ELT(FILEPOSITIONS,0,FILEPOSITIONSQC);
    SET_VECTOR_ELT(FILEPOSITIONS,1,FILEPOSITIONSUNITS);
    PROTECT(FILEPOSITIONSNames  = allocVector(STRSXP,2));
    SET_STRING_ELT(FILEPOSITIONSNames,0,mkChar("FilePosQC"));
    SET_STRING_ELT(FILEPOSITIONSNames,1,mkChar("FilePosUnits"));
    setAttrib(FILEPOSITIONS,R_NamesSymbol,FILEPOSITIONSNames);
    SET_VECTOR_ELT(CDFInfo,2,FILEPOSITIONS);
    UNPROTECT(4);
    
    PROTECT(QCUNITS = allocVector(VECSXP,my_cdf.header.n_qc_units));
    for (i =0; i < my_cdf.header.n_qc_units; i++){
      PROTECT(QCUNITSsub = allocVector(VECSXP,2));
      PROTECT(QCUNITSsubNames= allocVector(STRSXP,2));
      SET_STRING_ELT(QCUNITSsubNames,0,mkChar("QCUnitHeader"));
      SET_STRING_ELT(QCUNITSsubNames,1,mkChar("QCUnitInfo"));
      setAttrib(QCUNITSsub,R_NamesSymbol,QCUNITSsubNames);

      PROTECT(QCHEADER = allocVector(REALSXP,2));
      NUMERIC_POINTER(QCHEADER)[0] = (double)my_cdf.qc_units[i].type;
      NUMERIC_POINTER(QCHEADER)[1] = (double)my_cdf.qc_units[i].n_probes;
      PROTECT(QCHEADERNames = allocVector(STRSXP,2));
      SET_STRING_ELT(QCHEADERNames,0,mkChar("Type"));
      SET_STRING_ELT(QCHEADERNames,1,mkChar("n.probes"));

      setAttrib(QCHEADER,R_NamesSymbol,QCHEADERNames);
      SET_VECTOR_ELT(QCUNITSsub,0,QCHEADER);


      PROTECT(QCUNITSProbeInfo = allocVector(VECSXP,5));
      PROTECT(QCUNITSProbeInfoX = allocVector(REALSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoY = allocVector(REALSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoPL = allocVector(REALSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoPMFLAG = allocVector(REALSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoBGFLAG = allocVector(REALSXP,my_cdf.qc_units[i].n_probes));

      for (j=0; j < my_cdf.qc_units[i].n_probes; j++){
	NUMERIC_POINTER(QCUNITSProbeInfoX)[j] = (double)my_cdf.qc_units[i].qc_probes[j].x;	
	NUMERIC_POINTER(QCUNITSProbeInfoY)[j] = (double)my_cdf.qc_units[i].qc_probes[j].y;
	NUMERIC_POINTER(QCUNITSProbeInfoPL)[j] = (double)my_cdf.qc_units[i].qc_probes[j].probelength;
	NUMERIC_POINTER(QCUNITSProbeInfoPMFLAG)[j] = (double)my_cdf.qc_units[i].qc_probes[j].pmflag;
	NUMERIC_POINTER(QCUNITSProbeInfoBGFLAG)[j] = (double)my_cdf.qc_units[i].qc_probes[j].bgprobeflag;
      }

      SET_VECTOR_ELT(QCUNITSProbeInfo,0,QCUNITSProbeInfoX);
      SET_VECTOR_ELT(QCUNITSProbeInfo,1,QCUNITSProbeInfoY);
      SET_VECTOR_ELT(QCUNITSProbeInfo,2,QCUNITSProbeInfoPL);
      SET_VECTOR_ELT(QCUNITSProbeInfo,3,QCUNITSProbeInfoPMFLAG);
      SET_VECTOR_ELT(QCUNITSProbeInfo,4,QCUNITSProbeInfoBGFLAG);

      PROTECT(QCUNITSProbeInfoNames = allocVector(STRSXP,5));
      SET_STRING_ELT(QCUNITSProbeInfoNames,0,mkChar("x"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,1,mkChar("y"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,2,mkChar("ProbeLength"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,3,mkChar("PMFlag"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,4,mkChar("BGProbeFlag"));

      setAttrib(QCUNITSProbeInfo,R_NamesSymbol,QCUNITSProbeInfoNames);

      PROTECT(QCUNITSProbeInforow_names= allocVector(STRSXP,my_cdf.qc_units[i].n_probes)); 
      
      for (j=0; j < my_cdf.qc_units[i].n_probes; j++){
	sprintf(buf, "%d", j+1);
	SET_STRING_ELT(QCUNITSProbeInforow_names,j,mkChar(buf));
      }



      setAttrib(QCUNITSProbeInfo, R_RowNamesSymbol, QCUNITSProbeInforow_names);


      setAttrib(QCUNITSProbeInfo,R_ClassSymbol,mkString("data.frame"));

      SET_VECTOR_ELT(QCUNITSsub,1,QCUNITSProbeInfo);
      SET_VECTOR_ELT(QCUNITS,i,QCUNITSsub);
      UNPROTECT(12);
    }
    SET_VECTOR_ELT(CDFInfo,3,QCUNITS);
    UNPROTECT(1);

    
    PROTECT(UNITS = allocVector(VECSXP,my_cdf.header.n_units));
    for (i =0; i < my_cdf.header.n_units; i++){
      PROTECT(tmpUNIT = allocVector(VECSXP,2));
      PROTECT(tmpUNITNames = allocVector(STRSXP,2));
      SET_STRING_ELT(tmpUNITNames,0,mkChar("UnitHeader"));
      SET_STRING_ELT(tmpUNITNames,1,mkChar("Block"));
      setAttrib(tmpUNIT,R_NamesSymbol,tmpUNITNames);


      PROTECT(UNITSHeader = allocVector(REALSXP,7));
      PROTECT(UNITSHeaderNames = allocVector(STRSXP,7));
      SET_STRING_ELT(UNITSHeaderNames,0,mkChar("UnitType"));
      SET_STRING_ELT(UNITSHeaderNames,1,mkChar("Direction"));
      SET_STRING_ELT(UNITSHeaderNames,2,mkChar("n.atoms"));
      SET_STRING_ELT(UNITSHeaderNames,3,mkChar("n.blocks"));
      SET_STRING_ELT(UNITSHeaderNames,4,mkChar("n.cells"));
      SET_STRING_ELT(UNITSHeaderNames,5,mkChar("UnitNumber"));
      SET_STRING_ELT(UNITSHeaderNames,6,mkChar("n.cellsperatom"));

      setAttrib(UNITSHeader,R_NamesSymbol,UNITSHeaderNames);

      NUMERIC_POINTER(UNITSHeader)[0] = (double)my_cdf.units[i].unittype;
      NUMERIC_POINTER(UNITSHeader)[1] = (double)my_cdf.units[i].direction;
      NUMERIC_POINTER(UNITSHeader)[2] = (double)my_cdf.units[i].natoms;
      NUMERIC_POINTER(UNITSHeader)[3] = (double)my_cdf.units[i].nblocks;
      NUMERIC_POINTER(UNITSHeader)[4] = (double)my_cdf.units[i].ncells;
      NUMERIC_POINTER(UNITSHeader)[5] = (double)my_cdf.units[i].unitnumber;
      NUMERIC_POINTER(UNITSHeader)[6] = (double)my_cdf.units[i].ncellperatom;

      PROTECT(tmpUNITSBlock = allocVector(VECSXP,my_cdf.units[i].nblocks));
      for (j=0; j < my_cdf.units[i].nblocks; j++){
	PROTECT(UNITSBlock = allocVector(VECSXP,3));
	PROTECT(UNITSBlockNames = allocVector(STRSXP,3));
	SET_STRING_ELT(UNITSBlockNames,0,mkChar("Header"));
	SET_STRING_ELT(UNITSBlockNames,1,mkChar("Name"));
	SET_STRING_ELT(UNITSBlockNames,2,mkChar("UnitInfo"));
	setAttrib(UNITSBlock,R_NamesSymbol,UNITSBlockNames);

	PROTECT(UNITSBlockHeader = allocVector(REALSXP,6));
	PROTECT(UNITSBlockHeaderNames= allocVector(VECSXP,6));
	SET_VECTOR_ELT(UNITSBlockHeaderNames,0,mkChar("n.atoms"));
	SET_VECTOR_ELT(UNITSBlockHeaderNames,1,mkChar("n.cells"));
	SET_VECTOR_ELT(UNITSBlockHeaderNames,2,mkChar("n.cellsperatom"));
	SET_VECTOR_ELT(UNITSBlockHeaderNames,3,mkChar("Direction"));
	SET_VECTOR_ELT(UNITSBlockHeaderNames,4,mkChar("firstatom"));
	SET_VECTOR_ELT(UNITSBlockHeaderNames,5,mkChar("unused"));
	
	NUMERIC_POINTER(UNITSBlockHeader)[0] = (double)my_cdf.units[i].unit_block[j].natoms;
	NUMERIC_POINTER(UNITSBlockHeader)[1] = (double)my_cdf.units[i].unit_block[j].ncells;
	NUMERIC_POINTER(UNITSBlockHeader)[2] = (double)my_cdf.units[i].unit_block[j].ncellperatom;
	NUMERIC_POINTER(UNITSBlockHeader)[3] = (double)my_cdf.units[i].unit_block[j].direction;
	NUMERIC_POINTER(UNITSBlockHeader)[4] = (double)my_cdf.units[i].unit_block[j].firstatom;
	NUMERIC_POINTER(UNITSBlockHeader)[5] = (double)my_cdf.units[i].unit_block[j].unused;
	

	setAttrib(UNITSBlockHeader,R_NamesSymbol,UNITSBlockHeaderNames);
	
	SET_VECTOR_ELT(UNITSBlock,0,UNITSBlockHeader);
	
	SET_VECTOR_ELT(UNITSBlock,1,mkString(my_cdf.units[i].unit_block[j].blockname));

	PROTECT(UNITSBlockInfo = allocVector(VECSXP,6));
	
	PROTECT(UNITSBlockInfoNames = allocVector(STRSXP,6));
	SET_STRING_ELT(UNITSBlockInfoNames,0,mkChar("atom.number"));
	SET_STRING_ELT(UNITSBlockInfoNames,1,mkChar("x"));
	SET_STRING_ELT(UNITSBlockInfoNames,2,mkChar("y"));
	SET_STRING_ELT(UNITSBlockInfoNames,3,mkChar("index.position"));
	SET_STRING_ELT(UNITSBlockInfoNames,4,mkChar("pbase"));
	SET_STRING_ELT(UNITSBlockInfoNames,5,mkChar("tbase"));

	setAttrib(UNITSBlockInfo,R_NamesSymbol,UNITSBlockInfoNames);
	

	PROTECT(UNITSBlockInforow_names = allocVector(STRSXP,my_cdf.units[i].unit_block[j].ncells)); 
      
	for (k=0; k < my_cdf.units[i].unit_block[j].ncells; k++){
	  sprintf(buf, "%d", k+1);
	  SET_STRING_ELT(UNITSBlockInforow_names,k,mkChar(buf));
	}
	
	PROTECT(UNITSBlockAtom = allocVector(INTSXP,my_cdf.units[i].unit_block[j].ncells));
	PROTECT(UNITSBlockX = allocVector(INTSXP,my_cdf.units[i].unit_block[j].ncells));
	PROTECT(UNITSBlockY = allocVector(INTSXP,my_cdf.units[i].unit_block[j].ncells));
	PROTECT(UNITSBlockIndexPos = allocVector(INTSXP,my_cdf.units[i].unit_block[j].ncells));
	PROTECT(UNITSBlockPbase = allocVector(STRSXP,my_cdf.units[i].unit_block[j].ncells));
	PROTECT(UNITSBlockTbase = allocVector(STRSXP,my_cdf.units[i].unit_block[j].ncells));
	
	for (k=0; k < my_cdf.units[i].unit_block[j].ncells; k++){
	  /*  Rprintf("%d %d %d\n",i,j,k);
	  //  NUMERIC_POINTER(UNITSBlockAtom)[k] = (double)my_cdf.units[i].unit_block[j].unit_cells[k].atomnumber;
	  //  NUMERIC_POINTER(UNITSBlockX)[k] = (double)my_cdf.units[i].unit_block[j].unit_cells[k].x;
	  //  NUMERIC_POINTER(UNITSBlockY)[k] = (double)my_cdf.units[i].unit_block[j].unit_cells[k].y;
	  //  NUMERIC_POINTER(UNITSBlockIndexPos)[k] = (double)my_cdf.units[i].unit_block[j].unit_cells[k].indexpos; */
	  INTEGER_POINTER(UNITSBlockAtom)[k] = (int)my_cdf.units[i].unit_block[j].unit_cells[k].atomnumber;
	  INTEGER_POINTER(UNITSBlockX)[k] = (int)my_cdf.units[i].unit_block[j].unit_cells[k].x;
	  INTEGER_POINTER(UNITSBlockY)[k] = (int)my_cdf.units[i].unit_block[j].unit_cells[k].y;
	  INTEGER_POINTER(UNITSBlockIndexPos)[k] = (int)my_cdf.units[i].unit_block[j].unit_cells[k].indexpos;
	  sprintf(buf, "%c",my_cdf.units[i].unit_block[j].unit_cells[k].pbase);
	  SET_STRING_ELT(UNITSBlockPbase,k,mkChar(buf)); 

	  sprintf(buf, "%c",my_cdf.units[i].unit_block[j].unit_cells[k].tbase);
	  SET_STRING_ELT(UNITSBlockTbase,k,mkChar(buf));
	}

	SET_VECTOR_ELT(UNITSBlockInfo,0,UNITSBlockAtom);
	SET_VECTOR_ELT(UNITSBlockInfo,1,UNITSBlockX);
	SET_VECTOR_ELT(UNITSBlockInfo,2,UNITSBlockY);
	SET_VECTOR_ELT(UNITSBlockInfo,3,UNITSBlockIndexPos);
	SET_VECTOR_ELT(UNITSBlockInfo,4,UNITSBlockPbase);
	SET_VECTOR_ELT(UNITSBlockInfo,5,UNITSBlockTbase);
	UNPROTECT(6);




	setAttrib(UNITSBlockInfo, R_RowNamesSymbol, UNITSBlockInforow_names);
	setAttrib(UNITSBlockInfo,R_ClassSymbol,mkString("data.frame"));

	SET_VECTOR_ELT(UNITSBlock,2,UNITSBlockInfo);

	SET_VECTOR_ELT(tmpUNITSBlock,j,UNITSBlock);
	UNPROTECT(7);
      }

      SET_VECTOR_ELT(tmpUNIT,0,UNITSHeader);
      SET_VECTOR_ELT(tmpUNIT,1,tmpUNITSBlock);

      SET_VECTOR_ELT(UNITS,i,tmpUNIT);
      UNPROTECT(5);
    }
    SET_VECTOR_ELT(CDFInfo,4,UNITS);
    UNPROTECT(1);


  } else {
    /* return the abbreviated structure */
    error("Abbreviated structure not yet implemented.\n");
    

  }





  dealloc_cdf_xda(&my_cdf);
  UNPROTECT(1);
  return CDFInfo;


}
