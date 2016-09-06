#ifndef FEATURES_H
#define FEATURES_H

// INTERNAL_GCC

#ifdef _WIN32
  #define HAS_WINAPI
  #define HAS_SYS_UTIME
  #define HAS__POPEN
  #define HAS_DIRECT
  #define DIR_CHAR '\\'
  #ifdef INTERNAL_GCC
    #define DEFAULT_CXX "g++"
  #else
    #define DEFAULT_CXX "cl"
  #endif
  #define PLATFORM_NAME "windows"
  #define EXECUTABLE_SUFFIX "exe"
#else
  #define HAS_DIRENT
  #define HAS_UTIME
  #define DIR_CHAR '/'

  #ifdef __OpenBSD__
    #define PLATFORM_NAME "openbsd"
    #define DEFAULT_CXX "g++"
  #elif __FreeBSD__
    #define PLATFORM_NAME "freebsd"
    #define DEFAULT_CXX "clang++"
  #elif __linux__
    #define PLATFORM_NAME "linux"
    #define DEFAULT_CXX "g++"
  #else
    #define PLATFORM_NAME "other"
    #define DEFAULT_CXX "g++"
  #endif
#endif

#ifdef __clang__
  #include <memory>
  #define shared std::shared_ptr
  #define weak std::weak_ptr
#elif __GNUC__
  #include <tr1/memory>
  #define HAS_TR1_NAMESPACE
  #define shared std::tr1::shared_ptr
  #define weak std::tr1::weak_ptr
#elif _MSC_VER
  #include <memory>
  #define shared std::shared_ptr
  #define weak std::weak_ptr
#else

#endif

#include <stdlib.h>

template <class T>
void free_shared(T* ptr)
{
  ptr->~T();
  free(ptr);
}

template <class T>
shared<T> alloc_shared()
{
  shared<T> rtn;

  rtn.reset(new(calloc(1, sizeof(T))) T(), free_shared<T>);

  return rtn;
}

#endif
