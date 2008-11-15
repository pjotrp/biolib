/******************************************************************
 **
 ** file: read_pgf.c
 ** 
 ** Aim: implement parsing of PGF format files
 **
 ** Copyright (C) 2007    B. M. Bolstad
 **
 ** Created on Nov 4, 2007
 **
 ** History
 ** Nov 4, 2007 - Initial version
 ** Dec 17. 2007 - add function for counting number of each type of probeset
 ** Dec 31, 2007 - add function which checks that all required fields are present
 ** Mar 18, 2008 - fix error in read_pgf_header function
 **
 **
 ** 
 ******************************************************************/

#include <R.h>

#include <stdio.h>
#include <stdlib.h>
 

#define BUFFERSIZE 1024


/*******************************************************************
 *******************************************************************
 **
 ** Structures for dealing with pgf file information
 **
 **
 **
 *******************************************************************
 ******************************************************************/

/*******************************************************************
 *******************************************************************
 **
 ** Starting off with the headers
 **
 *******************************************************************
 ******************************************************************/

/* integer (from 0 to n-1) indicates position of header (-1 means header is not present) */

typedef struct{
  int probeset_id;
  int type;
  int probeset_name;
} header_0;

/* integer (from 0 to n-1) indicates position of header (-1 means header is not present) */

typedef struct{
  int atom_id;
  int type;
  int exon_position;
} header_1;

/* integer (from 0 to n-1) indicates position of header (-1 means header is not present) */

typedef struct{
  int probe_id;
  int type;
  int gc_count;
  int probe_length;
  int interrogation_position;
  int probe_sequence;
} header_2;



typedef struct{
  char **chip_type;
  int n_chip_type;
  char *lib_set_name;
  char *lib_set_version;
  char *pgf_format_version;
  char *header0_str;
  header_0 *header0;
  char *header1_str;
  header_1 *header1;
  char *header2_str;
  header_2 *header2;
  char *create_date;
  char *guid;
  char **other_headers_keys;
  char **other_headers_values;
  int n_other_headers;
} pgf_headers;


/********************************************************************
 *******************************************************************
 **
 ** Structures for dealing with data stored at the probelevel
 **
 **
 *******************************************************************
 *******************************************************************/

typedef struct{
  
  int probe_id;
  char *type;
  int gc_count;
  int probe_length;
  int interrogation_position;
  char *probe_sequence;
  struct probe_list_node *next;
} probe_list_node;


typedef struct{
  int n_probes;
  probe_list_node *first;
} probe_list_header;



/********************************************************************
 *******************************************************************
 **
 ** Structures for dealing with data stored at the atom level
 **
 **
 *******************************************************************
 *******************************************************************/

typedef struct{
  int atom_id;
  char *type;
  char *exon_position;
  probe_list_header *probes;
  struct atom_list_node *next;
} atom_list_node;


typedef struct{
  int n_atoms;
  atom_list_node *first;
} atom_list_header;



/*******************************************************************
 *******************************************************************
 **
 ** Structures for dealing with data as stored at the probeset level
 **
 **
 **
 *******************************************************************
 *******************************************************************/

typedef struct probeset_list_node *node_pointer;


typedef struct{
  int probeset_id;
  char *type;
  char *probeset_name;

  atom_list_header *atoms;
  
  struct probeset_list_node *next;
} probeset_list_node;



typedef struct{

  int n_probesets;

  probeset_list_node *first;
  probeset_list_node *current;
  probeset_list_node *last;
} probeset_list_header;



/*******************************************************************
 *******************************************************************
 **
 ** Structure for storing pgf file (after it is read from file)
 **
 *******************************************************************
 ******************************************************************/


typedef struct{
  pgf_headers *headers;
  probeset_list_header *probesets;
} pgf_file;


/*******************************************************************
 *******************************************************************
 **
 **
 ** Code for splitting a string into a series of tokens
 **
 **
 *******************************************************************
 *******************************************************************/


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

#if USE_PTHREADS  
  char *tmp_pointer;
#endif  
  int i=0;

  char *current_token;
  tokenset *my_tokenset = Calloc(1,tokenset);
  my_tokenset->n=0;
  
  my_tokenset->tokens = NULL;
#if USE_PTHREADS
  current_token = strtok_r(str,delimiters,&tmp_pointer);
#else
  current_token = strtok(str,delimiters);
#endif
  while (current_token != NULL){
    my_tokenset->n++;
    my_tokenset->tokens = Realloc(my_tokenset->tokens,my_tokenset->n,char*);
    my_tokenset->tokens[i] = Calloc(strlen(current_token)+1,char);
    strcpy(my_tokenset->tokens[i],current_token);
    my_tokenset->tokens[i][(strlen(current_token))] = '\0';
    i++;
#if USE_PTHREADS
    current_token = strtok_r(NULL,delimiters,&tmp_pointer);
#else
    current_token = strtok(NULL,delimiters);
#endif
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


/*******************************************************************
 *******************************************************************
 **
 ** Code for Reading from file
 **
 *******************************************************************
 *******************************************************************/



/****************************************************************
 **
 ** void ReadFileLine(char *buffer, int buffersize, FILE *currentFile)
 **
 ** char *buffer  - place to store contents of the line
 ** int buffersize - size of the buffer
 ** FILE *currentFile - FILE pointer to an opened CEL file.
 **
 ** Read a line from a file, into a buffer of specified size.
 ** otherwise die.
 **
 ***************************************************************/

static int ReadFileLine(char *buffer, int buffersize, FILE *currentFile){
  if (fgets(buffer, buffersize, currentFile) == NULL){
    return 0;
    //error("End of file reached unexpectedly. Perhaps this file is truncated.\n");
  }  
  return 1;
}  




/****************************************************************
 **
 ** Code for identifying what type of information is stored in 
 ** the current line
 **
 ***************************************************************/

/****************************************************************
 **
 ** static int IsHeaderLine(char *buffer)
 **
 ** char *buffer - contains line to evaluate
 **
 ** Checks whether supplied line is a header line (ie starts with #%)
 **
 ** return 1 (ie true) if header line. 0 otherwise
 **
 ***************************************************************/


static int IsHeaderLine(char *buffer){

  if (strncmp("#%",buffer,2) == 0){
    return 1;
  }
  return 0;
}

/****************************************************************
 **
 ** static int IsHeaderLine(char *buffer)
 **
 ** char *buffer - contains line to evaluate
 **
 ** Checks whether supplied line is a comment line (ie starts with #)
 **
 **
 ***************************************************************/

static int IsCommentLine(char *buffer){
  if (strncmp("#",buffer,1) == 0){
    return 1;
  }
  return 0;
}


/*****************************************************************
 **
 ** static int IsLevel2(char *buffer)
 **
 ** char *buffer - contains line to evaluate
 **
 ** checks whether supplied line begins with two tab characters it \t\t
 **
 ** Return 1 if true, 0 otherwise
 **
 ***************************************************************/

static int IsLevel2(char *buffer){
  if (strncmp("\t\t",buffer,2) == 0){
    return 1;
  }
  return 0;
}



/*****************************************************************
 **
 ** static int IsLevel1(char *buffer)
 **
 ** char *buffer - contains line to evaluate
 **
 ** checks whether supplied line begins with a single tab characters it \t
 **
 ** Return 1 if true, 0 otherwise
 **
 ***************************************************************/

static int IsLevel1(char *buffer){
  if (strncmp("\t",buffer,1) == 0){
    if (strncmp("\t\t",buffer,2) != 0){
      return 1;
    }
    return 0;
  }
  return 0;
}



/****************************************************************
 ****************************************************************
 **
 ** Code for deallocating or initializing header data structures
 **
 ****************************************************************
 ****************************************************************/

void dealloc_pgf_headers(pgf_headers *header){
  int i;

  if (header->n_chip_type > 0){
    for (i = 0; i < header->n_chip_type; i++){
      Free(header->chip_type[i]);
    }
    Free(header->chip_type);
  }
      
  if (header->lib_set_name != NULL){
    Free(header->lib_set_name);
  }

  if (header->lib_set_version != NULL){
    Free(header->lib_set_version);
  }

  if (header->pgf_format_version != NULL){
    Free(header->pgf_format_version);
  }

  if (header->header0_str != NULL){
    Free(header->header0_str);
    Free(header->header0);
  }
  if (header->header1_str != NULL){
    Free(header->header1_str);
    Free(header->header1);
  }
  if (header->header2_str != NULL){
    Free(header->header2_str);
    Free(header->header2);
  }
   
  if (header->create_date != NULL){
    Free(header->create_date);
  }

  if (header->guid != NULL){
    Free(header->guid);
  }

  if (header->n_other_headers > 0){
    for (i = 0; i < header->n_other_headers; i++){
      Free(header->other_headers_keys[i]);
      Free(header->other_headers_values[i]);
    }
    Free(header->other_headers_keys);
    Free(header->other_headers_values);
  }
}


void dealloc_probes(probe_list_header *probes){

  probe_list_node *temp_node;

  if (probes->first != NULL){
    temp_node = probes->first;
    while (temp_node != NULL){
      probes->first = (probe_list_node *)temp_node->next;
      if (temp_node->type != NULL){
	Free(temp_node->type);
      }
      if (temp_node->probe_sequence != NULL){
	Free(temp_node->probe_sequence);
      }
      Free(temp_node);
      temp_node = probes->first;
    }
    

  }
}



void dealloc_atoms(atom_list_header *atoms){

  atom_list_node *temp_node;

  if (atoms->first != NULL){
    temp_node = atoms->first;
    while (temp_node != NULL){
      atoms->first = (atom_list_node *)temp_node->next;
      if (temp_node->type != NULL){
	Free(temp_node->type);
      }
      if (temp_node->exon_position != NULL){
	Free(temp_node->exon_position);
      }
      if (temp_node->probes != NULL){
	dealloc_probes(temp_node->probes);
	Free(temp_node->probes);
      }

      Free(temp_node);
      temp_node = atoms->first;
    }
    

  }

  

}


void dealloc_pgf_probesets(probeset_list_header *probesets){

  probeset_list_node *temp_node;

  if (probesets->first != NULL){
    temp_node = probesets->first;
    while (temp_node != NULL){
      probesets->first = (probeset_list_node *)temp_node->next;
      
      if (temp_node->type != NULL){
	Free(temp_node->type);
      }
      if (temp_node->probeset_name != NULL){
	Free(temp_node->probeset_name);
      }
      
      if (temp_node->atoms != NULL){
	dealloc_atoms(temp_node->atoms);
	Free(temp_node->atoms);
      }

      Free(temp_node);
      temp_node = probesets->first;
    }
  }

}



void dealloc_pgf_file(pgf_file* my_pgf){


  if (my_pgf->headers != NULL){
    dealloc_pgf_headers(my_pgf->headers);
    Free(my_pgf->headers);
  }

  
  if (my_pgf->probesets !=NULL){
    dealloc_pgf_probesets(my_pgf->probesets);
    Free(my_pgf->probesets);
  }


}


void initialize_pgf_header(pgf_headers *header){

  header->chip_type = NULL;
  header->n_chip_type = 0;
  
  header->lib_set_name= NULL;
  header->lib_set_version= NULL;
  header->pgf_format_version= NULL;
  header->header0_str= NULL;
  header->header0= NULL;
  header->header1_str= NULL;
  header->header1= NULL;
  header->header2_str= NULL;
  header->header2= NULL;
  header->create_date= NULL;
  header->guid= NULL;
  header->other_headers_keys= NULL;
  header->other_headers_values= NULL;
  header->n_other_headers=0;
}

/****************************************************************
 ****************************************************************
 **
 ** Code for figuring out column ordering 
 ** 
 ****************************************************************
 ***************************************************************/


static void determine_order_header0(char *header_str, header_0 *header0){

  tokenset *cur_tokenset;
  int i;
  char *temp_str = Calloc(strlen(header_str) +1, char);


  strcpy(temp_str,header_str);

  header0->probeset_id = -1;
  header0->type = -1;
  header0->probeset_name = -1;
  
  cur_tokenset = tokenize(temp_str,"\t\r\n");
  
  for (i=0; i < tokenset_size(cur_tokenset); i++){
    if (strcmp(get_token(cur_tokenset,i),"probeset_id")==0){
      header0->probeset_id = i;
    } else if (strcmp(get_token(cur_tokenset,i),"type")==0){
      header0->type = i;
    } else if (strcmp(get_token(cur_tokenset,i),"type")==0){
      header0->probeset_name = i;
    }
  }
  delete_tokens(cur_tokenset);

  Free(temp_str);

}

static void determine_order_header1(char *header_str, header_1 *header1){

  tokenset *cur_tokenset;
  int i;
  char *temp_str = Calloc(strlen(header_str) +1, char);


  strcpy(temp_str,header_str);

  header1->atom_id = -1;
  header1->type = -1;
  header1->exon_position = -1;
  
  cur_tokenset = tokenize(temp_str,"\t\r\n");
  
  for (i=0; i < tokenset_size(cur_tokenset); i++){
    if (strcmp(get_token(cur_tokenset,i),"atom_id")==0){
      header1->atom_id = i;
    } else if (strcmp(get_token(cur_tokenset,i),"type")==0){
      header1->type = i;
    } else if (strcmp(get_token(cur_tokenset,i),"exon_position")==0){
      header1->exon_position = i;
    }
  }
  delete_tokens(cur_tokenset);

  Free(temp_str);

}

static void determine_order_header2(char *header_str, header_2 *header2){

  tokenset *cur_tokenset;
  int i;
  char *temp_str = Calloc(strlen(header_str) +1, char);


  strcpy(temp_str,header_str);

  header2->probe_id = -1;
  header2->type = -1;
  header2->gc_count = -1;
  header2->probe_length = -1;
  header2->interrogation_position = -1;
  header2->probe_sequence = -1;
  
  cur_tokenset = tokenize(temp_str,"\t\r\n");
  
  for (i=0; i < tokenset_size(cur_tokenset); i++){
    if (strcmp(get_token(cur_tokenset,i),"probe_id")==0){
      header2->probe_id = i;
    } else if (strcmp(get_token(cur_tokenset,i),"type")==0){
      header2->type = i;
    } else if (strcmp(get_token(cur_tokenset,i),"gc_count")==0){
      header2->gc_count = i;
    } else if (strcmp(get_token(cur_tokenset,i),"probe_length")==0){
      header2->probe_length = i;
    } else if (strcmp(get_token(cur_tokenset,i),"interrogation_position")==0){
      header2->interrogation_position = i;
    } else if (strcmp(get_token(cur_tokenset,i),"probe_sequence")==0){
      header2->probe_sequence = i;
    }
 
  }
  delete_tokens(cur_tokenset);

  Free(temp_str);

}


/****************************************************************
 **
 ** Validate that required headers are present in file. 
 **
 ** Return 0 if an expected header is not present.
 ** Returns 1 otherwise (ie everything looks fine)
 **
 ***************************************************************/

static int validate_pgf_header(pgf_headers *header){


  /* check that required headers are all there (have been read) */
  if (header->chip_type == NULL)
    return 0;

  if (header->lib_set_name == NULL)
    return 0;

  if (header->lib_set_version == NULL)
    return 0;

  if (header->pgf_format_version == NULL)
    return 0;

  if (header->header0_str == NULL)
    return 0;

  if (header->header1_str == NULL)
    return 0;
 
  if (header->header2_str == NULL)
    return 0;
      

  /* Check that format version is 1.0 (only supported version) */

  if (strcmp( header->pgf_format_version,"1.0") != 0){
    return 0;
  }

  /* check that header0, header1, header2 (ie the three levels of headers) have required fields */

  if (header->header0->probeset_id == -1)
    return 0;

  if (header->header1->atom_id == -1)
    return 0;

  if (header->header2->probe_id == -1)
    return 0;

  if (header->header2->type == -1)
    return 0;

  return 1;
}




/****************************************************************
 ****************************************************************
 **
 ** Code for actually reading from the file
 ** 
 ****************************************************************
 ***************************************************************/

static FILE *open_pgf_file(const char *filename){
  
  const char *mode = "r";
  FILE *currentFile = NULL; 
  
  currentFile = fopen(filename,mode);
  if (currentFile == NULL){
     error("Could not open file %s", filename);
  }   
  return currentFile;

}

/****************************************************************
 **
 ** Reading the header
 **
 ***************************************************************/

void read_pgf_header(FILE *cur_file, char *buffer, pgf_headers *header){


  tokenset *cur_tokenset;
  int i;
  char *temp_str;
  
  
  initialize_pgf_header(header);
  do {
    ReadFileLine(buffer, 1024, cur_file);
    /* Rprintf("%s\n",buffer); */
    if (IsHeaderLine(buffer)){
      cur_tokenset = tokenize(&buffer[2],"=\r\n");
      /* hopefully token 0 is Key 
	 and token 1 is Value */
      /*   Rprintf("Key is: %s\n",get_token(cur_tokenset,0));
	   Rprintf("Value is: %s\n",get_token(cur_tokenset,1)); */
      /* Decode the Key/Value pair */
      if (strcmp(get_token(cur_tokenset,0),"chip_type") == 0){
	if (header->n_chip_type == 0){
	  header->chip_type = Calloc(1, char *);
	} else {
	  header->chip_type = Realloc(header->chip_type, header->n_chip_type+1, char *);
	}
	temp_str = Calloc(strlen(get_token(cur_tokenset,1))+1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->chip_type[header->n_chip_type] = temp_str;
	header->n_chip_type++;
      } else if (strcmp(get_token(cur_tokenset,0), "lib_set_name") == 0){
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->lib_set_name = temp_str;
      } else if (strcmp(get_token(cur_tokenset,0), "lib_set_version") == 0){
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->lib_set_version = temp_str;
      } else if (strcmp(get_token(cur_tokenset,0), "pgf_format_version") == 0) {
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->pgf_format_version = temp_str;
      } else if (strcmp(get_token(cur_tokenset,0), "header0") == 0) {
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->header0_str = temp_str;
	header->header0 = Calloc(1,header_0);
	determine_order_header0(header->header0_str,header->header0);
      } else if (strcmp(get_token(cur_tokenset,0), "header1") == 0) {
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->header1_str = temp_str;
	header->header1 = Calloc(1,header_1);
	determine_order_header1(header->header1_str,header->header1);
      } else if (strcmp(get_token(cur_tokenset,0), "header2") == 0) {
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->header2_str = temp_str;
	header->header2 = Calloc(1,header_2);
	determine_order_header2(header->header2_str,header->header2);
      } else if (strcmp(get_token(cur_tokenset,0), "create_date") == 0) {
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->create_date = temp_str;
      } else if (strcmp(get_token(cur_tokenset,0), "guid") == 0) {
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->guid = temp_str;
      } else {
	/* not one of the recognised header types */
	if ( header->n_other_headers == 0){
	  header->other_headers_keys = Calloc(1, char *);
	  header->other_headers_values = Calloc(1, char *);
	} else {
	  header->other_headers_keys = Realloc(header->other_headers_keys,header->n_other_headers+1, char *);
	  header->other_headers_values = Realloc(header->other_headers_values,header->n_other_headers+1, char *);
	  header->chip_type = Realloc(header->chip_type, header->n_chip_type+1, char *);
	}
	temp_str = Calloc(strlen(get_token(cur_tokenset,1)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,1));
	header->other_headers_values[header->n_other_headers] = temp_str;
	temp_str = Calloc(strlen(get_token(cur_tokenset,0)) + 1,char);
	strcpy(temp_str,get_token(cur_tokenset,0));
	header->other_headers_keys[header->n_other_headers] = temp_str;
	header->n_other_headers++;

      }
      
      delete_tokens(cur_tokenset);
    }
  } while (IsHeaderLine(buffer));
 
}


/****************************************************************
 **
 ** Reading the probesets/body of the file
 **
 ***************************************************************/

void initialize_probeset_list(probeset_list_header *probeset_list){

  probeset_list->n_probesets = 0;
  probeset_list->first = NULL;
  probeset_list->current = NULL;
  probeset_list->last = NULL;
}



void insert_probe(char *buffer, probe_list_header *probe_list, header_2 *header2){

  char *temp_str;
  tokenset *cur_tokenset;
  probe_list_node *temp_ptr;

  probe_list_node *temp_node = Calloc(1,probe_list_node);

  cur_tokenset = tokenize(buffer,"\t\r\n");
  temp_node->probe_id = atoi(get_token(cur_tokenset,header2->probe_id));

  if (header2->type != -1){
    temp_str = Calloc(strlen(get_token(cur_tokenset,header2->type)) + 1,char);
    strcpy(temp_str,get_token(cur_tokenset,header2->type));
    temp_node->type = temp_str;
  }
  if (header2->gc_count != -1){
    temp_node->gc_count = atoi(get_token(cur_tokenset,header2->gc_count));
  }
  if (header2->probe_length != -1){
    temp_node->probe_length = atoi(get_token(cur_tokenset,header2->probe_length));
  }
  if (header2->interrogation_position != -1){
    temp_node->interrogation_position = atoi(get_token(cur_tokenset,header2->interrogation_position));
  }
  if (header2->probe_sequence != -1){
    temp_str = Calloc(strlen(get_token(cur_tokenset,header2->probe_sequence)) + 1,char);
    strcpy(temp_str,get_token(cur_tokenset,header2->probe_sequence));
    temp_node->probe_sequence = temp_str;
  }
 

  
  temp_node->next = NULL;
  if (probe_list->n_probes == 0){    
    probe_list->first = temp_node;
    probe_list->n_probes = 1;
  } else {
    /* figure out where the end of the list is. Insert there */
    temp_ptr = probe_list->first;
    
    while (temp_ptr->next != NULL){
      temp_ptr = (probe_list_node*)temp_ptr->next;
    }
    temp_ptr->next = (struct probe_list_node*)temp_node;
    probe_list->n_probes++;
  }
  delete_tokens(cur_tokenset);
}


void insert_level2(char *buffer, probeset_list_header *probeset_list, header_2 *header2){

  atom_list_header *current_level1;
  atom_list_node *current_atom;

  if (probeset_list->current == NULL){
    /* Oh Boy, this is a problem no header0 level object to insert into. */
    error("Can not read a level 2 line before seeing a level 0 line. File corrupted?");
  }
  
  if (probeset_list->current->atoms == NULL){
    /* Oh Boy, this is a problem no header1 level object to insert into. */
    error("Can not read a level 2 line before seeing a level 1 line. File corrupted?");
  }

  current_level1 = probeset_list->current->atoms;
  
  current_atom = current_level1->first;

  while (current_atom->next != NULL){
    current_atom = (atom_list_node *)current_atom->next;
  }

  if (current_atom->probes == NULL){
    current_atom->probes = Calloc(1,probe_list_header);
  }
  
  insert_probe(buffer, current_atom->probes, header2);
}





void insert_atom(char *buffer, atom_list_header *atoms_list, header_1 *header1){

  char *temp_str;
  tokenset *cur_tokenset;
  atom_list_node *temp_ptr;

  atom_list_node *temp_node = Calloc(1,atom_list_node);

  cur_tokenset = tokenize(buffer,"\t\r\n");

  temp_node->atom_id = atoi(get_token(cur_tokenset,header1->atom_id));

  if (header1->type != -1){
    temp_str = Calloc(strlen(get_token(cur_tokenset,header1->type)) + 1,char);
    strcpy(temp_str,get_token(cur_tokenset,header1->type));
    temp_node->type = temp_str;
  }
  if (header1->exon_position != -1){
    temp_str = Calloc(strlen(get_token(cur_tokenset,header1->exon_position)) + 1,char);
    strcpy(temp_str,get_token(cur_tokenset,header1->exon_position));
    temp_node->exon_position = temp_str;
  }
  temp_node->probes = NULL;
  temp_node->next = NULL;
  
  if (atoms_list->n_atoms == 0){    
    atoms_list->first = temp_node;
    atoms_list->n_atoms = 1;
  } else {
    /* figure out where the end of the list is. Insert there */
    temp_ptr = (atom_list_node*)atoms_list->first;
    
    while (temp_ptr->next != NULL){
      temp_ptr= (atom_list_node*)temp_ptr->next;
    }
    temp_ptr->next = (struct atom_list_node*)temp_node;
    atoms_list->n_atoms++;
  }
  delete_tokens(cur_tokenset);
}


void insert_level1(char *buffer, probeset_list_header *probeset_list, header_1 *header1){

  probeset_list_node *current_level0;


  if (probeset_list->current == NULL){
    /* Oh Boy, this is a problem no header0 level object to insert into. */
    error("Can not read a level 1 line before seeing a level 0 line. File corrupted?");
  }
  
  current_level0 = probeset_list->current;
  
  if (current_level0->atoms == NULL){
    current_level0->atoms = Calloc(1,atom_list_header);
  }

  /* Now lets insert the data */
  
  insert_atom(buffer, current_level0->atoms, header1);





}




void insert_level0(char *buffer, probeset_list_header *probeset_list, header_0 *header0){

  char *temp_str;
  tokenset *cur_tokenset;
  probeset_list_node *temp_ptr;

  probeset_list_node *temp_node = Calloc(1,probeset_list_node);

  cur_tokenset = tokenize(buffer,"\t\r\n");

  temp_node->probeset_id = atoi(get_token(cur_tokenset,header0->probeset_id));

  if (header0->type != -1){
    temp_str = Calloc(strlen(get_token(cur_tokenset,header0->type)) + 1,char);
    strcpy(temp_str,get_token(cur_tokenset,header0->type));
    temp_node->type = temp_str;
  }
  if (header0->probeset_name != -1){
    temp_str = Calloc(strlen(get_token(cur_tokenset,header0->probeset_name)) + 1,char);
    strcpy(temp_str,get_token(cur_tokenset,header0->probeset_name));
    temp_node->probeset_name = temp_str;
  }
  temp_node->atoms = NULL;
  temp_node->next = NULL;
  
  if (probeset_list->first == NULL){
    probeset_list->first = temp_node;
    probeset_list->current = temp_node;
    probeset_list->last = temp_node; 
    probeset_list->n_probesets = 1;
  } else {
    probeset_list->last->next = (struct probeset_list_node *)temp_node;
    probeset_list->last = temp_node;
    probeset_list->current = temp_node;
    probeset_list->n_probesets++;
  }
  delete_tokens(cur_tokenset);
}


void read_pgf_probesets(FILE *cur_file, char *buffer, probeset_list_header *probeset_list, pgf_headers *header){

  initialize_probeset_list(probeset_list);
  
  insert_level0(buffer, probeset_list, header->header0);
  
  while(ReadFileLine(buffer, 1024, cur_file)){
    if (IsLevel2(buffer)){
      insert_level2(buffer, probeset_list, header->header2);
    } else if (IsLevel1(buffer)){
      insert_level1(buffer, probeset_list, header->header1);
    } else if (IsCommentLine(buffer)){
      /*Ignore */
    } else {
       insert_level0(buffer, probeset_list, header->header0);
    }
  }
}

/****************************************************************
 ****************************************************************
 **
 ** Funtionality for counting probeset types
 **
 ****************************************************************
 ****************************************************************/

typedef struct{
  char *type;
  int count;
} probeset_type_list;



probeset_type_list *pgf_count_probeset_types(pgf_file *my_pgf, int *number){


  probeset_type_list *my_type_list = Calloc(1,probeset_type_list);

  char *cur_type;
  int n;

  /* traverse the probesets. each time examining the probeset type */


  if (my_pgf->probesets != NULL){
    
    if (my_pgf->probesets->first != NULL){
      
      my_pgf->probesets->current = my_pgf->probesets->first;
      
      if (my_pgf->probesets->current->type == NULL){
	my_type_list[0].type = Calloc(5,char);
	strcpy(my_type_list[0].type,"none");
	
      } else {
	my_type_list[0].type = Calloc(strlen(my_pgf->probesets->current->type) + 1,char);
	strcpy(my_type_list[0].type,my_pgf->probesets->current->type);
      }
      my_type_list[0].count = 1;
      *number = 1; /* number of different types seen */
      while (my_pgf->probesets->current->next != NULL){
	my_pgf->probesets->current= my_pgf->probesets->current->next;
	if (my_pgf->probesets->current->type == NULL){
	  cur_type = "none";
	} else {
	  cur_type = my_pgf->probesets->current->type;
	}
	n = 0;
	while (n < *number){
	  if (strcmp(cur_type,my_type_list[n].type) == 0){
	    break;
	  }
	  n++;
	}
	if (n == *number){
	  my_type_list = Realloc(my_type_list,(n+1),probeset_type_list);
	  my_type_list[n].type = Calloc(strlen(cur_type) + 1,char);
	  strcpy(my_type_list[n].type,cur_type);
	  my_type_list[n].count = 1;
	  *number = *number + 1;
  	} else {
	  my_type_list[n].count++;
	}
      }
    }
  }
  return  my_type_list;
}


void dealloc_probeset_type_list(probeset_type_list *my_type_list, int length){

  int i;

  for (i = 0; i < length; i++){
    Free(my_type_list[i].type);
  }

  Free(my_type_list);

}

/****************************************************************
 ****************************************************************
 **
 ** Functionality for testing the parsers (from R .C interface)
 **
 ****************************************************************
 ****************************************************************/

void read_pgf_file(char **filename){

  FILE *cur_file;
  pgf_file my_pgf;
  char *buffer = Calloc(1024, char);
  probeset_type_list *my_probeset_types;
  int ntypes;
  
  cur_file = open_pgf_file(filename[0]);
  
  my_pgf.headers = Calloc(1, pgf_headers);
  my_pgf.probesets = Calloc(1, probeset_list_header);

  read_pgf_header(cur_file,buffer,my_pgf.headers);
  if (validate_pgf_header(my_pgf.headers)){
    read_pgf_probesets(cur_file, buffer, my_pgf.probesets, my_pgf.headers);
    my_probeset_types = pgf_count_probeset_types(&my_pgf, &ntypes);
    dealloc_probeset_type_list(my_probeset_types, ntypes);
  }
  Free(buffer);
  dealloc_pgf_file(&my_pgf);
  fclose(cur_file);

}
