#ifndef READ_CELFILE_GENERIC_H
#define READ_CELFILE_GENERIC_H

#include "read_abatch.h"

int isGenericCelFile(const char *filename);
char *generic_get_header_info(const char *filename, int *dim1, int *dim2);
void generic_get_detailed_header_info(const char *filename, detailed_header_info *header_info);
int read_genericcel_file_intensities(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows);
int check_generic_cel_file(const char *filename, const char *ref_cdfName, int ref_dim_1, int ref_dim_2);
int read_genericcel_file_stddev(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows);
int read_genericcel_file_npixels(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows);
void generic_get_masks_outliers(const char *filename, int *nmasks, short **masks_x, short **masks_y, int *noutliers, short **outliers_x, short **outliers_y);
void generic_apply_masks(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows, int rm_mask, int rm_outliers);



int isgzGenericCelFile(const char *filename);
char *gzgeneric_get_header_info(const char *filename, int *dim1, int *dim2);
void gzgeneric_get_detailed_header_info(const char *filename, detailed_header_info *header_info);
int gzread_genericcel_file_intensities(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows);
int check_gzgeneric_cel_file(const char *filename, const char *ref_cdfName, int ref_dim_1, int ref_dim_2);
int gzread_genericcel_file_stddev(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows);
int gzread_genericcel_file_npixels(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows);
void gzgeneric_get_masks_outliers(const char *filename, int *nmasks, short **masks_x, short **masks_y, int *noutliers, short **outliers_x, short **outliers_y);
void gzgeneric_apply_masks(const char *filename, double *intensity, int chip_num, int rows, int cols,int chip_dim_rows, int rm_mask, int rm_outliers);


#endif
