#ifndef FEATURES_H
#define FEATURES_H

#ifdef _WIN32
  #define HAS_WINAPI
  #define HAS_SYS_UTIME
  #define HAS__POPEN
  #define HAS_DIRECT
  #define DIR_CHAR '\\'
  #define DEFAULT_CXX "cl"
  #define PLATFORM_NAME "windows"
  #define EXECUTABLE_SUFFIX "exe"
#else
  #define HAS_DIRENT
  #define HAS_UTIME
  #define DIR_CHAR '/'
  #define DEFAULT_CXX "g++"

  #ifdef __OpenBSD__
    #define PLATFORM_NAME "openbsd"
  #elif __linux__
    #define PLATFORM_NAME "linux"
  #else
    #define PLATFORM_NAME "other"
  #endif
#endif

#ifdef __GNUC__
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
