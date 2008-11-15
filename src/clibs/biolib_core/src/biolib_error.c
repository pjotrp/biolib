
#include <stdio.h>
#include <stdarg.h>
#include <biolib_error.h>

void biolib_fatal(const char *template, ...)
{

  va_list ap;
  fprintf (stderr, "BIOLIB FATAL ERROR: ");
  va_start (ap, template);
  vfprintf (stderr, template, ap);
  va_end (ap);
  fprintf (stderr,"\n");

  exit(4);
}
