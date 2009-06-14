
// #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <biolib_R_map.h>

int R_running = false;

/* 
 * Initialize the R environment so we can use Rlib.so
 */

void BioLib_R_Init() {
  char *argv[] = {"BiolibEmbeddedR", "--gui=none", "--silent", "--no-environ" };
  int argc = sizeof(argv)/sizeof(argv[0]);

  if (!R_running) {
    setenv("R_HOME","/usr/lib/R",1);
    Rf_initEmbeddedR(argc, argv);
    R_running = true;
    printf("Initialized embedded R (lib)\n");
  }
}

/*
 * Close down R environment
 */

void BioLib_R_Close() {
  if (R_running) {
    Rf_endEmbeddedR(0);
    R_running = false;
  }
}

