#ifndef FEATURES_H
#define FEATURES_H

#ifdef _WIN32
  #define HAS_WINAPI
  #define HAS_SYS_UTIME
  #define HAS__POPEN
  #define HAS_DIRECT
  #define DIR_CHAR '\\'
  #define DEFAULT_CXX "cl"
#else
  #define HAS_DIRENT
  #define HAS_UTIME
  #define DIR_CHAR '/'
  #define DEFAULT_CXX "g++"
#endif

#ifdef __GNUC__
  #define HAS_TR1_NAMESPACE
#elif _MSC_VER

#else

#endif

#endif
