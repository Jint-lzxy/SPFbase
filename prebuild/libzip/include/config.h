#ifndef HAD_CONFIG_H
#define HAD_CONFIG_H
#ifndef _HAD_ZIPCONF_H
#include "zipconf.h"
#endif
/* BEGIN DEFINES */
/* #undef HAVE___PROGNAME */
#define HAVE__CHMOD
#define HAVE__CLOSE
#define HAVE__DUP
#define HAVE__FDOPEN
#define HAVE__FILENO
#define HAVE__OPEN
#define HAVE__SETMODE
/* #undef HAVE__SNPRINTF */
#define HAVE__STRDUP
#define HAVE__STRICMP
#define HAVE__STRTOI64
#define HAVE__STRTOUI64
/* #undef HAVE__UMASK */
#define HAVE__UNLINK
/* #undef HAVE_ARC4RANDOM */
/* #undef HAVE_CLONEFILE */
/* #undef HAVE_COMMONCRYPTO */
#define HAVE_CRYPTO
/* #undef HAVE_FICLONERANGE */
#define HAVE_FILENO
/* #undef HAVE_FSEEKO */
/* #undef HAVE_FTELLO */
/* #undef HAVE_GETPROGNAME */
/* #undef HAVE_GNUTLS */
/* #undef HAVE_LIBBZ2 */
/* #undef HAVE_LIBLZMA */
/* #undef HAVE_LOCALTIME_R */
/* #undef HAVE_MBEDTLS */
/* #undef HAVE_MKSTEMP */
/* #undef HAVE_NULLABLE */
#define HAVE_OPEN
/* #undef HAVE_OPENSSL */
#define HAVE_SETMODE
/* #undef HAVE_SNPRINTF */
/* #undef HAVE_SSIZE_T_LIBZIP */
/* #undef HAVE_STRCASECMP */
#define HAVE_STRDUP
#define HAVE_STRICMP
#define HAVE_STRTOLL
#define HAVE_STRTOULL
/* #undef HAVE_STRUCT_TM_TM_ZONE */
#define HAVE_STDBOOL_H
/* #undef HAVE_STRINGS_H */
/* #undef HAVE_UNISTD_H */
#define HAVE_WINDOWS_CRYPTO
#define __INT8_LIBZIP 1
#define INT8_T_LIBZIP 1
#define UINT8_T_LIBZIP 1
#define __INT16_LIBZIP 2
#define INT16_T_LIBZIP 2
#define UINT16_T_LIBZIP 2
#define __INT32_LIBZIP 4
#define INT32_T_LIBZIP 4
#define UINT32_T_LIBZIP 4
#define __INT64_LIBZIP 8
#define INT64_T_LIBZIP 8
#define UINT64_T_LIBZIP 8
#define SHORT_LIBZIP 2
#define INT_LIBZIP 4
#define LONG_LIBZIP 4
#define LONG_LONG_LIBZIP 8
#define SIZEOF_OFF_T 4
#define SIZE_T_LIBZIP 4
/* #undef SSIZE_T_LIBZIP */
/* #undef HAVE_DIRENT_H */
/* #undef HAVE_FTS_H */
/* #undef HAVE_NDIR_H */
/* #undef HAVE_SYS_DIR_H */
/* #undef HAVE_SYS_NDIR_H */
/* #undef WORDS_BIGENDIAN */
#define HAVE_SHARED
/* END DEFINES */
#define PACKAGE "libzip"
#define VERSION "1.6.1"

#ifndef HAVE_SSIZE_T_LIBZIP
#  if SIZE_T_LIBZIP == INT_LIBZIP
typedef int ssize_t;
#  elif SIZE_T_LIBZIP == LONG_LIBZIP
typedef long ssize_t;
#  elif SIZE_T_LIBZIP == LONG_LONG_LIBZIP
typedef long long ssize_t;
#  else
#error no suitable type for ssize_t found
#  endif
#endif

#endif /* HAD_CONFIG_H */
