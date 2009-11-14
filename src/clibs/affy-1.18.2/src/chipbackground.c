/***********************************************************************
 **
 ** file: chipbackground.c
 **
 ** aim: an implementation of the affymetrix background/noise correction
 **      as documented in Affymetrix Statistical Algorithm whitesheet
 **
 ** This implementation is
 ** Copyright (C) 2002-2003   Ben Bolstad
 **
 ** written by: B. M. Bolstad   <bolstad@stat.berkeley.edu>
 ** 
 ** created: Oct 3, 2002
 **
 ** last Modified: Oct 3, 2002
 **
 ** History:
 ** Oct 3, 2002 - Initial version
 ** Oct 26/27, 2002 - generalize the code so that it can deal with an 
 **                arbitrary sized chip, also optimise algorithm so that 
 **                when we call from R with multiple chips, things like distances
 **                are only computed once rather than multiple times.
 **
 ** Oct 28, 2002 - added a couple of 'static' statement when declaring
 **                the functions (you never know...) -- LG
 ** 
 ** Feb 5, 2003 - add in I(x,y) = max(I(x,y),0.5) but commented out for now.
 ** Feb 25, 2003 - fix up some compiler warnings by adding some includes
 **                and remove a declared but unused variable. (gcc -Wall)    
 ** Feb 28, 2003 - Change background to be average of lowest 2% rather than
 **                2% quantile following suggestion by Helene Boucher <bouchel01@borabora.crchul.ulaval.ca>             
 **
 ** Mar 10, 2003 - Check indexing, see that it roams on x =1..ncol  and y=1..nrow. Note
 **                that affy cdf files are on x=0.. ncol-1  and y=0..nrow-1
 ** Mar 6, 2004 - All mallocs/free are now Calloc/Free
 ** Jun 7, 2006 - change distance calculations to be computed using floating point
 **               rather than integer arithmetic.
 **
 ***********************************************************************/
 
#include <R.h>
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdlib.h>
#include <math.h>
#include "rma_common.h"

/************************************************************************
 **
 ** void get_centroids(int rows, int cols, int grid_dim, int *centroidx, int *centroidy)
 **
 ** compute and return the x,y locations of of the centroids of the regions
 **
 ** int rows
 ** int cols
 ** int grid_dim_rows
 ** int grid_dim_cols
 ** int *centroidx - place to store computed centroids
 ** int *centroidy - place to store computed centroids 
 **
 **************************************************************************/

void static get_centroids(int rows, int cols, int grid_dim_rows, int grid_dim_cols, double *centroidx, double *centroidy){
  int i,j;
  double *cuts_x = (double *)Calloc(grid_dim_rows,double);
  double *cuts_y = (double *)Calloc(grid_dim_cols,double);
  
  for (i = 0; i < grid_dim_rows; i++)
    cuts_x[i] = ((double)(i+1)*(double)rows)/(double)grid_dim_rows - (double)rows/(2.0*(double)grid_dim_rows);
  for (j = 0; j < grid_dim_cols; j++)
    cuts_y[j] = ((double)(j+1)*(double)cols)/(double)grid_dim_cols - (double)cols/(2.0*(double)grid_dim_cols);
  
  for (j = 0; j < grid_dim_cols; j++){
    for (i = 0; i < grid_dim_rows; i++){
      centroidx[j*grid_dim_rows + i] = cuts_x[(j*grid_dim_rows + i) / grid_dim_rows]+0.5;
      centroidy[j*grid_dim_rows + i] = cuts_y[(j*grid_dim_rows + i) % grid_dim_rows]+0.5;
    }
  }
  Free(cuts_x);
  Free(cuts_y);
}


void R_get_centroids(int *rows, int *cols, int *grid_dim_rows, int *grid_dim_cols, double *centroidx, double *centroidy){

  get_centroids(*rows,*cols, *grid_dim_rows,*grid_dim_cols, centroidx,centroidy);
}





/**********************************************************************
 **
 ** void get_gridpts(int rows, int cols, int grid_dim, int *gridpt_x, int *gridpt_y)
 **
 ** compute the x and y locations of the "grid points". Grid points are 
 ** (x,y) locations in the interior of the chip which mark out the boundaries
 ** of the grid regions. for a 640 by 640 chip with 16 grid regions the grid points
 ** would be (160,160), (160,320), (160,480), (320,160), (320,320), .......
 **
 ** there would be 9 grid points for a 16 grid region chip.
 **
 ** int rows - size of chip in rows
 ** int cols - size of chip in cols
 ** int grid_dim -  the number of grids (default = 16)
 ** int *gridpt_x - place to store gridpoints
 ** int *gridpt_y - place to store gridpoints
 **
 **********************************************************************/

void static get_gridpts(int rows, int cols, int grid_dim, int *gridpt_x, int *gridpt_y){

  int i;
  int grid_dim1d = (int)sqrt(grid_dim);

  if ((rows == 640) && (cols == 640) && (grid_dim == 16) && (1==0)){
    gridpt_x[0] = 160;
    gridpt_x[1] = 320;
    gridpt_x[2] = 480;
    gridpt_y[0] = 160;
    gridpt_y[1] = 320;
    gridpt_y[2] = 480;
  } else {
    for (i =0; i < grid_dim1d-1; i++){
      gridpt_x[i] =((i+1)*cols)/grid_dim1d;
      gridpt_y[i] =((i+1)*rows)/grid_dim1d;
      /*    printf("%d %d\n", gridpt_x[i],gridpt_y[i]); */
    }
  }
}

/***********************************************************************
 **
 ** find_distances(int x, int y, int rows, int cols, int grid_dim,int *distance)
 **
 ** aim: return a vector of distances squared from a cell location to the 
 **      centroids of rectangular regions.
 **
 ** int x - x location of cell
 ** int y - y location of cell
 ** int rows - size of chip in rows
 ** int cols - size of chip in cols
 ** int grid_dim - the number of grids (default = 16)
 ** int *centroidx - x locations of centroids (length grid_dim)
 ** int *centroidy - y locations of centroids (length grid_dim)
 ** int *distance - vector of grid_dim length to store computed distances
 **
 ** 
 ***********************************************************************/

void static find_distances(int x, int y, int grid_dim,double *centroidx, double *centroidy, double *distance){
  
  int i=0;

  for (i = 0; i < grid_dim; i++){
    distance[i] = (x - centroidx[i])*(x - centroidx[i]) + (y-centroidy[i])*(y-centroidy[i]);
  }
  
}

/*********************************************************************************************
 **
 ** void compute_weights_individual(int x, int y,int rows, int cols,int grid_dim, double *weights, double smooth)
 **
 ** computes the weights for an individual x,y location: to be used in background calculation
 **
 ** int x - x location of cell
 ** int y - y location of cell
 ** int grid_dim - the number of grids (default = 16) 
 ** double *weights - where weights will be stored upon return
 ** double smooth - smooth parameter used in the weights
 **
 **********************************************************************************************/

void static compute_weights_individual(int x, int y, int grid_dim, double *centroidx, double *centroidy, double *weights, double smooth){

  int i=0;
  double *distance = (double *)Calloc(grid_dim,double);

  find_distances(x, y, grid_dim, centroidx, centroidy, distance);

  for (i = 0; i < grid_dim; i++){
    weights[i] =  1.0/((double)distance[i] + smooth);
  }
  Free(distance);
}

/*********************************************************************************************
 **
 ** void compute_weights_individual(int x, int y,int rows, int cols,int grid_dim, double *weights, double smooth)
 **
 ** computes the weights for an individual x,y location: to be used in background calculation
 **
 ** int *x - x location of cells
 ** int *y - y location of cells
 ** int nprobes - number of probes
 ** int grid_dim - the number of grids  
 ** int *centroidx - x and y locations of centroids of sectors.
 ** int *centroidy - 
 ** double *weights - where weights will be stored upon return
 **
 **********************************************************************************************/

void static compute_weights(int *x, int *y, int nprobes, int grid_dim, double *centroidx, double *centroidy, double *weights){

  double smooth = 100.0;
  int i=0;
  
  for (i=0; i < nprobes; i++){
    compute_weights_individual(x[i],y[i], grid_dim, centroidx, centroidy, &weights[i*grid_dim],smooth);
  }

}

/***************************************************************************************
 **
 ** Compute_grids(int *x, int *y, int nprobes, int rows, int cols, int grid_dim,int *whichgrid){
 **
 ** figure out which grid sector each probe is in
 ** 
 ** int *x - x location of probe cell
 ** int *y - y location of probe cell
 ** int nprobes - number of probes (ie length of x and y)
 ** int rows - size of chip in rows
 ** int cols - size of chip in cols
 ** int grid_dim - the number of grids (default = 16)
 ** int *whichgrid - a vector of length nprobes into which we store a number indicating 
 **                  which grid the x,y location falls.
 ** 
 **
 ***************************************************************************************/

void static Compute_grids(int *x, int *y, int rows, int cols, int nprobes, int grid_dim, int *gridpt_x, int *gridpt_y, int *whichgrid){
  int i =0,j=0;  
  int thisgrid = 0,in_range;
  int high, low;
  int grid_dim1d = (int)sqrt(grid_dim);

  if ((rows == 640) && (cols == 640) && (grid_dim == 16) && (1 ==0)){
    for (i=0; i < nprobes; i++){
      if ((x[i] > 0) && (x[i] <= gridpt_x[0])){
	if ((y[i] > 0) && (y[i] <= gridpt_y[0])){
	  whichgrid[i] = 1;
	} else if((y[i] > gridpt_y[0]) && (y[i] <= gridpt_y[1])) {
	  whichgrid[i] = 2;
	} else if ((y[i] > gridpt_y[1]) && (y[i] <= gridpt_y[2])){
	  whichgrid[i] = 3;
	} else {
	  whichgrid[i] = 4;
	}
      } else if((x[i] > gridpt_x[0]) && (x[i] <= gridpt_x[1])) {
	if ((y[i] > 0) && (y[i] <= gridpt_y[0])){
	  whichgrid[i] = 5;
	} else if((y[i] > gridpt_y[0]) && (y[i] <= gridpt_y[1])) {
	  whichgrid[i] = 6;
	} else if ((y[i] > gridpt_y[1]) && (y[i] <= gridpt_y[2])){
	  whichgrid[i] = 7;
	} else {
	  whichgrid[i] = 8;
	}
      } else if ((x[i] > gridpt_x[1]) && (x[i] <= gridpt_x[2])){
        if ((y[i] > 0) && (y[i] <= gridpt_y[0])){
	  whichgrid[i] = 9;
	} else if((y[i] > gridpt_y[0]) && (y[i] <= gridpt_y[1])) {
	  whichgrid[i] = 10;
	} else if ((y[i] > gridpt_y[1]) && (y[i] <= gridpt_y[2])){
	  whichgrid[i] = 11;
	} else {
	  whichgrid[i] = 12;
	}
      } else {
        if ((y[i] > 0) && (y[i] <= gridpt_y[0])){
	  whichgrid[i] = 13;
	} else if((y[i] > gridpt_y[0]) && (y[i] <= gridpt_y[1])) {
	  whichgrid[i] = 14;
	} else if ((y[i] > gridpt_y[1]) && (y[i] <= gridpt_y[2])){
	  whichgrid[i] = 15;
	} else {
	  whichgrid[i] = 16;
	}
      }
    }
  } else {
    for (i =0; i < nprobes; i++){
      in_range = 0;
      low = 0;
      high = gridpt_x[0];
      j =0;
      while (!in_range){
	if ((x[i] > low) && (x[i] <= high)){
	  in_range=1;
	  thisgrid = j*grid_dim1d;
	} else {
	  low = gridpt_x[j];
	  if ((j+2)== grid_dim1d){
	    high = rows;
	  } else {
	    high = gridpt_x[j+1];
	  }
	  j++;
	}
      }
      in_range = 0;
      j = 0;
      low = 0;
      high = gridpt_y[0];
      while (!in_range){
	if ((y[i] > low) && (y[i] <= high)){
	  in_range=1;
	  thisgrid = thisgrid + j +1;
	} else {
	  low = gridpt_y[j];
	  if ((j+2)== grid_dim1d){
	    high = cols;
	  } else {
	    high = gridpt_y[j+1];
	  }
	}
	j++;
	}
      whichgrid[i] = thisgrid;
    }    
  }
}



/****************************************************************************************************
 **
 ** void compute_background_quadrant(double *probeintensity, int nprobes, int grid_dim,int *whichgrid,double *bg_q,double *noise_q)
 **
 ** compute the value of the background in each quadrant, also computes the "noise" as defined in the
 ** Affymetrix Statistical Algorithm Whitepaper.
 **
 ** double *probeintensity - the probeintensities to be corrected
 ** int nprobes - the 
 ** int grid_dim - number of grids
 ** int *whichgrid - which grid does the probe fall in
 ** double *bg_q - should be allocated, on exit contains background values for each quadrant
 ** double *noise_q - should be allocated, on exit contains noise values for each quadrant
 **
 ***************************************************************************************************/

void static compute_background_quadrant(double *probeintensity, int nprobes, int grid_dim, int *whichgrid, double *bg_q,double *noise_q){

  int lower2pc;
  int i=0,j=0;
  int *nprobes_in_sec = (int *)Calloc(grid_dim,int); 
  int *cur_n = (int *)Calloc(grid_dim,int);
  double **data_by_sector =(double **)Calloc(grid_dim,double *);
  double sumx,sumx2;

  for (j = 0; j < grid_dim; j++){  
    nprobes_in_sec[j] = 0;
  }

  for (i = 0; i < nprobes; i++){  
    nprobes_in_sec[whichgrid[i] - 1]++;
  }
  
  for (j =0; j < grid_dim; j++){
    data_by_sector[j] = (double *)Calloc(nprobes_in_sec[j],double);
  }
  
  for (j =0; j < grid_dim; j++){
    cur_n[j] = 0;
  }

  for (i =0; i < nprobes; i++){
    /*    printf("%d %d \n",whichgrid[i] -1, cur_n[whichgrid[i] -1]); */
    data_by_sector[whichgrid[i] -1][cur_n[whichgrid[i] -1]] = probeintensity[i];
    cur_n[whichgrid[i] -1]++;
  }
  
  for (j=0; j < grid_dim; j++){
    qsort(data_by_sector[j],cur_n[j],sizeof(double),(int(*)(const void*, const void*))sort_double);
  }
  
 
  /********* This section was commented out to change from quantile to average (Feb 28, 2003) ************     
  for (j=0; j < grid_dim; j++){
  bg_q[j] = data_by_sector[j][(int)(0.02* nprobes_in_sec[j])];
  }
  ******************************************************************************************************/
  for (j=0; j < grid_dim; j++){
    sumx = 0.0;
    sumx2 = 0.0;
    lower2pc = (int)(0.02* nprobes_in_sec[j]);
    i = 0;
    while (i < lower2pc){
      sumx += data_by_sector[j][i];
      i++;
    }
    sumx = sumx/lower2pc;
    i =0;
    while (i < lower2pc){
      sumx2 += (data_by_sector[j][i] - sumx)*(data_by_sector[j][i]-sumx);
      i++;
    }
    /* the 1 line following changes the b_k to average of lowest2pc */
    bg_q[j] = sumx;
    noise_q[j] = sqrt(sumx2/(lower2pc -1));
  }
 
  for (j =0; j < grid_dim; j++){
    Free(data_by_sector[j]);
  }
  
  Free(nprobes_in_sec);
  Free(cur_n);
  Free(data_by_sector);
}


/*********************************************************************************************
 **
 ** void background_correct(int x, int y,int rows, int cols,int grid_dim, double *Centroid_background)
 **
 ** computes background correction for a probe at cell location (x,y)
 **
 ** int x - x location of cell
 ** int y - y location of cell
 ** int grid_dim - the number of grids (default = 16) 
 ** double *weights - weighting scheme for cell location at (x,y)
 ** double *Centroid_background - Background values for each of the centroid regions
 **
 **********************************************************************************************/


double static background_correct(int x, int y,int grid_dim,double *weights, double *Centroid_background){

  int i;
  double sum = 0.0;
  double sum_weights = 0.0;
  /* double smooth = 100.0; */

  for (i = 0 ; i < grid_dim; i++){
    sum += weights[i]*Centroid_background[i];
    sum_weights += weights[i];
  }

  return(sum/sum_weights);
}



double static max(double one, double two){

  if (one > two){
    return one;
  } else {
    return two;
  }
}

/********************************************************************************************
 **
 ** affy_background_adjust(double *probeintensity,int *x, int *y, int nprobes, int rows, int cols,int grid_dim)
 **
 ** carries out Affymetrixs background correction
 **
 ** double *probeintensity - the probe intensities to be corrected
 ** int *x - x location of probe
 ** int *y - y location of probe
 ** int nprobes - number of probes
 ** int nchips - number of chips
 ** int rows - number of rows on chip
 ** int cols - number of cols on chip
 ** int grid_dim - number of regions in grid.
 **
 ********************************************************************************************/

void static affy_background_adjust(double *probeintensity,int *x, int *y, int nprobes, int nchips, int rows, int cols, int grid_dim){
  int i=0,j=0;
  int *whichgrid = (int *)Calloc(nprobes,int);
  double *bg_q = (double *)Calloc(grid_dim,double);
  double *noise_q = (double *)Calloc(grid_dim,double);
  double *weights = (double *)Calloc(grid_dim*nprobes,double);
  double *centroidx = (double *)Calloc(grid_dim,double);
  double *centroidy = (double *)Calloc(grid_dim,double);
  int *gridpt_x = (int *)Calloc(((int)(sqrt(grid_dim) -1.0)),int);
  int *gridpt_y = (int *)Calloc(((int)(sqrt(grid_dim) -1.0)),int);
  
  get_centroids(rows, cols, (int)sqrt(grid_dim),(int)sqrt(grid_dim), centroidx, centroidy);
  get_gridpts(rows, cols, grid_dim, gridpt_x, gridpt_y);
  compute_weights(x, y, nprobes, grid_dim, centroidx, centroidy, weights);
  Compute_grids(x, y, rows, cols, nprobes, grid_dim, gridpt_x,gridpt_y, whichgrid);
  
  for (j=0; j < nchips; j++){

    compute_background_quadrant(&probeintensity[j*nprobes], nprobes, grid_dim, whichgrid, bg_q,noise_q);
  
    for (i=0; i < nprobes; i++){
      /* probeintensity[j*nprobes + i] =  max(probeintensity[j*nprobes + i],0.5); */
      probeintensity[j*nprobes+ i] = max(probeintensity[j*nprobes + i]-background_correct(x[i], y[i], grid_dim,&weights[grid_dim*i],bg_q),0.5*background_correct(x[i], y[i], grid_dim, &weights[grid_dim*i],noise_q)); 
    }
  }

  Free(gridpt_x);
  Free(gridpt_y);
  Free(centroidx);
  Free(centroidy);
  Free(weights);
  Free(whichgrid);
  Free(noise_q);
  Free(bg_q);
}



/********************************************************************************************
 **
 ** affy_background_adjust_R(double *probeintensity,int *x, int *y, int nprobes, int rows, int cols,int grid_dim)
 **
 ** Wrapper function to be called from R: carries out Affymetrixs background correction
 **
 ** double *probeintensity - the probe intensities to be corrected
 ** int *x - x location of probe
 ** int *y - y location of probe
 ** int *nprobes - number of probes
 ** int *nchips - number of chips
 ** int *rows - number of rows on chip
 ** int *cols - number of cols on chip
 ** int *grid_dim - number of regions in grid.
 **
 ********************************************************************************************/

void affy_background_adjust_R(double *probeintensity,int *x, int *y, int *nprobes, int *nchips, int *rows, int *cols,int *grid_dim){

  affy_background_adjust(probeintensity,x, y, *nprobes, *nchips, *rows, *cols, *grid_dim);

}

