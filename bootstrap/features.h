#ifndef FEATURES_H
#define FEATURES_H

#ifdef _WIN32
  #define HAS_WINAPI
  #define HAS_SYS_UTIME
  #define HAS__POPEN
#else
  #define HAS_DIRENT
  #define HAS_UTIME
#endif

#endif