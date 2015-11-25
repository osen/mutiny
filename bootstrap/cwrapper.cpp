#include "cwrapper.h"

#ifdef HAS_SYS_UTIME
  #include <sys/utime.h>
#endif

#ifdef HAS_DIRECT
  #include <direct.h>
#endif

#ifdef HAS_UTIME
  #include <utime.h>
#endif

std::shared_ptr<Dirent> Dirent::create()
{
  static Dirent s;
  std::shared_ptr<Dirent> rtn(new Dirent(s));

  return rtn;
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
    throw std::exception();
  }
}

std::shared_ptr<Dir> Dir::opendir(std::string path)
{
  static Dir s;
#ifdef HAS_WINAPI
  s.hFind = INVALID_HANDLE_VALUE;
#endif

  std::shared_ptr<Dir> rtn(new Dir(s));
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


std::shared_ptr<Dirent> Dir::readdir()
{
  std::shared_ptr<Dirent> rtn = Dirent::create();
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
    return std::shared_ptr<Dirent>();
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

std::shared_ptr<File> File::popen(std::string path)
{
  static File s;
  std::shared_ptr<File> rtn(new File(s));

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

std::shared_ptr<Stat> Stat::stat(std::string path)
{
  static Stat s;
  std::shared_ptr<Stat> rtn(new Stat(s));

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
std::string Module::getModuleFileName(std::shared_ptr<Module> module)
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