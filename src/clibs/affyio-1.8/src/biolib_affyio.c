/*! BIOLIB 'C' interface to affyio - for linking against the Bio* languages
 *
 * Author: Pjotr Prins 2008
 */

#include <stdlib.h>
#include <string.h>
#include <R.h>  // For R's Free function only
#include <biolib_affyio.h>

/*!
 * Open a cel file using the Affyio library and return a pointer to a CELOBJECT,
 * which maintains state keeping track of the opened CEL data. The full array
 * data gets stored in memory - including stddev, npixels, masks and outliers. 
 *
 * Use the direct celfile_methods instead, for more effecient memory usage.
 *
 * @param celfilename points to a valid Affy CEL file (or .gz edition)
 *
 * @return pointer to CELOBJECT
 * 
 * @see close_celfile
 * @see cel_intensities
 * @see cel_stddev
 * @see celfile_intensities
 * @see open_cdffile
 */

CELOBJECT *open_celfile(const char *celfilename)
{
  CELOBJECT *celobject = (CELOBJECT *)malloc(sizeof(CELOBJECT));
  if (celobject) {
    memset(celobject,0,sizeof(CELOBJECT));
    strncpy(celobject->id,"[CEL]",6);
    celobject->cel = read_cel_file(celfilename, 1);
  }
  return celobject;
}

/**
 * Close a CELOBJECT opened with open_celfile and frees up RAM
 *
 * @param object
 *
 */

void close_celfile(CELOBJECT *object)
{
  CEL *cel = object->cel;

  Free(cel->header.cdfName);
  Free(cel->header.DatHeader);
  Free(cel->header.Algorithm);
  Free(cel->header.AlgorithmParameters);
  
  
  Free(cel->intensities);
  Free(cel->stddev);
  Free(cel->npixels);

  Free(cel->masks_x);
  Free(cel->masks_y);
  Free(cel->outliers_x);
  Free(cel->outliers_y);
  
  Free(cel);

  if (object->masks != NULL) { free(object->masks); }
  if (object->outliers != NULL) { free(object->outliers); }
  free(object);
}

/*! @return number of columns on the chip */

unsigned long cel_num_cols(CELOBJECT *object)
{
  return object->cel->header.cols;
}

/*! @return number of rows on the chip */

unsigned long cel_num_rows(CELOBJECT *object)
{
  return object->cel->header.rows;
}

/*! @return number of masked probes */

unsigned long cel_num_masks(CELOBJECT *object)
{
  return object->cel->nmasks*2;
}

/*! @return number of outliers */

unsigned long cel_num_outliers(CELOBJECT *object)
{
  return object->cel->noutliers*2;
}


/*! @return number of cells (probes) - [INTENSITY]->NumberCells (rows*cols) */

unsigned long cel_size(CELOBJECT *object)
{
  return object->cel->header.rows * object->cel->header.cols;
}

/*! @return number of intensities (probes) */

unsigned long cel_num_intensities(CELOBJECT *object)
{
  return object->cel->header.rows * object->cel->header.cols;
}

/*! 
 * @parameter index of cel/probe 
 * @return an intensity value 
 * @see cel_pm
 */

double cel_intensity(CELOBJECT *object, unsigned long index)
{
  return object->cel->intensities[index];
}

/*! 
 * @parameter x pos on chip
 * @parameter y pos on chip
 * @return an intensity value 
 * @see cel_pm
 */

double cel_intensity_xy(CELOBJECT *object, unsigned long x, unsigned long y)
{
  return object->cel->intensities[y*cel_num_rows(object)+x];
}

/*! @return a double array to the cel/probe intensities 
 * @see cel_pm
 */

double *cel_intensities(CELOBJECT *object)
{
  return object->cel->intensities;
}

/*! @return the stddev for the cel/probe */

double cel_stddev(CELOBJECT *object, unsigned long index)
{
  return object->cel->stddev[index];
}

/*! @return a double array to the stddev */

double *cel_stddevs(CELOBJECT *object)
{
  return object->cel->stddev;
}

/*! 
 * @param index is the nth item in the mask list
 * @return the cel/probe mask index 
 * @see cel_num_masks
 */

unsigned int cel_mask(CELOBJECT *object, unsigned long index)
{
  CEL *cel = object->cel;
  if (!object->masks) {
    // initialize
    object->masks = malloc(cel->nmasks*2*sizeof(short));
    int i;
    for (i=0; i < cel->nmasks; i++){
      object->masks[i] = (int)cel->masks_x[i];
      object->masks[cel->nmasks + i] = (int)cel->masks_y[i];
    }
  }
  return object->masks[index];
}

/*!
 * @param index is the nth item in the outlier list
 * @return the outlier cel/probe index
 * @see cel_num_outliers
 */
unsigned int cel_outlier(CELOBJECT *object, unsigned long index)
{
  CEL *cel = object->cel;
  if (!object->outliers) {
    // initialize
    object->outliers = malloc(cel->noutliers*2*sizeof(short));
    int i;
    for (i=0; i < cel->noutliers; i++){
      object->outliers[i] = (int)cel->outliers_x[i];
      object->outliers[cel->noutliers + i] = (int)cel->outliers_y[i];
    }
  }
  return object->outliers[index];
}

/* ========================================================================= */

static void cdf_alloc_probesets(CDFOBJECT *cdfobject)
{
  cdfobject->probeset = malloc(sizeof(CDFPROBESET)*cdf_num_probesets(cdfobject)); 
  memset(cdfobject->probeset,0,sizeof(CDFPROBESET));
}

/*
 * Fill the structures that keep track of probesets and probes
 */

static void cdf_calc_text_probe_refs(CDFOBJECT *cdfobject)
{
  cdf_text my_cdf;
  memcpy(&my_cdf,&cdfobject->text,sizeof(cdf_text));
  CDFPROBESET *probeset = cdfobject->probeset;
 
  int i,j,k,l;
  for (i=0; i < my_cdf.header.numberofunits; i++) {
    for (j=0; j < my_cdf.units[i].numberblocks; j++) {
      CDFPROBESET *pset = &probeset[i];
      // here we copy the probeset name:
      strncpy(pset->name,my_cdf.units[i].blocks[j].name,sizeof(pset->name)-1);
      // get the number of probes
      int cells = my_cdf.units[i].blocks[j].num_cells;
      pset->isQC = 0;
      pset->pm_num = cells/2;
      pset->mm_num = cells/2;
      pset->pm = malloc(sizeof(CDFPROBE)*pset->pm_num);
      pset->mm = malloc(sizeof(CDFPROBE)*pset->mm_num);
      /*
      // assuming even cells are PM and odd cells are MM
      for (k=0; k < cells/2; k++) {
        CDFPROBE *pm = &pset->pm[k];
        CDFPROBE *mm = &pset->mm[k];
        pm->x = my_cdf.units[i].blocks[j].probes[k*2].x;
        pm->y = my_cdf.units[i].blocks[j].probes[k*2].y;
        mm->x = my_cdf.units[i].blocks[j].probes[k*2+1].x;
        mm->y = my_cdf.units[i].blocks[j].probes[k*2+1].y;
      }
      */
      // assuming PM always sits above an MM cel
      for (k=0; k < cells/2; k++) {
        CDFPROBE *pm = &pset->pm[k];
        CDFPROBE *mm = &pset->mm[k];
        pm->x = my_cdf.units[i].blocks[j].probes[k*2].x;
        pm->y = my_cdf.units[i].blocks[j].probes[k*2].y;
        mm->x = my_cdf.units[i].blocks[j].probes[k*2+1].x;
        mm->y = my_cdf.units[i].blocks[j].probes[k*2+1].y;
        if (pm->x!=mm->x) { error("PM cel does not sit above MM cel"); }
        if (pm->y > mm->y) {
          int swap = pm->y; pm->y = mm->y; mm->y = swap;
        }
      }
    }
  }
}

/*! 
 * Open a cdf file using the Affyio library and return a pointer to a CDFOBJECT,
 * which maintains state keeping track of the opened CDF data. Unlike the Affyio
 * internal representation the Biolib affyio CDF methods represent a unified
 * layout for Affymetrix chips. Basically every probeset can return the name, probe
 * values (PM, MM) and QC. Loading all other information is trivial, as Affyio
 * makes it available - but not implemented here, at this point.
 *
 * @note FIXME: XDA format not tested
 *
 * @param cdffilename points to a valid Affy CDF file (textual or XDA binary)
 *
 * @return pointer to CDFOBJECT
 * 
 * @see close_cdffile
 */

CDFOBJECT *open_cdffile(const char *cdffilename)
{
  CDFOBJECT *cdfobject = (CDFOBJECT *)malloc(sizeof(CDFOBJECT));
  if (cdfobject) {
    memset(cdfobject,0,sizeof(CDFOBJECT));
    strncpy(cdfobject->id,"[CDF]",6);
    if (isTextCDFFile(cdffilename)) {
      cdfobject->isText = 1;
      if (!read_cdf_text(cdffilename, &cdfobject->text)) {
        free(cdfobject);
        cdfobject = NULL;
      }
      else {
        cdfobject->cols = cdfobject->text.header.cols;
        cdfobject->rows = cdfobject->text.header.rows;
        cdf_alloc_probesets(cdfobject);
        cdf_calc_text_probe_refs(cdfobject);
      }
    }
    if (check_cdf_xda(cdffilename)) {
      if (!read_cdf_xda(cdffilename,&cdfobject->xda)) {
        free(cdfobject);
        cdfobject = NULL;
      }
      else {
        cdfobject->cols = cdfobject->xda.header.cols;
        cdfobject->rows = cdfobject->xda.header.rows;
        cdf_alloc_probesets(cdfobject);
      }
    }
  }
  return cdfobject;
}


void close_cdffile(CDFOBJECT *cdfobject)
{
    if (cdfobject) {
      free(cdfobject->probeset);
      if (cdfobject->isText) {
        dealloc_cdf_text(&cdfobject->text);
      }
      else {
        dealloc_cdf_xda(&cdfobject->xda);
      }
    }
}

/*! @return number of probesets (units*blocks) including QC units */

unsigned long cdf_num_probesets(CDFOBJECT *cdfobject)
{
  unsigned long probesets = 0;
  if (cdfobject->isText) {
    probesets = cdfobject->text.header.NumQCUnits;
    int i,j;
    for (i=0; i < cdfobject->text.header.numberofunits; i++) {
      probesets += cdfobject->text.units[i].numberblocks;
    }
  }
  else {
    probesets = cdfobject->xda.header.n_units +
                cdfobject->xda.header.n_qc_units;
  }
  return probesets;
}

/*!
 * @return CDFPROBESET related to probeset number
 */
CDFPROBESET *cdf_probeset_info(CDFOBJECT *cdfobject, unsigned int probeset)
{
  return &cdfobject->probeset[probeset];
}

/*!
 * @return CDFPROBE related to probe in probeset
 */
CDFPROBE *cdf_pmprobe_info(CDFOBJECT *cdfobject, unsigned int probeset, unsigned int probe)
{
  return &cdfobject->probeset[probeset].pm[probe];
}

/*!
 * @return CDFPROBE related to probe in probeset
 */
CDFPROBE *cdf_mmprobe_info(CDFOBJECT *cdfobject, unsigned int probeset, unsigned int probe)
{
  return &cdfobject->probeset[probeset].mm[probe];
}

/*! 
 * \note FIXME: in progress...
 *
 * @return PM value (perfect match) of the probe number in probeset; -1 on error 
 */

double cel_pm(CELOBJECT *celobject, CDFOBJECT *cdfobject, unsigned int probeset, unsigned int probe)
{
  CDFPROBESET *pset = &cdfobject->probeset[probeset];
  if (pset) {
    CDFPROBE *p = &pset->pm[probe];
    return cel_intensity_xy(celobject, p->x, p->y);
  }
  return -1;
}

/*! 
 * @return MM value (mismatch) of the probe number in probeset; -1 on error 
 */
double cel_mm(CELOBJECT *celobject, CDFOBJECT *cdfobject, unsigned int probeset, unsigned int probe)
{
  CDFPROBESET *pset = &cdfobject->probeset[probeset];
  if (pset) {
    CDFPROBE *p = &pset->mm[probe];
    return cel_intensity_xy(celobject, p->x, p->y);
  }
  return -1;
}

