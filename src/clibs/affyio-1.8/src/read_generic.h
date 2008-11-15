
#include <zlib.h>

/******
 ******
 ****** Data Structures
 ******
 ******/



/* File header */

typedef struct{
  uint8_t magic_number;
  uint8_t version;
  int32_t n_data_groups;
  uint32_t first_group_file_pos;
} generic_file_header;




/* An affy generic STRING */

typedef struct{
  int32_t len;
  char *value;
}  ASTRING;

/* An affy generic WSTRING */

typedef struct{
  int32_t len;
  wchar_t *value;
}  AWSTRING;


/* Name Value Type Triplet */

typedef struct{
  AWSTRING name;
  ASTRING value;
  AWSTRING type;
} nvt_triplet;




/* Data Header */

typedef struct generic_data_header *generic_data_header_pointer;

typedef struct{
  ASTRING data_type_id;         /*Stored in file as INT followed by CHAR array */
  ASTRING unique_file_id;       /*See above */
  AWSTRING Date_time;         /*Stored in file as INT followed by WCHAR array */
  AWSTRING locale; 
  int32_t n_name_type_value;
  nvt_triplet *name_type_value;
  int32_t n_parent_headers;
  void **parent_headers;
} generic_data_header;


/* Data Group */

typedef struct {
  
  uint32_t file_position_nextgroup;
  uint32_t file_position_first_data;
  int32_t n_data_sets;
  AWSTRING data_group_name;
} generic_data_group;


/* Dataset */

typedef struct {
  AWSTRING name;
  uint8_t type;
  int32_t size;
} col_nvts_triplet;



typedef struct {
  uint32_t file_pos_first;
  uint32_t file_pos_last;
  AWSTRING data_set_name;
  int32_t n_name_type_value;
  nvt_triplet *name_type_value;
  uint32_t ncols;
  col_nvts_triplet* col_name_type_value;
  uint32_t nrows;
  void **Data;   /* in the docs this is rows */ 
} generic_data_set;




typedef enum{
  
  ASCIITEXT = 1,
  PLAINTEXT = 2,
  UINT8 = 3,
  INT8= 4,
  UINT16 = 5,
  INT16 = 6,
  UINT32 = 7,
  INT32 = 8,
  FLOAT32 = 9

} AffyMIMEtypes;



AffyMIMEtypes determine_MIMETYPE(nvt_triplet triplet);
void *decode_MIME_value(nvt_triplet triplet, AffyMIMEtypes mimetype, void *result, int *size);
char *decode_MIME_value_toASCII(nvt_triplet triplet, AffyMIMEtypes mimetype, void *result, int *size);

nvt_triplet* find_nvt(generic_data_header *data_header,char *name);

int read_generic_file_header(generic_file_header* file_header, FILE *instream);
int read_generic_data_header(generic_data_header *data_header, FILE *instream);
int read_generic_data_group(generic_data_group *data_group, FILE *instream);
int read_generic_data_set(generic_data_set *data_set, FILE *instream);
int read_generic_data_set_rows(generic_data_set *data_set, FILE *instream);

  
void Free_generic_data_header(generic_data_header *header);
void Free_generic_data_group(generic_data_group *data_group);
void Free_generic_data_set(generic_data_set *data_set);


int gzread_generic_file_header(generic_file_header* file_header, gzFile *instream);
int gzread_generic_data_header(generic_data_header *data_header, gzFile *instream);
int gzread_generic_data_group(generic_data_group *data_group,gzFile *instream);
int gzread_generic_data_set(generic_data_set *data_set, gzFile *instream);
int gzread_generic_data_set_rows(generic_data_set *data_set, gzFile *instream);
