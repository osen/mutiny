#include "cwrapper.h"
#include "Util.h"

#ifdef HAS_SYS_UTIME
  #include <sys/utime.h>
#endif

#ifdef HAS_DIRECT
  #include <direct.h>
#endif

#ifdef HAS_UTIME
  #include <utime.h>
#endif

#ifdef HAS_WINAPI

#else
  #include <unistd.h>
#endif

#include <iostream>
#include <string>
#include <vector>

shared<Dirent> Dirent::create()
{
  shared<Dirent> rtn = alloc_shared<Dirent>();

  return rtn;
}

std::string Dir::getcwd()
{
#ifdef HAS_WINAPI
  char rtn[MAX_PATH];

  if(GetCurrentDirectory(MAX_PATH, rtn) == 0)
#else
  char rtn[PATH_MAX];

  if(::getcwd(rtn, PATH_MAX) == NULL)
#endif
  {
    return "";
  }

  return rtn;
}

void Dir::mkdir_r(std::string path)
{
  std::vector<std::string> parts;

  while(true)
  {
    std::string part = Util::cropRight(path, DIR_CHAR);
    parts.push_back(part);
    std::string origPath = path;
    path = Util::trimRight(path, DIR_CHAR);

    if(path == "" || path == origPath)
    {
      break;
    }
  }

  std::string tpath;
  std::string sep;

  for(int i = parts.size() - 1; i >= 0; i--)
  {
    tpath += sep + parts.at(i);
    sep = DIR_CHAR;

    if(Dir::isdir(tpath) == true) continue;

    mkdir(tpath);
  }

  //Dir::opendir(path);
}

void Dir::mkdir(std::string path)
{
#ifdef HAS_DIRECT
  if(::_mkdir(path.c_str()) == -1)
#endif
#ifdef HAS_DIRENT
  if(::mkdir(path.c_str(), 0700) == -1)
#endif
  {
    throw std::exception();
  }
}

void Dir::remove(std::string path)
{
  if(::remove(path.c_str()) == -1)
  {
#ifdef HAS_WINAPI
    if(RemoveDirectory(path.c_str()) == 0)
#endif
    throw std::exception();
  }
}

bool Dir::isdir(std::string path)
{
  shared<Dir> rtn = alloc_shared<Dir>();
#ifdef HAS_WINAPI
  rtn->hFind = INVALID_HANDLE_VALUE;
#endif
  rtn->self = rtn;

#ifdef HAS_DIRENT
  rtn->dir = ::opendir(path.c_str());

  if(rtn->dir == NULL)
#endif
#ifdef HAS_WINAPI
  path = path + "\\*";
  rtn->hFind = FindFirstFile(path.c_str(), &rtn->ffd);

  if(rtn->hFind == INVALID_HANDLE_VALUE)
#endif
  {
    return false;
  }

  return true;
}

shared<Dir> Dir::opendir(std::string path)
{
  shared<Dir> rtn = alloc_shared<Dir>();
#ifdef HAS_WINAPI
  rtn->hFind = INVALID_HANDLE_VALUE;
#endif
  rtn->self = rtn;

#ifdef HAS_DIRENT
  rtn->dir = ::opendir(path.c_str());

  if(rtn->dir == NULL)
#endif
#ifdef HAS_WINAPI
  path = path + "\\*";
  rtn->hFind = FindFirstFile(path.c_str(), &rtn->ffd);

  if(rtn->hFind == INVALID_HANDLE_VALUE)
#endif
  {
    throw std::exception();
  }

  return rtn;
}

Dir::~Dir()
{
#ifdef HAS_DIRENT
  if(dir != NULL)
  {
    ::closedir(dir);
  }
#endif
#ifdef HAS_WINAPI
  if(hFind != INVALID_HANDLE_VALUE)
  {
    FindClose(hFind);
  }
#endif
}


shared<Dirent> Dir::readdir()
{
  shared<Dirent> rtn = Dirent::create();
#ifdef HAS_DIRENT
  rtn->dp = ::readdir(dir);

  if(rtn->dp == NULL)
  {
#endif
#ifdef HAS_WINAPI
  if(end == false)
  {
    rtn->name = ffd.cFileName;

    if(FindNextFile(hFind, &ffd) == 0)
    {
      end = true;
    }
  }
  else
  {
#endif
    return shared<Dirent>();
  }

  rtn->parent = self.lock();

  return rtn;
}

std::string Dirent::d_name()
{
#ifdef HAS_DIRENT
  return dp->d_name;
#endif
#ifdef HAS_WINAPI
  return name;
#endif
}

shared<File> File::popen(std::string path)
{
  shared<File> rtn = alloc_shared<File>();

#ifdef HAS__POPEN
  rtn->file = ::_popen(path.c_str(), "r");
#else
  rtn->file = ::popen(path.c_str(), "r");
#endif

  if(rtn->file == NULL)
  {
    throw std::exception();
  }

  rtn->type = 1;

  return rtn;
}

size_t File::fgets(std::string& line)
{
  char buffer[2048];

  if(::fgets(buffer, 2048, file) == NULL)
  {
    return std::string::npos;
  }

  line = buffer;

  return line.length();
}

int File::pclose()
{
  if(type != 1)
  {
    throw std::exception();
  }

  if(file == NULL)
  {
    throw std::exception();
  }

#ifdef HAS__POPEN
  int result = ::_pclose(file);
#else
  int result = ::pclose(file);
#endif
  file = NULL;
  type = 0;

  return result;
}

File::~File()
{
  if(type == 1)
  {
#ifdef HAS__POPEN
    ::_pclose(file);
#else
    ::pclose(file);
#endif
  }
}

shared<Stat> Stat::stat(std::string path)
{
  shared<Stat> rtn = alloc_shared<Stat>();

#ifdef HAS__POPEN
  if(::_stat(path.c_str(), &rtn->attrib) == -1)
#else
  if(::stat(path.c_str(), &rtn->attrib) == -1)
#endif
  {
    throw std::exception();
  }

  return rtn;
}

time_t Stat::get_st_mtime()
{
  return attrib.st_mtime;
}

void Stat::utime(std::string path, time_t aTime, time_t mTime)
{
  struct utimbuf times = {0};
  times.actime = aTime;
  times.modtime = mTime;

  if(::utime(path.c_str(), &times) == -1)
  {
    throw std::exception();
  }
}

#ifdef HAS_WINAPI
std::string Module::getModuleFileName(shared<Module> module)
{
  char buffer[MAX_PATH];
  int result;

  if(module.get() == NULL)
  {
    result = GetModuleFileName(NULL, buffer, sizeof(buffer));
  }
  else
  {
    result = GetModuleFileName(module->hModule, buffer, sizeof(buffer));
  }

  if(result == 0)
  {
    throw std::exception();
  }

  return buffer;
}
#endif
