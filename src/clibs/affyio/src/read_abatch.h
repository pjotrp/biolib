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


#endif
