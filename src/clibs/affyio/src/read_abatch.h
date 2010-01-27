#ifndef READ_ABATCH_H
#define READ_ABATCH_H



/****************************************************************
 **
 ** A structure for holding full header information
 **
 **
 **
 ***************************************************************/

typedef struct{
  char *cdfName;
  int cols;
  int rows;
  int GridCornerULx,GridCornerULy;	/* XY coordinates of the upper left grid corner in pixel coordinates.*/
  int GridCornerURx,GridCornerURy;    	/* XY coordinates of the upper right grid corner in pixel coordinates.*/
  int GridCornerLRx,GridCornerLRy;	/* XY coordinates of the lower right grid corner in pixel coordinates.*/
  int GridCornerLLx,GridCornerLLy;      /* XY coordinates of the lower left grid corner in pixel coordinates.*/ 
  char *DatHeader;
  char *Algorithm;
  char *AlgorithmParameters;
  char *ScanDate;
} detailed_header_info;

/******************************************************************
 **
 ** A "C" level object designed to hold information for a
 ** single CEL file
 **
 ** These should be created using the function
 **
 ** read_cel_file()
 **
 **
 **
 *****************************************************************/

typedef struct{
  detailed_header_info header;
  
  /** these are for storing the intensities, the sds and the number of pixels **/
  double *intensities;
  double *stddev;
  double *npixels;

  /** these are for storing information in the masks and outliers section **/
  
  int nmasks;
  int noutliers;

  short *masks_x, *masks_y;
  short *outliers_x, *outliers_y;

} CEL;

extern CEL *read_cel_file(const char *filename, int read_intensities_only);



#endif
