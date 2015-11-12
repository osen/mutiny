#ifndef CWRAPPER_H
#define CWRAPPER_H

#include <dirent.h>

#include <string>
#include <memory>

#include <stdio.h>

class File
{
public:
  static std::shared_ptr<File> popen(std::string path);
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
  static std::shared_ptr<Dirent> create();

  std::string d_name();

private:
  struct dirent* dp;
  std::shared_ptr<Dir> parent;

};

class Dir
{
public:
  static std::shared_ptr<Dir> opendir(std::string path);
  ~Dir();

  std::shared_ptr<Dirent> readdir();

private:
  DIR* dir;
  std::weak_ptr<Dir> self;
};

#endif

