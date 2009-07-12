/*! \file biolib_affyio.h 
 *
 * \ingroup affyio
 *
 * BIOLIB 'C' interface to affyio - for linking against the Bio* languages
 *
 * These functions provide access to Affymetrix probe values (CEL files) and
 * the location description of each probe on the trip (CDF files). The underlying
 * library parsing these files is Affyio by Ben Bolstad. The same that is used
 * in R/Bioconductor.
 *
 * De pseudo-code for reading all PM's in a file is:
 *
 * \code
 *   cel = open_cel('celfile')
 *   cdf = open_cdf('cdffile')
 *   for probeset=0 ; probeset < cdf_num_probesets(cdf) do
 *     info = cdf_probeset_info(cdf,probeset)
 *     for probe=0; probe < info.probes ; do
 *       print cel_pm(cel,cdf,probeset,probe)
 * \endcode
 *
 * \author Pjotr Prins 2008
 *
 * See the BioLib API or biolib_affyio.c for method descriptions. Some implementation
 * info is available in ./src/clibs/affyio-ver/README_BIOLIB.
 *
 * @see open_celfile
 * @see open_cdffile
 *
 */

/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BIOLIB
  #include <biolib_R_map.h>
#endif
#include <read_abatch.h>
#include <read_cdf.h>

/*! State object - keeps track of the opened CEL file */
typedef struct {
  /// Should be '[CEL]'
  char id[8];
  /// Points to CEL array
  CEL *cel;
  /// Masked indices
  short *masks;
  /// Outlier indices
  short *outliers;
} CELOBJECT;

CELOBJECT *open_celfile(const char *celfilename);
void close_celfile(CELOBJECT *object);
unsigned long cel_num_cols(CELOBJECT *object);
unsigned long cel_num_rows(CELOBJECT *object);
unsigned long cel_size(CELOBJECT *object);
unsigned long cel_num_intensities(CELOBJECT *object);
unsigned long cel_num_masks(CELOBJECT *object);
unsigned long cel_num_outliers(CELOBJECT *object);
double cel_intensity(CELOBJECT *object, unsigned long index);
double cel_intensity_xy(CELOBJECT *object, unsigned long x, unsigned long y);
double *cel_intensities(CELOBJECT *object);
double cel_stddev(CELOBJECT *object, unsigned long index);
double *cel_stddevs(CELOBJECT *object);
unsigned int cel_mask(CELOBJECT *object, unsigned long index);
unsigned int cel_outlier(CELOBJECT *object, unsigned long index);

/*! Probe description */
typedef struct {
  /// x coordinate on chip
  unsigned int x;
  /// y coordinate on chip
  unsigned int y;
  // unsigned int id; (unused - same as probeset name)
} CDFPROBE;

/*! Probeset description */
typedef struct {
  /// Is quality control?
  int isQC;
  /// Number of pm probes
  unsigned int pm_num;
  /// Number of mm probes
  unsigned int mm_num;
  /// pm index array
  CDFPROBE *pm;
  /// mm index array (when available)
  CDFPROBE *mm;
  /// Name of probeset
  char name[64];
} CDFPROBESET;

/*! State object - keeps track of opened CDF file */
typedef struct {
  /// Should be '[CDF]'
  char id[8];
  /// Is this a textual file?
  int isText;
  /// Affyio internal reference
  cdf_text text;
  /// Affyio internal reference
  cdf_xda xda;
  /// Chip cols
  unsigned int cols;
  /// Chip rows
  unsigned int rows;
  /// Pointer to probeset info array
  CDFPROBESET *probeset;
} CDFOBJECT;

CDFOBJECT *open_cdffile(const char *cdffilename);
void close_cdffile(CDFOBJECT *cdfobject);
unsigned long cdf_num_probesets(CDFOBJECT *cdfobject);
CDFPROBESET *cdf_probeset_info(CDFOBJECT *cdfobject, unsigned int probeset);
CDFPROBE *cdf_pmprobe_info(CDFOBJECT *cdfobject, unsigned int probeset, unsigned int probe);
CDFPROBE *cdf_mmprobe_info(CDFOBJECT *cdfobject, unsigned int probeset, unsigned int probe);
double cel_pm(CELOBJECT *celobject, CDFOBJECT *cdfobject, unsigned int probeset, unsigned int probe);
double cel_mm(CELOBJECT *celobject, CDFOBJECT *cdfobject, unsigned int probeset, unsigned int probe);

#ifdef __cplusplus
}
#endif

/*@}*/
