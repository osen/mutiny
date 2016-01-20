#include "FileInfo.h"
#include "Util.h"
#include "cwrapper.h"
#include "features.h"

#include <iostream>
#include <fstream>


void FileInfo::scanDirectory(std::string path, bool directories, std::vector<arc<FileInfo> >& output)
{
  arc<Dir> dir = Dir::opendir(path);
  arc<Dirent> dirent = dir->readdir();

  while(dirent.get() != NULL)
  {
    if(dirent->d_name().at(0) != '.')
    {
      try
      {
        scanDirectory(path + DIR_CHAR + dirent->d_name(), directories, output);

        if(directories == true)
        {
          output.push_back(FileInfo::create(path + DIR_CHAR + dirent->d_name()));
        }
      }
      catch(std::exception& e)
      {
        if(directories == false)
        {
          output.push_back(FileInfo::create(path + DIR_CHAR + dirent->d_name()));
        }
      }
    }

    dirent = dir->readdir();
  }
}

arc<FileInfo> FileInfo::create(std::string absolutePath)
{
  arc<FileInfo> rtn = arc<FileInfo>::alloc();
  rtn->FileInfo::init(absolutePath);

  return rtn;
}

std::string FileInfo::getAbsolutePath()
{
  return absolutePath;
}

std::string FileInfo::getFileName()
{
  return getFileName(absolutePath);
}

std::string FileInfo::getBaseName()
{
  return getBaseName(absolutePath);
}

void FileInfo::updateModified()
{
  arc<Stat> stat = Stat::stat(absolutePath);
  modified = stat->get_st_mtime();
}

void FileInfo::init(std::string absolutePath)
{
  this->absolutePath = absolutePath;

  arc<Stat> stat = Stat::stat(absolutePath);
  modified = stat->get_st_mtime();
}

std::string FileInfo::getFileName(std::string absolutePath)
{
  return Util::cropRight(absolutePath, DIR_CHAR);
}

std::string FileInfo::getBaseName(std::string absolutePath)
{
  std::string filename = Util::cropRight(absolutePath, DIR_CHAR);

  return Util::trimRight(filename, '.');
}

std::string FileInfo::getSuffix(std::string absolutePath)
{
  return Util::cropRight(absolutePath, '.');
}

std::string FileInfo::getFolderPath(std::string absolutePath)
{
  return Util::trimRight(Util::fixPath(absolutePath), DIR_CHAR);
}

time_t FileInfo::getModified()
{
  return modified;
}

arc<SourceFileInfo> SourceFileInfo::create(std::string absolutePath)
{
  return SourceFileInfo::create(absolutePath, std::vector<std::string>());
}

arc<SourceFileInfo> SourceFileInfo::create(std::string absolutePath,
  std::vector<std::string> additionalIncludeDirectories)
{
  arc<SourceFileInfo> rtn = arc<SourceFileInfo>::alloc();
  rtn->additionalIncludeDirectories = additionalIncludeDirectories;
  rtn->FileInfo::init(absolutePath);

  //std::cout << "Source: " << absolutePath << std::endl;

  //try
  //{
    rtn->processInclude(absolutePath);
  //}
  //catch(std::exception& e)
  //{
  //  std::cout << "Warning: Failed to process source: " << absolutePath << std::endl;
  //}

  time_t recentModification = rtn->getModified();

  for(int i = 0; i < rtn->dependencies.size(); i++)
  {
    if(rtn->dependencies.at(i)->getModified() > recentModification)
    {
      recentModification = rtn->dependencies.at(i)->getModified();
    }

    //std::cout << "Dep: " << rtn->dependencies.at(i)->getAbsolutePath() << std::endl;
    //std::cout << "  Mod: " << rtn->dependencies.at(i)->getModified() << std::endl;
  }

  if(recentModification > rtn->getModified())
  {
    //std::cout << "Need update..." << std::endl;
    Stat::utime(absolutePath, recentModification, recentModification);
    rtn->modified = recentModification;
  }

  return rtn;
}

void SourceFileInfo::processInclude(std::string absolutePath)
{
  // Dont want to reprocess file if already in list
  for(int i = 0; i < dependencies.size(); i++)
  {
    if(absolutePath == dependencies.at(i)->getAbsolutePath())
    {
      return;
    }
  }

  // Dont add initial cpp unit to list of depends
  if(absolutePath != this->absolutePath)
  {
    dependencies.push_back(FileInfo::create(absolutePath));
  }

  //std::cout << "Processing: " << absolutePath << std::endl;

  std::ifstream file(absolutePath.c_str());

  if(file.is_open() == false)
  {
    std::cout << "Warning: Failed to open: " << absolutePath << std::endl;
    throw std::exception();
  }

  while(file.eof() == false)
  {
    std::string token;
    file >> token;

    if(token == "") continue;

    if(token.substr(0, 1) == "#")
    {
      if(token == "#")
      {
        std::string tmp;
        file >> tmp;
        token = token + tmp;
      }

      if(token.substr(0, 8) == "#include")
      {
        if(token == "#include")
        {
          std::string tmp;
          file >> tmp;
          token = token + tmp;
        }

        std::string dep = token.substr(8);

        if(dep.at(0) == '"')
        {
          dep = Util::trimLeft(dep, '"');
          dep = Util::trimRight(dep, '"');
          dep = Util::fixPath(getFolderPath(absolutePath) + DIR_CHAR + dep);

          try
          {
            //std::cout << "Processing: " << dep << std::endl;
            processInclude(dep);
          }
          catch(std::exception& e){}
        }
        else if(dep.at(0) == '<')
        {
          dep = Util::trimLeft(dep, '<');
          dep = Util::trimRight(dep, '>');

          for(int i = 0; i < additionalIncludeDirectories.size(); i++)
          {
            try
            {
              //std::cout << "Additional: " << additionalIncludeDirectories.at(i) << DIR_CHAR << dep << std::endl;
              processInclude(additionalIncludeDirectories.at(i) + DIR_CHAR + dep);
            }
            catch(std::exception& e){}
          }
        }
      }
    }
  }
}
