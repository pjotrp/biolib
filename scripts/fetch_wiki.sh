#! /bin/sh

for x in Main_Page Road_map Interesting_libraries BioLib_best_practises Supported_data_types SWIG NIX Add_C_Library Add_Ruby_Module BioLib_Affymetrix CMake ; do 
  curl "http://biolib.open-bio.org/wiki/Special:Export/$x" > doc/wiki/$x.wiki
done
curl "http://biolib.open-bio.org/wiki/Special:Statistics" > doc/wiki/Special:Statistics.wiki
