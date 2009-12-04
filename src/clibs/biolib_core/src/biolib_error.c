/* Error and logger functions */

#include <stdio.h>
#include <stdarg.h>
#include <biolib_error.h>

static int loglevel = LOG_WARNING;
static FILE *stdlog = NULL;
static char *lognames[] = {
"LOG_EMERG",
"LOG_ALERT",
"LOG_CRIT",
"LOG_ERR", 
"LOG_WARNING",
"LOG_NOTICE",
"LOG_INFO",   
"LOG_DEBUG" }; 


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

/* 
 * Set the loglevel (defined in biolib_error.h) for the simple logger 
 */

void biolib_setloglevel(int level)
{
  loglevel = level;
  char buf[256];
  sprintf(buf,"Setting log level to %d",level);
  biolib_log(LOG_ALERT,buf);
}

/*
 * Simple logger for biolib
 */

void biolib_log(int level, const char *s)
{
  if (level <= loglevel) {
    if (stdlog==NULL)
      stdlog = stderr;
    fprintf(stdlog,"biolib_log (level %d): ",level);
    fprintf(stdlog,lognames[level]);
    fprintf(stdlog,": ");
    fprintf(stdlog,s);
    fprintf(stdlog,"\n");
  }
}

