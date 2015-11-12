#include "cwrapper.h"

#include <utime.h>

std::shared_ptr<Dirent> Dirent::create()
{
  static Dirent s;
  std::shared_ptr<Dirent> rtn(new Dirent(s));

  return rtn;
}

void Dir::mkdir(std::string path)
{
  if(::mkdir(path.c_str(), 0700) == -1)
  {
    throw std::exception();
  }
}

std::shared_ptr<Dir> Dir::opendir(std::string path)
{
  static Dir s;
  std::shared_ptr<Dir> rtn(new Dir(s));
  rtn->self = rtn;
  rtn->dir = ::opendir(path.c_str());

  if(rtn->dir == NULL)
  {
    throw std::exception();
  }

  return rtn;
}

Dir::~Dir()
{
  if(dir != NULL)
  {
    ::closedir(dir);
  }
}

std::shared_ptr<Dirent> Dir::readdir()
{
  std::shared_ptr<Dirent> rtn = Dirent::create();
  rtn->dp = ::readdir(dir);

  if(rtn->dp == NULL)
  {
    return std::shared_ptr<Dirent>();
  }

  rtn->parent = self.lock();

  return rtn;
}

std::string Dirent::d_name()
{
  return dp->d_name;
}

std::shared_ptr<File> File::popen(std::string path)
{
  static File s;
  std::shared_ptr<File> rtn(new File(s));

  rtn->file = ::popen(path.c_str(), "r");

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

  int result = ::pclose(file);
  file = NULL;
  type = 0;

  return result;
}

File::~File()
{
  if(type == 1)
  {
    ::pclose(file);
  }
}

std::shared_ptr<Stat> Stat::stat(std::string path)
{
  static Stat s;
  std::shared_ptr<Stat> rtn(new Stat(s));

  if(::stat(path.c_str(), &rtn->attrib) == -1)
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
