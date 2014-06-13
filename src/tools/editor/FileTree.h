#ifndef FILETREE_H
#define FILETREE_H

#include <vector>
#include <string>

class FileTree
{
public:
  FileTree(std::string path);

  std::string getName();

//private:
  std::vector<FileTree> children;
  std::string path;
  bool directory;
  bool expanded;

};

#endif

