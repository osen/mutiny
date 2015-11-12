#include "cwrapper.h"

std::shared_ptr<Dirent> Dirent::create()
{
  static Dirent s;
  std::shared_ptr<Dirent> rtn(new Dirent(s));

  return rtn;
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
