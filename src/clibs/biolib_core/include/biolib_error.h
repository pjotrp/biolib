#ifdef BIOLIB_BUILD

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_EMERG    1
#define LOG_ALERT    2
#define LOG_CRIT     3
#define LOG_ERR      4
#define LOG_WARNING  5
#define LOG_NOTICE   6
#define LOG_INFO     7
#define LOG_DEBUG    8

void biolib_fatal(const char *e_template, ...);
void biolib_setloglevel(int level);
void biolib_log(int level, const char *s);

#ifdef __cplusplus
}
#endif

#endif // BIOLIB_BUILD
