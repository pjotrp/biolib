/****************************************************************
 **
 ** File: read_cdffile2.c
 **
 ** Implementation by: B. M. Bolstad
 **
 ** Copyright (C) B. M. Bolstad 2005
 **
 ** A parser designed to read text CDF files into an R List structure
 **
 ** Note this version only parses GC3.0 version text files (which should
 ** be almost all text CDF files currently used)
 **
 ** Note that the original text CDF parser (from which this file is not in
 ** anyway based) was written by Laurent Gautier. That file was named
 ** read_cdffile.c (originally part of affy and then later makecdfenv)
 **
 ** Implemented based on documentation available from Affymetrix
 **
 ** Implementation begun 2005.
 **
 ** Modification Dates
 ** Jul 24 - Initial version
 ** Sep 20 - Continued Implementation
 ** Sep 21 - Continued Implementation and debugging
 ** Sep 22 - Continued Implementation and testing
 ** Sep 24 - QCunit probes, Unit Block probes, Finish and tested.
 ** Dec 1, 2005 - Some comment cleaning. Added isTextCDFFile,CheckCDFtext
 ** Feb 28, 2006 - replace C++ comments with ANSI comments for older compilers
 ** May 31, 2006 - fix some compiler warnings
 ** Jan 15, 2008 - Fix VECTOR_ELT/STRING_ELT issues
 **  
 **
 *******************************************************************/

#include <R.h>
#include <Rdefines.h>

#include "stdlib.h"
#include "stdio.h"

#ifdef BIOLIB
  #include <biolib_R_map.h>
#endif

#define BUFFER_SIZE 1024


/*****************************************************************
 **
 **
 ** A structure for holding information in the 
 ** "CDF" and "Chip" sections (basically header information)
 **
 ******************************************************************/



typedef struct {

  char *version;
  char *name;
  int rows,cols;
  int numberofunits;
  int maxunit;
  int NumQCUnits;
  char *chipreference;
} cdf_text_header;


/*****************************************************************
 **
 **
 ** A structure for holding QC probe information
 ** Note the "CYCLES" item is ignored and never parsed
 **
 ******************************************************************/


typedef struct {
  int x;
  int y;
  char *probe;
  int plen;
  int atom;
  int index;
  int match;
  int bg;
} cdf_text_qc_probe;







/*******************************************************************
 **
 ** A structure for holding QC units information. These are
 ** areas of the chip that contain probes that may or may not be useful
 ** for QC and other purposes. 
 **
 **
 *******************************************************************/



typedef struct{
  int type;
  unsigned int n_probes;
  int qccontains[8];     /* either 0 or 1 for each of the eight possible fields. a 1 means that field is present.*/
  cdf_text_qc_probe *qc_probes;
  
} cdf_text_qc_unit;


/*******************************************************************
 **
 ** A structure for holding probe information for unit_blocks_probes 
 **
 ** probes are stored within blocks
 ** 
 *******************************************************************/

typedef struct{
  int x;
  int y;
  char *probe;
  char *feat;
  char *qual;
  int expos;
  int pos;
  char *cbase;
  char *pbase;
  char *tbase;
  int atom;
  int index;
  int codonid;
  int codon;
  int regiontype;
  char* region;
} cdf_text_unit_block_probe;




/*******************************************************************
 **
 ** A structure holding Unit_blocks
 **
 ** blocks are stored within units.
 ** blocks contain many probes
 **
 *******************************************************************/

typedef struct{
  char *name;
  int blocknumber;
  int num_atoms;
  int num_cells;
  int start_position;
  int stop_position;
  int direction;
  cdf_text_unit_block_probe *probes;

} cdf_text_unit_block;






/*******************************************************************
 **
 ** A structure for holding "Units" AKA known as probesets
 **
 ** Each unit contains one or more blocks. Each block contains one or
 ** more probes
 **
 *******************************************************************/


typedef struct{
  char *name;
  int direction;
  int num_atoms;
  int num_cells;
  int unit_number;
  int unit_type;
  int numberblocks;
  int MutationType;
  cdf_text_unit_block *blocks;
} cdf_text_unit;



/*******************************************************************
 **
 ** A structure for holding a text CDF file
 **
 ** text cdf files consist of 
 ** basic header information
 ** qcunits
 **       - qc probes
 ** units (aka probesets)
 **       - blocks
 **            - probes
 **
 **
 *******************************************************************/

typedef struct{
  cdf_text_header header;
  cdf_text_qc_unit *qc_units;
  cdf_text_unit *units;
} cdf_text;


/**************************************************************
 **
 ** The following code is for tokenizing strings 
 ** originally included in read_abatch.c from the affy package.
 **
 *************************************************************/

/***************************************************************
 **
 ** tokenset
 ** 
 ** char **tokens  - a array of token strings
 ** int n - number of tokens in this set.
 **
 ** a structure to hold a set of tokens. Typically a tokenset is
 ** created by breaking a character string based upon a set of 
 ** delimiters.
 **
 **
 **************************************************************/

typedef struct{
  char **tokens;
  int n;
} tokenset;



/******************************************************************
 **
 ** tokenset *tokenize(char *str, char *delimiters)
 **
 ** char *str - a string to break into tokens
 ** char *delimiters - delimiters to use in breaking up the line
 **
 **
 ** RETURNS a new tokenset
 **
 ** Given a string, split into tokens based on a set of delimitors
 **
 *****************************************************************/

static tokenset *tokenize(char *str, char *delimiters){

  int i=0;

  char *current_token;
  tokenset *my_tokenset = Calloc(1,tokenset);
  my_tokenset->n=0;
  
  my_tokenset->tokens = NULL;

  current_token = strtok(str,delimiters);
  while (current_token != NULL){
    my_tokenset->n++;
    my_tokenset->tokens = Realloc(my_tokenset->tokens,my_tokenset->n,char*);
    my_tokenset->tokens[i] = Calloc(strlen(current_token)+1,char);
    strcpy(my_tokenset->tokens[i],current_token);
    i++;
    current_token = strtok(NULL,delimiters);
  }

  return my_tokenset; 
}


/******************************************************************
 **
 ** int tokenset_size(tokenset *x)
 **
 ** tokenset *x - a tokenset
 ** 
 ** RETURNS the number of tokens in the tokenset 
 **
 ******************************************************************/

static int tokenset_size(tokenset *x){
  return x->n;
}


/******************************************************************
 **
 ** char *get_token(tokenset *x, int i)
 **
 ** tokenset *x - a tokenset
 ** int i - index of the token to return
 ** 
 ** RETURNS pointer to the i'th token
 **
 ******************************************************************/

static char *get_token(tokenset *x,int i){
  return x->tokens[i];
}

/******************************************************************
 **
 ** void delete_tokens(tokenset *x)
 **
 ** tokenset *x - a tokenset
 ** 
 ** Deallocates all the space allocated for a tokenset 
 **
 ******************************************************************/

static void delete_tokens(tokenset *x){
  
  int i;

  for (i=0; i < x->n; i++){
    Free(x->tokens[i]);
  }
  Free(x->tokens);
  Free(x);
}

/*******************************************************************
 **
 ** int token_ends_with(char *token, char *ends)
 ** 
 ** char *token  -  a string to check
 ** char *ends_in   - we are looking for this string at the end of token
 **
 **
 ** returns  0 if no match, otherwise it returns the index of the first character
 ** which matchs the start of *ends.
 **
 ** Note that there must be one additional character in "token" beyond 
 ** the characters in "ends". So
 **
 **  *token = "TestStr"
 **  *ends = "TestStr"   
 **  
 ** would return 0 but if 
 **
 ** ends = "estStr"
 **
 ** we would return 1.
 **
 ** and if 
 ** 
 ** ends= "stStr"
 ** we would return 2 .....etc
 **
 **
 ******************************************************************/

static int token_ends_with(char *token, char *ends_in){
  
  int tokenlength = strlen(token);
  int ends_length = strlen(ends_in);
  int start_pos;
  char *tmp_ptr;
  
  if (tokenlength <= ends_length){
    /* token string is too short so can't possibly end with ends */
    return 0;
  }
  
  start_pos = tokenlength - ends_length;
  
  tmp_ptr = &token[start_pos];

  if (strcmp(tmp_ptr,ends_in)==0){
    return start_pos;
  } else {
    return 0;
  }
}


/******************************************************************
 **
 ** The following code, also from read_abatch.c is more about locating
 ** sections in the file and reading it in.
 **
 ******************************************************************/


/**
 ** This reads a line from the specified file stream
 **
 **
 **/


static void ReadFileLine(char *buffer, int buffersize, FILE *currentFile){
  if (fgets(buffer, buffersize, currentFile) == NULL){
    error("End of file reached unexpectedly. Perhaps this file is truncated.\n");
  }
}



/******************************************************************
 **
 ** void findStartsWith(FILE *my_file,char *starts, char *buffer)
 **
 ** FILE *my_file - an open file to read from
 ** char *starts - the string to search for at the start of each line
 ** char *buffer - where to place the line that has been read.
 **
 **
 ** Find a line that starts with the specified character string.
 ** At exit buffer should contain that line
 **
 *****************************************************************/


static void  findStartsWith(FILE *my_file,char *starts, char *buffer){

  int starts_len = strlen(starts);
  int match = 1;

  do {
    ReadFileLine(buffer, BUFFER_SIZE, my_file);
    match = strncmp(starts, buffer, starts_len);
  } while (match != 0);
}


/******************************************************************
 **
 ** void AdvanceToSection(FILE *my_file,char *sectiontitle, char *buffer)
 **
 ** FILE *my_file - an open file
 ** char *sectiontitle - string we are searching for
 ** char *buffer - return's with line starting with sectiontitle
 **
 **
 *****************************************************************/

static void AdvanceToSection(FILE *my_file,char *sectiontitle, char *buffer){
  findStartsWith(my_file,sectiontitle,buffer);
}


/*******************************************************************
 **
 ** void read_cdf_header(FILE *infile,  cdf_text *mycdf, char* linebuffer)
 **
 ** FILE *infile - pointer to open file presumed to be a CDF file
 ** cdf_text *mycdf - structure for holding cdf file
 ** char *linebuffer - a place to store strings that are read in. Length
 **                   is given by BUFFER_SIZE
 **
 *******************************************************************/

static void read_cdf_header(FILE *infile,  cdf_text *mycdf, char* linebuffer){

  tokenset *cur_tokenset;

  /* move to the Chip section */
  AdvanceToSection(infile,"[Chip]",linebuffer);
 
  findStartsWith(infile,"Name",linebuffer);
  
  /* Read the Name */
  cur_tokenset = tokenize(linebuffer,"=\r\n");
  mycdf->header.name = Calloc(strlen(get_token(cur_tokenset,1))+1,char);
  strcpy(mycdf->header.name,get_token(cur_tokenset,1));
  delete_tokens(cur_tokenset);

  /* Read the Rows and Cols, Number of units etc  */

  findStartsWith(infile,"Rows",linebuffer);  
  cur_tokenset = tokenize(linebuffer,"=");
  mycdf->header.rows = atoi(get_token(cur_tokenset,1));
  delete_tokens(cur_tokenset);

  findStartsWith(infile,"Cols",linebuffer);
  cur_tokenset = tokenize(linebuffer,"=");
  mycdf->header.cols = atoi(get_token(cur_tokenset,1));
  delete_tokens(cur_tokenset);

  findStartsWith(infile,"NumberOfUnits",linebuffer);
  cur_tokenset = tokenize(linebuffer,"=");
  mycdf->header.numberofunits = atoi(get_token(cur_tokenset,1));
  delete_tokens(cur_tokenset);

  findStartsWith(infile,"MaxUnit",linebuffer);
  cur_tokenset = tokenize(linebuffer,"=");
  mycdf->header.maxunit = atoi(get_token(cur_tokenset,1));
  delete_tokens(cur_tokenset);

  findStartsWith(infile,"NumQCUnits",linebuffer);
  cur_tokenset = tokenize(linebuffer,"=");
  mycdf->header.NumQCUnits = atoi(get_token(cur_tokenset,1));
  delete_tokens(cur_tokenset);
  
  findStartsWith(infile,"ChipReference",linebuffer);
  cur_tokenset = tokenize(linebuffer,"=\r\n");
  if (cur_tokenset->n > 1){
    mycdf->header.chipreference = Calloc(strlen(get_token(cur_tokenset,1))+1,char);
    strcpy(mycdf->header.chipreference,get_token(cur_tokenset,1));
  } else {
    mycdf->header.chipreference = NULL;
  }


  delete_tokens(cur_tokenset);



}



/*******************************************************************
 **
 **  void read_cdf_QCUnits_probes(FILE *infile,  cdf_text *mycdf, char* linebuffer,int index)
 **
 **  FILE *infile - an opened CDF file
 **  cdf_text *mycdf - a structure for holding cdf file
 **  char *linebuffer - temporary place to store lines of text read in
 **  int index - which QCunit. 
 **
 ** This function reads in the QC unit probes from the cdf file. It is assumed that the space to
 ** store them is already allocated.
 **
 *******************************************************************/


static void read_cdf_QCUnits_probes(FILE *infile,  cdf_text *mycdf, char* linebuffer,int index){
  tokenset *cur_tokenset;
  int i;

  for (i =0; i < mycdf->qc_units[index].n_probes; i++){
    ReadFileLine(linebuffer, BUFFER_SIZE, infile);
    cur_tokenset = tokenize(linebuffer,"=\t\r\n");
    if (mycdf->qc_units[index].qccontains[0]){
      mycdf->qc_units[index].qc_probes[i].x = atoi(get_token(cur_tokenset,1));
    }
    if (mycdf->qc_units[index].qccontains[1]){
      mycdf->qc_units[index].qc_probes[i].y = atoi(get_token(cur_tokenset,2));
    }
    if (mycdf->qc_units[index].qccontains[2]){
      mycdf->qc_units[index].qc_probes[i].probe=Calloc(strlen(get_token(cur_tokenset,3))+1,char);
      strcpy(mycdf->qc_units[index].qc_probes[i].probe,get_token(cur_tokenset,3));
    }
    if (mycdf->qc_units[index].qccontains[3]){
      mycdf->qc_units[index].qc_probes[i].plen = atoi(get_token(cur_tokenset,4));
    }
    if (mycdf->qc_units[index].qccontains[4]){
      mycdf->qc_units[index].qc_probes[i].atom = atoi(get_token(cur_tokenset,5));
    }
    if (mycdf->qc_units[index].qccontains[5]){
      mycdf->qc_units[index].qc_probes[i].index = atoi(get_token(cur_tokenset,6));
    }
    if (mycdf->qc_units[index].qccontains[6]){
      mycdf->qc_units[index].qc_probes[i].match = atoi(get_token(cur_tokenset,7));
    }
    if (mycdf->qc_units[index].qccontains[7]){
      mycdf->qc_units[index].qc_probes[i].bg = atoi(get_token(cur_tokenset,8));
    }
    delete_tokens(cur_tokenset);
  }



}

/*******************************************************************
 **
 ** void read_cdf_QCUnits(FILE *infile,  cdf_text *mycdf, char* linebuffer)
 **
 **  FILE *infile - an opened CDF file
 **  cdf_text *mycdf - a structure for holding cdf file
 **  char *linebuffer - temporary place to store lines of text read in
 **
 **  Reads all the QC units. Note that it allocates the space for the probes
 **  it is assumed that the space for the actual QC units are already allocated
 **
 *******************************************************************/

static void read_cdf_QCUnits(FILE *infile,  cdf_text *mycdf, char* linebuffer){
  
  tokenset *cur_tokenset;
  int i,j;

  mycdf->qc_units = Calloc(mycdf->header.NumQCUnits,cdf_text_qc_unit);


  for (i =0; i < mycdf->header.NumQCUnits; i++){
    /* move to the next QC section */
    AdvanceToSection(infile,"[QC",linebuffer);
    findStartsWith(infile,"Type",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->qc_units[i].type = (unsigned short)atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);
    findStartsWith(infile,"NumberCells",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->qc_units[i].n_probes = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);
    mycdf->qc_units[i].qc_probes = Calloc(mycdf->qc_units[i].n_probes,cdf_text_qc_probe);
    
    /* Figure out which fields this QC unit has */
    findStartsWith(infile,"CellHeader",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=\t\r\n");
    for (j=1; j < tokenset_size(cur_tokenset); j++){
      if(strncmp("X", get_token(cur_tokenset,j), 1) == 0){
	mycdf->qc_units[i].qccontains[0]  =1;
      } else if (strncmp("Y", get_token(cur_tokenset,j), 1) == 0){
	mycdf->qc_units[i].qccontains[1]  =1;
      } else if (strncmp("PROBE",get_token(cur_tokenset,j), 5) == 0){
	mycdf->qc_units[i].qccontains[2]  =1;
      } else if (strncmp("PLEN",get_token(cur_tokenset,j), 4) == 0){
	mycdf->qc_units[i].qccontains[3]  =1;
      } else if (strncmp("ATOM",get_token(cur_tokenset,j), 4) == 0){
	mycdf->qc_units[i].qccontains[4]  =1;
      } else if (strncmp("INDEX",get_token(cur_tokenset,j), 5) == 0){
	mycdf->qc_units[i].qccontains[5]  =1;
      } else if (strncmp("MATCH",get_token(cur_tokenset,j), 5) == 0){
	mycdf->qc_units[i].qccontains[6]  =1;
      } else if (strncmp("BG",get_token(cur_tokenset,j), 2) == 0){
	mycdf->qc_units[i].qccontains[7]  =1;
      } 
    }
    delete_tokens(cur_tokenset);
    
    read_cdf_QCUnits_probes(infile,mycdf,linebuffer,i);
    



  }
}

/*******************************************************************
 **
 ** void read_cdf_unit_block_probes(FILE *infile,  cdf_text *mycdf, char* linebuffer, int unit,int block)
 **
 **  FILE *infile - an opened CDF file
 **  cdf_text *mycdf - a structure for holding cdf file
 **  char *linebuffer - temporary place to store lines of text read in from the file
 **  int unit - which unit
 **  int block - which block
 **
 ** Reads in the probes for each unit. Note that it is assumed that the
 ** space for the probes has actually been allocated.
 ** 
 *******************************************************************/



static void read_cdf_unit_block_probes(FILE *infile,  cdf_text *mycdf, char* linebuffer, int unit,int block){
  int i;
   tokenset *cur_tokenset;

  /* Read the Cell Header for the unit block */ 
  ReadFileLine(linebuffer, BUFFER_SIZE, infile);

  for (i =0; i < mycdf->units[unit].blocks[block].num_cells; i++){
    ReadFileLine(linebuffer, BUFFER_SIZE, infile);
    cur_tokenset = tokenize(linebuffer,"=\t\r\n");
    mycdf->units[unit].blocks[block].probes[i].x = atoi(get_token(cur_tokenset,1));
    mycdf->units[unit].blocks[block].probes[i].y = atoi(get_token(cur_tokenset,2));
    mycdf->units[unit].blocks[block].probes[i].probe=Calloc(strlen(get_token(cur_tokenset,3))+1,char);
    strcpy(mycdf->units[unit].blocks[block].probes[i].probe,get_token(cur_tokenset,3));
    mycdf->units[unit].blocks[block].probes[i].feat=Calloc(strlen(get_token(cur_tokenset,4))+1,char);
    strcpy(mycdf->units[unit].blocks[block].probes[i].feat,get_token(cur_tokenset,4));
    mycdf->units[unit].blocks[block].probes[i].qual=Calloc(strlen(get_token(cur_tokenset,5))+1,char);
    strcpy(mycdf->units[unit].blocks[block].probes[i].qual,get_token(cur_tokenset,5));
    mycdf->units[unit].blocks[block].probes[i].expos = atoi(get_token(cur_tokenset,6));
    mycdf->units[unit].blocks[block].probes[i].pos = atoi(get_token(cur_tokenset,7));
    mycdf->units[unit].blocks[block].probes[i].cbase = Calloc(strlen(get_token(cur_tokenset,8))+1,char);
    strcpy(mycdf->units[unit].blocks[block].probes[i].cbase,get_token(cur_tokenset,8));
    mycdf->units[unit].blocks[block].probes[i].pbase = Calloc(strlen(get_token(cur_tokenset,9))+1,char);
    strcpy(mycdf->units[unit].blocks[block].probes[i].pbase,get_token(cur_tokenset,9));
    mycdf->units[unit].blocks[block].probes[i].tbase = Calloc(strlen(get_token(cur_tokenset,10))+1,char);
    strcpy(mycdf->units[unit].blocks[block].probes[i].tbase,get_token(cur_tokenset,10));
    mycdf->units[unit].blocks[block].probes[i].atom = atoi(get_token(cur_tokenset,11));
    mycdf->units[unit].blocks[block].probes[i].index = atoi(get_token(cur_tokenset,12));
    mycdf->units[unit].blocks[block].probes[i].codonid = atoi(get_token(cur_tokenset,13));
    mycdf->units[unit].blocks[block].probes[i].codon = atoi(get_token(cur_tokenset,14));  
    mycdf->units[unit].blocks[block].probes[i].regiontype = atoi(get_token(cur_tokenset,15));  
    delete_tokens(cur_tokenset);
  }

}


/*******************************************************************
 **
 ** void read_cdf_unit_block(FILE *infile,  cdf_text *mycdf, char* linebuffer, int unit)
 ** 
 **  FILE *infile - an opened CDF file
 **  cdf_text *mycdf - a structure for holding cdf file
 **  char *linebuffer - temporary place to store lines of text read in from the file
 **  int unit - which unit
 **
 ** Reads in all the blocks for the unit. Assumes that space for the blocks are allocated
 ** already. Allocates the space for the probes and calls a function to read them in.
 ** 
 *******************************************************************/


static void read_cdf_unit_block(FILE *infile,  cdf_text *mycdf, char* linebuffer, int unit){
  tokenset *cur_tokenset;
  int i;
  

  
  for (i=0; i < mycdf->units[unit].numberblocks; i++){ 

    findStartsWith(infile,"Name",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=\r\n");
    mycdf->units[unit].blocks[i].name = Calloc(strlen(get_token(cur_tokenset,1))+1,char);
    strcpy(mycdf->units[unit].blocks[i].name,get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);
    /* Rprintf("%s\n",mycdf->units[unit].blocks[i].name); */
    


    findStartsWith(infile,"BlockNumber",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[unit].blocks[i].blocknumber = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);
    /*  Rprintf("%d %d %d\n",unit,i,mycdf->header.numberofunits); */

    findStartsWith(infile,"NumAtoms",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[unit].blocks[i].num_atoms = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);

    findStartsWith(infile,"NumCells",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[unit].blocks[i].num_cells = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);


    findStartsWith(infile,"StartPosition",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[unit].blocks[i].start_position = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);

    findStartsWith(infile,"StopPosition",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[unit].blocks[i].stop_position = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);

    if (mycdf->units[unit].unit_type == 2){
      findStartsWith(infile,"Direction",linebuffer);
      cur_tokenset = tokenize(linebuffer,"=");
      mycdf->units[unit].blocks[i].direction = atoi(get_token(cur_tokenset,1));
      delete_tokens(cur_tokenset); 
    } else {
      mycdf->units[unit].blocks[i].direction = mycdf->units[unit].direction;
    }
    
    mycdf->units[unit].blocks[i].probes = Calloc(mycdf->units[unit].blocks[i].num_cells,cdf_text_unit_block_probe);

    read_cdf_unit_block_probes(infile,mycdf,linebuffer,unit,i);
    


  }
}


/*******************************************************************
 **
 ** void read_cdf_Units(FILE *infile,  cdf_text *mycdf, char* linebuffer)
 ** 
 **  FILE *infile - an opened CDF file
 **  cdf_text *mycdf - a structure for holding cdf file
 **  char *linebuffer - temporary place to store lines of text read in from the file
 ** 
 ** Reads in all the units allocating the space for them and then calling sub functions
 ** to read each block and probes within the blocks
 **
 *******************************************************************/

static void read_cdf_Units(FILE *infile,  cdf_text *mycdf, char* linebuffer){
  tokenset *cur_tokenset;
  int i;

  mycdf->units = Calloc(mycdf->header.numberofunits,cdf_text_unit);

  for (i =0; i < mycdf->header.numberofunits; i++){
    /* move to the next Unit section */
    AdvanceToSection(infile,"[Unit",linebuffer);
    findStartsWith(infile,"Name",linebuffer); 
    cur_tokenset = tokenize(linebuffer,"=\r\n");
    mycdf->units[i].name = Calloc(strlen(get_token(cur_tokenset,1))+1,char);
    strcpy(mycdf->units[i].name,get_token(cur_tokenset,1));
 
    delete_tokens(cur_tokenset);
  
    
    
    findStartsWith(infile,"Direction",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[i].direction = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);
    
    findStartsWith(infile,"NumAtoms",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[i].num_atoms = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);
    
    findStartsWith(infile,"NumCells",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[i].num_cells = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);

    findStartsWith(infile,"UnitNumber",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[i].unit_number = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);

    findStartsWith(infile,"UnitType",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[i].unit_type = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset);

    findStartsWith(infile,"NumberBlocks",linebuffer);
    cur_tokenset = tokenize(linebuffer,"=");
    mycdf->units[i].numberblocks = atoi(get_token(cur_tokenset,1));
    delete_tokens(cur_tokenset); 

    /*Skip MutationType since only appears on one type of array */
    
    mycdf->units[i].blocks = Calloc(mycdf->units[i].numberblocks,cdf_text_unit_block);

  
    read_cdf_unit_block(infile,mycdf,linebuffer,i); 
    /*    AdvanceToSection(infile,"[Unit",linebuffer);
	  Rprintf("%d\n",i); */
  }
  


}


/*******************************************************************
 **
 ** int read_cdf_text(const char *filename, cdf_text *mycdf)
 **
 ** const char *filename - name of text file
 ** cdf_text *mycdf - pointer to root of structure that will contain
 **                   the contents of the CDF file at the conclusion
 **                   of the function.
 **
 ** RETURNS 0 if the function failed, otherwise returns 1
 **
 ** this function reads a text CDF file into C data structure.
 **
 *******************************************************************/


static int read_cdf_text(const char *filename, cdf_text *mycdf){

  FILE *infile;

  char linebuffer[BUFFER_SIZE];  /* a character buffer */
  tokenset *cur_tokenset;
  
  if ((infile = fopen(filename, "r")) == NULL)
    {
      error("Unable to open the file %s",filename);
      return 0;
    }
  


  /* Check that is is a text CDF file */
  ReadFileLine(linebuffer, BUFFER_SIZE, infile);
  if (strncmp("[CDF]", linebuffer, 5) != 0){
      error("The file %s does not look like a text CDF file",filename);
  }
  
  /* Read the version number */
  ReadFileLine(linebuffer, BUFFER_SIZE, infile);

  cur_tokenset = tokenize(linebuffer,"=\r\n");
  if (strncmp("GC3.0", get_token(cur_tokenset,1), 5) != 0){
    error("The file %s does not look like a version GC3.0 CDF file",filename);
  } else {
    mycdf->header.version = Calloc(strlen(get_token(cur_tokenset,1))+1,char);
    strcpy(mycdf->header.version,get_token(cur_tokenset,1));
  }
  delete_tokens(cur_tokenset);


  read_cdf_header(infile,mycdf,linebuffer);
  read_cdf_QCUnits(infile,mycdf,linebuffer);
  read_cdf_Units(infile,mycdf,linebuffer);


  return 1;
}

/*******************************************************************
 **
 ** void dealloc_cdf_text(cdf_text *my_cdf)
 **
 ** Frees memory allocated 
 **
 ******************************************************************/



static void dealloc_cdf_text(cdf_text *my_cdf){
  int i,j,k;
  

   Free(my_cdf->header.version);
   Free(my_cdf->header.name);
   if (my_cdf->header.chipreference != NULL)
     Free(my_cdf->header.chipreference);

   for (i =0; i <  my_cdf->header.NumQCUnits; i++){
     for (j=0; j < my_cdf->qc_units[i].n_probes; j++){
       Free(my_cdf->qc_units[i].qc_probes[j].probe);
     }
     Free(my_cdf->qc_units[i].qc_probes);
   } 

   
   for (i =0; i <  my_cdf->header.numberofunits; i++){
     for (j=0; j < my_cdf->units[i].numberblocks; j++){
       for (k=0; k < my_cdf->units[i].blocks[j].num_cells;k++){
	 Free(my_cdf->units[i].blocks[j].probes[k].probe);
	 Free(my_cdf->units[i].blocks[j].probes[k].feat);
	 Free(my_cdf->units[i].blocks[j].probes[k].qual);
	 Free(my_cdf->units[i].blocks[j].probes[k].cbase);
	 Free(my_cdf->units[i].blocks[j].probes[k].pbase);
	 Free(my_cdf->units[i].blocks[j].probes[k].tbase);
       }
       Free(my_cdf->units[i].blocks[j].probes);
       Free(my_cdf->units[i].blocks[j].name);
     }
     Free(my_cdf->units[i].blocks);
     Free(my_cdf->units[i].name);
   } 


}



/*******************************************************************
 **
 ** static int isTextCDFFile(const char *filename)
 **
 ** const char *filename - name of file to check
 **
 ** checks whether the supplied file is a text CDF file or not.
 ** uses a very simple test.
 **
 ** Attempts to open the supplied filename. Then checks to see if the first
 ** 5 characters are "[CDF]" if so returns 1, otherwise 0.
 ** 
 **
 ******************************************************************/

static int isTextCDFFile(const char *filename){


  FILE *infile;

  char linebuffer[BUFFER_SIZE];  /* a character buffer */

  
  if ((infile = fopen(filename, "r")) == NULL)
    {
      error("Unable to open the file %s",filename);
    }
  


  /* Check that is is a text CDF file */
  ReadFileLine(linebuffer, BUFFER_SIZE, infile);
  if (strncmp("[CDF]", linebuffer, 5) == 0){
    fclose(infile);
    return 1;
  }
  fclose(infile);
  return 0;
}





/*******************************************************************
 **
 ** SEXP ReadtextCDFFileIntoRList(SEXP filename)
 **
 ** SEXP filename - name of cdffile. Should be full path to file.
 **     
 ** this function should be called from R. When supplied the name
 ** of a text cdf file it first parses it into a C data structure.
 **
 ** An R list structure is then constructed from the C data structure
 **
 ** The R list is then returned.
 **
 ** Note no special effort is made to reduce down the information in
 ** the text CDF file. Instead almost everything is returned, even 
 ** somewhat redundant information.
 **
 ******************************************************************/


SEXP ReadtextCDFFileIntoRList(SEXP filename){

  SEXP CDFInfo;  /* this is the object that will be returned */
  SEXP CDFInfoNames;
  SEXP HEADER;  /* The file header */
  SEXP HEADERNames;
  SEXP TEMPSXP;
  SEXP TEMPSXP2;
  SEXP TEMPSXP3;
  SEXP TEMPSXP4;

  SEXP QCUNITS;
  SEXP UNITS;


  /* Basically fields (possible) for QC probes */
  SEXP QCUNITSProbeInfoX;
  SEXP QCUNITSProbeInfoY;
  SEXP QCUNITSProbeInfoPROBE;
  SEXP QCUNITSProbeInfoPL;
  SEXP QCUNITSProbeInfoATOM;
  SEXP QCUNITSProbeInfoINDEX;
  SEXP QCUNITSProbeInfoPMFLAG;
  SEXP QCUNITSProbeInfoBGFLAG;
  SEXP QCUNITSProbeInfoNames = R_NilValue;
  SEXP QCUNITSProbeInforow_names;

  /* Basically fields (possible) for  Unit Block probes */
  
  SEXP UNITSProbeInfoX;
  SEXP UNITSProbeInfoY;
  SEXP UNITSProbeInfoPROBE;
  SEXP UNITSProbeInfoFEAT;
  SEXP UNITSProbeInfoQUAL;
  SEXP UNITSProbeInfoEXPOS;
  SEXP UNITSProbeInfoPOS;
  SEXP UNITSProbeInfoCBASE;
  SEXP UNITSProbeInfoPBASE;
  SEXP UNITSProbeInfoTBASE;
  SEXP UNITSProbeInfoATOM;
  SEXP UNITSProbeInfoINDEX;
  SEXP UNITSProbeInfoCODONIND;
  SEXP UNITSProbeInfoCODON;
  SEXP UNITSProbeInfoREGIONTYPE;
  SEXP UNITSProbeInfoNames;
  SEXP UNITSProbeInforow_names;

  char buf[10]; /* temporary buffer for making names */
  int i,j,k,l;
  int tmpsum =0;
						

  cdf_text my_cdf;

  const char *cur_file_name;
  cur_file_name = CHAR(STRING_ELT(filename,0));

  if(!read_cdf_text(cur_file_name, &my_cdf)){
    error("Problem reading text cdf file %s. Possibly corrupted or truncated?\n",cur_file_name);
  }


  /* Now build the R list structure */


   /* return the full structure */
  PROTECT(CDFInfo = allocVector(VECSXP,3));
  PROTECT(CDFInfoNames = allocVector(STRSXP,3));
  SET_STRING_ELT(CDFInfoNames,0,mkChar("Chip"));
  SET_STRING_ELT(CDFInfoNames,1,mkChar("QC"));
  SET_STRING_ELT(CDFInfoNames,2,mkChar("Unit"));

  setAttrib(CDFInfo,R_NamesSymbol,CDFInfoNames);
  UNPROTECT(1);

  /* Deal with the HEADER */
  PROTECT(HEADER = allocVector(VECSXP,8));
  PROTECT(HEADERNames = allocVector(STRSXP,8));
  SET_STRING_ELT(HEADERNames,0,mkChar("Version"));
  SET_STRING_ELT(HEADERNames,1,mkChar("Name"));
  SET_STRING_ELT(HEADERNames,2,mkChar("Rows"));
  SET_STRING_ELT(HEADERNames,3,mkChar("Cols"));
  SET_STRING_ELT(HEADERNames,4,mkChar("NumberOfUnits"));
  SET_STRING_ELT(HEADERNames,5,mkChar("MaxUnit"));
  SET_STRING_ELT(HEADERNames,6,mkChar("NumQCUnits"));
  SET_STRING_ELT(HEADERNames,7,mkChar("ChipReference"));
  setAttrib(HEADER,R_NamesSymbol,HEADERNames);
  UNPROTECT(1);
  
  PROTECT(TEMPSXP = allocVector(STRSXP,1));
  SET_STRING_ELT(TEMPSXP,0,mkChar(my_cdf.header.version));
  SET_VECTOR_ELT(HEADER,0,TEMPSXP); 
  UNPROTECT(1);
  
  PROTECT(TEMPSXP = allocVector(STRSXP,1));
  SET_STRING_ELT(TEMPSXP,0,mkChar(my_cdf.header.name));
  SET_VECTOR_ELT(HEADER,1,TEMPSXP); 
  UNPROTECT(1);

  PROTECT(TEMPSXP = allocVector(REALSXP,1));
  NUMERIC_POINTER(TEMPSXP)[0] = (double)my_cdf.header.rows;
  SET_VECTOR_ELT(HEADER,2,TEMPSXP);
  UNPROTECT(1);
  
  PROTECT(TEMPSXP = allocVector(REALSXP,1));
  NUMERIC_POINTER(TEMPSXP)[0] = (double)my_cdf.header.cols;
  SET_VECTOR_ELT(HEADER,3,TEMPSXP);
  UNPROTECT(1);
 
  PROTECT(TEMPSXP = allocVector(REALSXP,1));
  NUMERIC_POINTER(TEMPSXP)[0] = (double)my_cdf.header.numberofunits;
  SET_VECTOR_ELT(HEADER,4,TEMPSXP);
  UNPROTECT(1);

  PROTECT(TEMPSXP = allocVector(REALSXP,1));
  NUMERIC_POINTER(TEMPSXP)[0] = (double)my_cdf.header.maxunit;
  SET_VECTOR_ELT(HEADER,5,TEMPSXP);
  UNPROTECT(1);

  PROTECT(TEMPSXP = allocVector(REALSXP,1));
  NUMERIC_POINTER(TEMPSXP)[0] = (double)my_cdf.header.NumQCUnits;
  SET_VECTOR_ELT(HEADER,6,TEMPSXP);
  UNPROTECT(1);
  
  PROTECT(TEMPSXP = allocVector(REALSXP,1));
  if (my_cdf.header.chipreference !=NULL){
    SET_VECTOR_ELT(TEMPSXP,0,mkChar(my_cdf.header.chipreference));
    SET_VECTOR_ELT(HEADER,7,TEMPSXP); 
  }
  UNPROTECT(1);
  
  SET_VECTOR_ELT(CDFInfo,0,HEADER);

  PROTECT(QCUNITS = allocVector(VECSXP,my_cdf.header.NumQCUnits));
  for (i=0; i <my_cdf.header.NumQCUnits; i++){
    PROTECT(TEMPSXP=allocVector(VECSXP,3));
    PROTECT(TEMPSXP2 = allocVector(REALSXP,1));
    NUMERIC_POINTER(TEMPSXP2)[0] = (double)my_cdf.qc_units[i].type;
    SET_VECTOR_ELT(TEMPSXP,0,TEMPSXP2);
    UNPROTECT(1);
    PROTECT(TEMPSXP2 = allocVector(REALSXP,1));
    NUMERIC_POINTER(TEMPSXP2)[0] = (double)my_cdf.qc_units[i].n_probes;
    SET_VECTOR_ELT(TEMPSXP,1,TEMPSXP2);
    UNPROTECT(1);
    /*Figure out what the probe information is for this QC unit and then allocate the space */
    tmpsum=0;
    for (j=0; j < 8; j++){
      tmpsum+=my_cdf.qc_units[i].qccontains[j];
    }

    if (tmpsum == 6){
      PROTECT(TEMPSXP2 = allocVector(VECSXP,6));
    } else if (tmpsum ==8){
      PROTECT(TEMPSXP2 = allocVector(VECSXP,8));
    }

    if (tmpsum == 6){
      PROTECT(QCUNITSProbeInfoX = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoY = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoPROBE = allocVector(STRSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoPL = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoATOM = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoINDEX = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
    } else if (tmpsum == 8){
      PROTECT(QCUNITSProbeInfoX = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoY = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoPROBE = allocVector(STRSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoPL = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoATOM = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoINDEX = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoPMFLAG = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      PROTECT(QCUNITSProbeInfoBGFLAG = allocVector(INTSXP,my_cdf.qc_units[i].n_probes));
      
    }
   
    /* store what was read in for the QC units in the R structure */
    if (tmpsum == 6){
      for (j =0; j < my_cdf.qc_units[i].n_probes; j++){
	INTEGER_POINTER(QCUNITSProbeInfoX)[j] = my_cdf.qc_units[i].qc_probes[j].x;
	INTEGER_POINTER(QCUNITSProbeInfoY)[j] = my_cdf.qc_units[i].qc_probes[j].y;
	SET_STRING_ELT(QCUNITSProbeInfoPROBE,j,mkChar( my_cdf.qc_units[i].qc_probes[j].probe));
	INTEGER_POINTER(QCUNITSProbeInfoPL)[j] = my_cdf.qc_units[i].qc_probes[j].plen;
	INTEGER_POINTER(QCUNITSProbeInfoATOM)[j] = my_cdf.qc_units[i].qc_probes[j].atom;
	INTEGER_POINTER(QCUNITSProbeInfoINDEX)[j] = my_cdf.qc_units[i].qc_probes[j].index;

      }
    } else if (tmpsum == 8){
      for (j =0; j < my_cdf.qc_units[i].n_probes; j++){
	INTEGER_POINTER(QCUNITSProbeInfoX)[j] = my_cdf.qc_units[i].qc_probes[j].x;
	INTEGER_POINTER(QCUNITSProbeInfoY)[j] = my_cdf.qc_units[i].qc_probes[j].y;
	SET_STRING_ELT(QCUNITSProbeInfoPROBE,j,mkChar( my_cdf.qc_units[i].qc_probes[j].probe));
	INTEGER_POINTER(QCUNITSProbeInfoPL)[j] = my_cdf.qc_units[i].qc_probes[j].plen;
	INTEGER_POINTER(QCUNITSProbeInfoATOM)[j] = my_cdf.qc_units[i].qc_probes[j].atom;
	INTEGER_POINTER(QCUNITSProbeInfoINDEX)[j] = my_cdf.qc_units[i].qc_probes[j].index;
	INTEGER_POINTER(QCUNITSProbeInfoPMFLAG)[j] = my_cdf.qc_units[i].qc_probes[j].match;
	INTEGER_POINTER(QCUNITSProbeInfoBGFLAG)[j] = my_cdf.qc_units[i].qc_probes[j].bg;
      }
    }

    if (tmpsum == 6){
      SET_VECTOR_ELT(TEMPSXP2,0,QCUNITSProbeInfoX);
      SET_VECTOR_ELT(TEMPSXP2,1,QCUNITSProbeInfoY);
      SET_VECTOR_ELT(TEMPSXP2,2,QCUNITSProbeInfoPROBE);
      SET_VECTOR_ELT(TEMPSXP2,3,QCUNITSProbeInfoPL);
      SET_VECTOR_ELT(TEMPSXP2,4,QCUNITSProbeInfoATOM);
      SET_VECTOR_ELT(TEMPSXP2,5,QCUNITSProbeInfoINDEX);
    } else if (tmpsum ==8){
      SET_VECTOR_ELT(TEMPSXP2,0,QCUNITSProbeInfoX);
      SET_VECTOR_ELT(TEMPSXP2,1,QCUNITSProbeInfoY);
      SET_VECTOR_ELT(TEMPSXP2,2,QCUNITSProbeInfoPROBE);
      SET_VECTOR_ELT(TEMPSXP2,3,QCUNITSProbeInfoPL);
      SET_VECTOR_ELT(TEMPSXP2,4,QCUNITSProbeInfoATOM);
      SET_VECTOR_ELT(TEMPSXP2,5,QCUNITSProbeInfoINDEX);
      SET_VECTOR_ELT(TEMPSXP2,6,QCUNITSProbeInfoPMFLAG);
      SET_VECTOR_ELT(TEMPSXP2,7,QCUNITSProbeInfoBGFLAG);

    }

    
    if (tmpsum == 6){
      UNPROTECT(6);
    } else if (tmpsum == 8){
      UNPROTECT(8);
    }
    

    if (tmpsum == 6){
      PROTECT(QCUNITSProbeInfoNames = allocVector(STRSXP,6));
      SET_STRING_ELT(QCUNITSProbeInfoNames,0,mkChar("x"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,1,mkChar("y"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,2,mkChar("Probe"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,3,mkChar("ProbeLength"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,4,mkChar("Atom"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,5,mkChar("Index"));
    } else if (tmpsum == 8){
      PROTECT(QCUNITSProbeInfoNames = allocVector(STRSXP,8));
      SET_STRING_ELT(QCUNITSProbeInfoNames,0,mkChar("x"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,1,mkChar("y"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,2,mkChar("Probe"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,3,mkChar("ProbeLength"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,4,mkChar("Atom"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,5,mkChar("Index"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,6,mkChar("PMFlag"));
      SET_STRING_ELT(QCUNITSProbeInfoNames,7,mkChar("BGProbeFlag"));
    } 
    setAttrib(TEMPSXP2,R_NamesSymbol,QCUNITSProbeInfoNames);
    UNPROTECT(1);
    PROTECT(QCUNITSProbeInforow_names= allocVector(STRSXP,my_cdf.qc_units[i].n_probes)); 
      
    for (j=0; j < my_cdf.qc_units[i].n_probes; j++){
      sprintf(buf, "%d", j+1);
      SET_STRING_ELT(QCUNITSProbeInforow_names,j,mkChar(buf));
    }
    setAttrib(TEMPSXP2, R_RowNamesSymbol, QCUNITSProbeInforow_names);
    UNPROTECT(1);

    setAttrib(TEMPSXP2,R_ClassSymbol,mkString("data.frame"));
    SET_VECTOR_ELT(TEMPSXP,2,TEMPSXP2);
    UNPROTECT(1);

    PROTECT(TEMPSXP2=allocVector(STRSXP,3));
    SET_STRING_ELT(TEMPSXP2,0,mkChar("Type"));
    SET_STRING_ELT(TEMPSXP2,1,mkChar("NumberCells"));
    SET_STRING_ELT(TEMPSXP2,2,mkChar("QCCells"));
    setAttrib(TEMPSXP,R_NamesSymbol,TEMPSXP2);
    UNPROTECT(1);
    SET_VECTOR_ELT(QCUNITS,i,TEMPSXP);
   
    UNPROTECT(1);
  }
  SET_VECTOR_ELT(CDFInfo,1,QCUNITS);
  UNPROTECT(1);


  PROTECT(UNITS = allocVector(VECSXP,my_cdf.header.numberofunits));
  for (i=0; i < my_cdf.header.numberofunits; i++){
    PROTECT(TEMPSXP=allocVector(VECSXP,8));
    PROTECT(TEMPSXP2=allocVector(STRSXP,1));
      
    SET_STRING_ELT(TEMPSXP2,0,mkChar(my_cdf.units[i].name));
    SET_VECTOR_ELT(TEMPSXP,0,TEMPSXP2);
    UNPROTECT(1);
    
    
    PROTECT(TEMPSXP2 = allocVector(REALSXP,1));
    NUMERIC_POINTER(TEMPSXP2)[0] = (double)my_cdf.units[i].direction;
    SET_VECTOR_ELT(TEMPSXP,1,TEMPSXP2);
    UNPROTECT(1);

    PROTECT(TEMPSXP2 = allocVector(REALSXP,1));
    NUMERIC_POINTER(TEMPSXP2)[0] = (double)my_cdf.units[i].num_atoms;
    SET_VECTOR_ELT(TEMPSXP,2,TEMPSXP2);
    UNPROTECT(1);

    PROTECT(TEMPSXP2 = allocVector(REALSXP,1));
    NUMERIC_POINTER(TEMPSXP2)[0] = (double)my_cdf.units[i].num_cells;
    SET_VECTOR_ELT(TEMPSXP,3,TEMPSXP2);
    UNPROTECT(1);

   
    PROTECT(TEMPSXP2 = allocVector(REALSXP,1));
    NUMERIC_POINTER(TEMPSXP2)[0] = (double)my_cdf.units[i].unit_number;
    SET_VECTOR_ELT(TEMPSXP,4,TEMPSXP2);
    UNPROTECT(1); 

    PROTECT(TEMPSXP2 = allocVector(REALSXP,1));
    NUMERIC_POINTER(TEMPSXP2)[0] = (double)my_cdf.units[i].unit_type;
    SET_VECTOR_ELT(TEMPSXP,5,TEMPSXP2);
    UNPROTECT(1); 

    PROTECT(TEMPSXP2 = allocVector(REALSXP,1));
    NUMERIC_POINTER(TEMPSXP2)[0] = (double)my_cdf.units[i].numberblocks;
    SET_VECTOR_ELT(TEMPSXP,6,TEMPSXP2);
    UNPROTECT(1); 

    PROTECT(TEMPSXP2 = allocVector(VECSXP,my_cdf.units[i].numberblocks));

    for (j=0; j <my_cdf.units[i].numberblocks; j++){
      PROTECT(TEMPSXP3 = allocVector(VECSXP,8));

      
      PROTECT(TEMPSXP4=allocVector(STRSXP,1));
      
      SET_STRING_ELT(TEMPSXP4,0,mkChar(my_cdf.units[i].blocks[j].name));
      SET_VECTOR_ELT(TEMPSXP3,0,TEMPSXP4);
      UNPROTECT(1);

      
      PROTECT(TEMPSXP4=allocVector(REALSXP,1));
      NUMERIC_POINTER(TEMPSXP4)[0] = (double)my_cdf.units[i].blocks[j].blocknumber;
      SET_VECTOR_ELT(TEMPSXP3,1,TEMPSXP4);
      UNPROTECT(1);

      PROTECT(TEMPSXP4=allocVector(REALSXP,1));
      NUMERIC_POINTER(TEMPSXP4)[0] = (double)my_cdf.units[i].blocks[j].num_atoms;
      SET_VECTOR_ELT(TEMPSXP3,2,TEMPSXP4);
      UNPROTECT(1);
      
      PROTECT(TEMPSXP4=allocVector(REALSXP,1));
      NUMERIC_POINTER(TEMPSXP4)[0] = (double)my_cdf.units[i].blocks[j].num_cells;
      SET_VECTOR_ELT(TEMPSXP3,3,TEMPSXP4);
      UNPROTECT(1);
      

      PROTECT(TEMPSXP4=allocVector(REALSXP,1));
      NUMERIC_POINTER(TEMPSXP4)[0] = (double)my_cdf.units[i].blocks[j].start_position;
      SET_VECTOR_ELT(TEMPSXP3,4,TEMPSXP4);
      UNPROTECT(1);
      
      PROTECT(TEMPSXP4=allocVector(REALSXP,1));
      NUMERIC_POINTER(TEMPSXP4)[0] = (double)my_cdf.units[i].blocks[j].stop_position;
      SET_VECTOR_ELT(TEMPSXP3,5,TEMPSXP4);
      UNPROTECT(1);


      PROTECT(TEMPSXP4=allocVector(REALSXP,1));
      NUMERIC_POINTER(TEMPSXP4)[0] = (double)my_cdf.units[i].blocks[j].direction;
      SET_VECTOR_ELT(TEMPSXP3,6,TEMPSXP4);
      UNPROTECT(1);

      PROTECT(TEMPSXP4=allocVector(VECSXP,15));
      

      PROTECT(UNITSProbeInfoX = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoY = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoPROBE = allocVector(STRSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoFEAT = allocVector(STRSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoQUAL = allocVector(STRSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoEXPOS = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoPOS = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoCBASE = allocVector(STRSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoPBASE = allocVector(STRSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoTBASE = allocVector(STRSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoATOM = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoINDEX = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoCODONIND = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoCODON = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      PROTECT(UNITSProbeInfoREGIONTYPE = allocVector(INTSXP,my_cdf.units[i].blocks[j].num_cells));
      for (k=0; k < my_cdf.units[i].blocks[j].num_cells; k++){
	INTEGER_POINTER(UNITSProbeInfoX)[k]=my_cdf.units[i].blocks[j].probes[k].x;
	INTEGER_POINTER(UNITSProbeInfoY)[k]=my_cdf.units[i].blocks[j].probes[k].y;
	INTEGER_POINTER(UNITSProbeInfoEXPOS)[k]=my_cdf.units[i].blocks[j].probes[k].expos;
	INTEGER_POINTER(UNITSProbeInfoPOS)[k]=my_cdf.units[i].blocks[j].probes[k].pos;
	INTEGER_POINTER(UNITSProbeInfoATOM)[k]=my_cdf.units[i].blocks[j].probes[k].atom;
	INTEGER_POINTER(UNITSProbeInfoINDEX)[k]=my_cdf.units[i].blocks[j].probes[k].index;
	INTEGER_POINTER(UNITSProbeInfoCODONIND)[k]=my_cdf.units[i].blocks[j].probes[k].codonid;
	INTEGER_POINTER(UNITSProbeInfoCODON)[k]=my_cdf.units[i].blocks[j].probes[k].codon;
	INTEGER_POINTER(UNITSProbeInfoREGIONTYPE)[k]=my_cdf.units[i].blocks[j].probes[k].regiontype;
	SET_VECTOR_ELT(UNITSProbeInfoPROBE,k,mkChar(my_cdf.units[i].blocks[j].probes[k].probe));
	SET_STRING_ELT(UNITSProbeInfoFEAT,k,mkChar(my_cdf.units[i].blocks[j].probes[k].feat));
	SET_STRING_ELT(UNITSProbeInfoQUAL,k,mkChar(my_cdf.units[i].blocks[j].probes[k].qual));
	SET_STRING_ELT(UNITSProbeInfoCBASE,k,mkChar(my_cdf.units[i].blocks[j].probes[k].cbase));
	SET_STRING_ELT(UNITSProbeInfoPBASE,k,mkChar(my_cdf.units[i].blocks[j].probes[k].pbase));	
	SET_STRING_ELT(UNITSProbeInfoTBASE,k,mkChar(my_cdf.units[i].blocks[j].probes[k].tbase));
      }
      

      SET_VECTOR_ELT(TEMPSXP4,0,UNITSProbeInfoX);
      SET_VECTOR_ELT(TEMPSXP4,1,UNITSProbeInfoY);
      SET_VECTOR_ELT(TEMPSXP4,2,UNITSProbeInfoPROBE);
      SET_VECTOR_ELT(TEMPSXP4,3,UNITSProbeInfoFEAT);
      SET_VECTOR_ELT(TEMPSXP4,4,UNITSProbeInfoQUAL);
      SET_VECTOR_ELT(TEMPSXP4,5,UNITSProbeInfoEXPOS);
      SET_VECTOR_ELT(TEMPSXP4,6,UNITSProbeInfoPOS);
      SET_VECTOR_ELT(TEMPSXP4,7,UNITSProbeInfoCBASE);
      SET_VECTOR_ELT(TEMPSXP4,8,UNITSProbeInfoPBASE);
      SET_VECTOR_ELT(TEMPSXP4,9,UNITSProbeInfoTBASE);
      SET_VECTOR_ELT(TEMPSXP4,10,UNITSProbeInfoATOM);
      SET_VECTOR_ELT(TEMPSXP4,11,UNITSProbeInfoINDEX);
      SET_VECTOR_ELT(TEMPSXP4,12,UNITSProbeInfoCODONIND);
      SET_VECTOR_ELT(TEMPSXP4,13,UNITSProbeInfoCODON);
      SET_VECTOR_ELT(TEMPSXP4,14,UNITSProbeInfoREGIONTYPE);







      UNPROTECT(15);

      PROTECT(UNITSProbeInfoNames =allocVector(STRSXP,15));
      SET_STRING_ELT(UNITSProbeInfoNames,0,mkChar("x"));
      SET_STRING_ELT(UNITSProbeInfoNames,1,mkChar("y"));
      SET_STRING_ELT(UNITSProbeInfoNames,2,mkChar("Probe"));
      SET_STRING_ELT(UNITSProbeInfoNames,3,mkChar("Feat"));
      SET_STRING_ELT(UNITSProbeInfoNames,4,mkChar("Qual"));
      SET_STRING_ELT(UNITSProbeInfoNames,5,mkChar("Expos"));
      SET_STRING_ELT(UNITSProbeInfoNames,6,mkChar("Pos"));
      SET_STRING_ELT(UNITSProbeInfoNames,7,mkChar("cbase"));
      SET_STRING_ELT(UNITSProbeInfoNames,8,mkChar("pbase"));
      SET_STRING_ELT(UNITSProbeInfoNames,9,mkChar("tbase"));
      SET_STRING_ELT(UNITSProbeInfoNames,10,mkChar("Atom"));
      SET_STRING_ELT(UNITSProbeInfoNames,11,mkChar("Index"));
      SET_STRING_ELT(UNITSProbeInfoNames,12,mkChar("CodonInd"));
      SET_STRING_ELT(UNITSProbeInfoNames,13,mkChar("Codon"));
      SET_STRING_ELT(UNITSProbeInfoNames,14,mkChar("Regiontype")); 


      setAttrib(TEMPSXP4,R_NamesSymbol,UNITSProbeInfoNames);
      UNPROTECT(1);
      
      PROTECT(UNITSProbeInforow_names= allocVector(STRSXP,my_cdf.units[i].blocks[j].num_cells)); 
      
      for (l=0; l < my_cdf.units[i].blocks[j].num_cells; l++){
	sprintf(buf, "%d", l+1);
	SET_STRING_ELT(UNITSProbeInforow_names,l,mkChar(buf));
      }
      setAttrib(TEMPSXP4, R_RowNamesSymbol, UNITSProbeInforow_names);
      UNPROTECT(1);



      setAttrib(TEMPSXP4,R_ClassSymbol,mkString("data.frame"));
      SET_VECTOR_ELT(TEMPSXP3,7,TEMPSXP4);
      UNPROTECT(1);



      PROTECT(TEMPSXP4=allocVector(STRSXP,8));
      SET_STRING_ELT(TEMPSXP4,0,mkChar("Name"));
      SET_STRING_ELT(TEMPSXP4,1,mkChar("BlockNumber"));
      SET_STRING_ELT(TEMPSXP4,2,mkChar("NumAtoms"));
      SET_STRING_ELT(TEMPSXP4,3,mkChar("NumCells"));
      SET_STRING_ELT(TEMPSXP4,4,mkChar("StartPosition"));
      SET_STRING_ELT(TEMPSXP4,5,mkChar("StopPosition"));
      SET_STRING_ELT(TEMPSXP4,6,mkChar("Direction"));
      SET_STRING_ELT(TEMPSXP4,7,mkChar("Unit_Block_Cells"));
      setAttrib(TEMPSXP3,R_NamesSymbol,TEMPSXP4);
      UNPROTECT(1);

      SET_VECTOR_ELT(TEMPSXP2,j,TEMPSXP3);
      UNPROTECT(1);
    }






    SET_VECTOR_ELT(TEMPSXP,7,TEMPSXP2);
    UNPROTECT(1); 

    


    PROTECT(TEMPSXP2 = allocVector(STRSXP,8));
    SET_STRING_ELT(TEMPSXP2,0,mkChar("Name"));
    SET_STRING_ELT(TEMPSXP2,1,mkChar("Direction"));
    SET_STRING_ELT(TEMPSXP2,2,mkChar("NumAtoms"));
    SET_STRING_ELT(TEMPSXP2,3,mkChar("NumCells"));
    SET_STRING_ELT(TEMPSXP2,4,mkChar("UnitNumber"));
    SET_STRING_ELT(TEMPSXP2,5,mkChar("UnitType"));
    SET_STRING_ELT(TEMPSXP2,6,mkChar("NumberBlocks"));
    SET_STRING_ELT(TEMPSXP2,7,mkChar("Unit_Block"));
    setAttrib(TEMPSXP,R_NamesSymbol,TEMPSXP2);
    UNPROTECT(1);





    SET_VECTOR_ELT(UNITS,i,TEMPSXP);
    UNPROTECT(1);
    


  }
  SET_VECTOR_ELT(CDFInfo,2,UNITS);
  UNPROTECT(1);


  
  dealloc_cdf_text(&my_cdf);
  UNPROTECT(2);
  return CDFInfo;
}





/*************************************************************
 **
 ** SEXP CheckCDFtext(SEXP filename)
 ** 
 ** Takes a given file name and returns 1 if it is a text format CDF file
 ** otherwise it returns 0
 **
 *************************************************************/



SEXP CheckCDFtext(SEXP filename){
  SEXP tmp;
  int good;
  const char *cur_file_name;
  
  cur_file_name = CHAR(STRING_ELT(filename,0));
  
  good = isTextCDFFile(cur_file_name);
  
  PROTECT(tmp= allocVector(INTSXP,1));

  INTEGER(tmp)[0] = good;

  UNPROTECT(1);
  return tmp;
}

