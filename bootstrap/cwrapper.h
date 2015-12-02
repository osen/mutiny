#ifndef CWRAPPER_H
#define CWRAPPER_H

#include "features.h"
#include "arc.h"

#ifdef HAS_DIRENT
  #include <dirent.h>
#endif

#include <sys/stat.h>

#ifdef HAS_WINAPI
  #include <windows.h>
#endif

#include <string>
#include <memory>

#include <cstdio>

class File
{
public:
  static arc<File> popen(std::string path);
  ~File();

  int pclose();
  size_t fgets(std::string& line);

private:
  int type;
  FILE* file;

};

class Dir;
class Dirent
{
  friend class Dir;
public:
  static arc<Dirent> create();

  std::string d_name();

private:
#ifdef HAS_DIRENT
  struct dirent* dp;
#endif
#ifdef HAS_WINAPI
  std::string name;
#endif
  arc<Dir> parent;

};

class Dir
{
public:
  static arc<Dir> opendir(std::string path);
  static void mkdir(std::string path);
  static void remove(std::string path);
  ~Dir();

  arc<Dirent> readdir();

private:
#ifdef HAS_DIRENT
  DIR* dir;
#endif
#ifdef HAS_WINAPI
  HANDLE hFind;
  WIN32_FIND_DATA ffd;
  bool end;
#endif
  arc<Dir> self;

};

class Stat
{
public:
  static arc<Stat> stat(std::string path);
  static void utime(std::string path, time_t aTime, time_t mTime);

  time_t get_st_mtime();

private:
#ifdef HAS__POPEN
  struct _stat attrib;
#else
  struct stat attrib;
#endif

};

#ifdef HAS_WINAPI
class Module
{
public:
  static std::string getModuleFileName(arc<Module> module);

private:
  HMODULE hModule;

};
#endif

#endif

