#include "FileTree.h"

#include <string>
#include <iostream>

#include <sys/types.h>
#include <dirent.h>

FileTree::FileTree(std::string path)
{
  DIR* dp = NULL;
  struct dirent* ep = NULL;
  std::vector<std::string> filenames;

  //std::cout << path << std::endl;

  this->path = path;
  expanded = false;
  directory = false;
  dp = opendir(path.c_str());

  if(dp != NULL)
  {
    directory = true;

    while(ep = readdir(dp))
    {
      std::string filename = ep->d_name;

      if(filename == "." || filename == "..")
      {
        continue;
      }

      filenames.push_back(filename);
    }

    closedir (dp);
  }

  for(int i = 0; i < filenames.size(); i++)
  {
    children.push_back(FileTree(path + "/" + filenames.at(i)));
  }
}

std::string FileTree::getName()
{
  int lastSep = -1;

  for(int i = 0; i < path.length(); i++)
  {
    if(path[i] == '/' || path[i] == '\\')
    {
      lastSep = i;
    }
  }

  if(lastSep == -1)
  {
    return path;
  }

  return path.substr(lastSep + 1);
}
