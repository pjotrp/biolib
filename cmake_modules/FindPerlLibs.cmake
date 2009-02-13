# - Find Perl libraries
#
# This module finds if PERL is installed and determines where the include files
# and libraries are (using the Config module first). It also determines what
# the name of the library is. This code sets the following variables:
#
#  PERL_INCLUDE_PATH = path to where perl.h is found
#  PERL_LIB_PATH     = path where to install modules
#  PERL_SLIB_PATH    = path where to install shared libraries (auto)
#  PERL_EXECUTABLE   = full path to the perl binary
#

# ---- find the perl interpreter on the PATH
FIND_PROGRAM(PERL_EXECUTABLE perl)

IF (NOT PERL_EXECUTABLE)
  FIND_PROGRAM(PERL_EXECUTABLE
  NAMES perl
  PATHS
  /usr/bin
  /usr/local/bin
  /opt/local/bin
  )
ELSE (NOT PERL_EXECUTABLE)
  message("Found Perl on PATH")
ENDIF (NOT PERL_EXECUTABLE)

message(STATUS "PERL_EXECUTABLE=${PERL_EXECUTABLE}")

IF(PERL_EXECUTABLE)
  EXECUTE_PROCESS(COMMAND ${PERL_EXECUTABLE} -MConfig -e "print \$Config{version}" OUTPUT_VARIABLE PVERSION)
  EXECUTE_PROCESS(COMMAND ${PERL_EXECUTABLE} -MConfig -e "print \$Config{archname}" OUTPUT_VARIABLE PARCH)
  EXECUTE_PROCESS(COMMAND ${PERL_EXECUTABLE} -MConfig -e "print \$Config{archlib}" OUTPUT_VARIABLE PARCHLIB)
  EXECUTE_PROCESS(COMMAND ${PERL_EXECUTABLE} -MConfig -e "print \$Config{sitearch}" OUTPUT_VARIABLE PSITEARCH)
  EXECUTE_PROCESS(COMMAND ${PERL_EXECUTABLE} -MConfig -e "print \$Config{libperl}" OUTPUT_VARIABLE PLIBPERL)

MESSAGE(STATUS "PLIBPERL=${PLIBPERL}")
  # ---- Find perl.h and set PERL_INCLUDE_PATH
  SET(PERL_POSSIBLE_INCLUDE_PATHS
	        ${PARCHLIB}
					/usr/lib/perl5/${PVERSION}/${PARCH}/CORE
					/usr/lib/perl/${PVERSION}/${PARCH}/CORE
					/usr/lib/perl5/${PVERSION}/CORE
					/usr/lib/perl/${PVERSION}/CORE
					/usr/lib/perl5/5.8/CORE
					/usr/lib/perl/5.8/CORE
					/opt/local/lib/perl5/${PVERSION}/${PARCH}/CORE
					/opt/local/lib/perl/${PVERSION}/${PARCH}/CORE
					/opt/local/lib/perl5/${PVERSION}/CORE
					/opt/local/lib/perl/${PVERSION}/CORE
  )

	FIND_PATH(PERL_INCLUDE_PATH perl.h  ${PERL_POSSIBLE_INCLUDE_PATHS})
	GET_FILENAME_COMPONENT(PERL_LIB_PATH ${PERL_INCLUDE_PATH} PATH)
					
	# ---- Find location for installing shared libraries FIXME!
  SET(PERL_LIB_PATH ${PSITEARCH})  
  SET(PERL_SLIB_PATH ${PSITEARCH})  

  FIND_FILE(PERLLIB_LIBRARY ${PLIBPERL} 
		${PERL_POSSIBLE_INCLUDE_PATHS}
    ${NIX_LIB_PATH} 
	  /lib
	  /usr/lib
  )
  MESSAGE("PERLLIB_LIBRARY=${PERLLIB_LIBRARY}")

  SET(PERL_LIBRARY ${PERLLIB_LIBRARY})  
ENDIF(PERL_EXECUTABLE)

message(STATUS "PERL_INCLUDE_PATH=${PERL_INCLUDE_PATH}")
message(STATUS "PERL_LIB_PATH=${PERL_LIB_PATH}")
message(STATUS "PERL_SLIB_PATH=${PERL_SLIB_PATH}")
message(STATUS "PERL_LIBRARY=${PERL_LIBRARY}")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PERL DEFAULT_MSG PERL_INCLUDE_PATH PERL_LIB_PATH PERL_SLIB_PATH PERL_LIBRARY)

MARK_AS_ADVANCED(
  PERL_INCLUDE_PATH
  PERL_EXECUTABLE
  PERL_LIB_PATH
  PERL_SLIB_PATH
	PERL_LIBRARY
  )
