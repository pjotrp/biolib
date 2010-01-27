/*****************************************************************
 ** 
 ** This file contains the record definitions for the CDF files. 
 ** They come in two formats (textual and binary). The first set
 ** represents the textual form (starting with cdf_text_..
 ** 
 ******************************************************************/

/*****************************************************************
 ** Textual CDF formats
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




// int check_xda_file(const char *filename);
int isTextCDFFile(const char *filename);
int read_cdf_text(const char *filename, cdf_text *mycdf);
void dealloc_cdf_text(cdf_text *my_cdf);
int read_cdf_xda(const char *filename,cdf_xda *my_cdf);
void dealloc_cdf_xda(cdf_xda *my_cdf);

