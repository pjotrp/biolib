#! /bin/sh

list="ASciLib Add_C_Library Add_Perl_Module Add_Python_Module Add_Ruby_Module BioLib_Affymetrix BioLib_Bio++  BioLib_RQTL BioLib_Staden_io_lib BioLib_best_practises BioLib_libsequence  Biolib_Poll CMake GSL Generator Interesting_libraries Main_Page NIX Road_map  SWIG Supported_data_types Mapping_EMBOSS"

for x in $list ; do 
  curl "http://biolib.open-bio.org/wiki/Special:Export/$x" > doc/wiki/$x.wiki
done
curl "http://biolib.open-bio.org/wiki/Special:Statistics" > doc/wiki/Special:Statistics.wiki
