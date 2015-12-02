#ifndef FILEINFO_H
#define FILEINFO_H

#include "arc.h"

#include <string>
#include <memory>
#include <vector>

class FileInfo
{
public:
  static arc<FileInfo> create(std::string absolutePath);
  static std::string getSuffix(std::string absolutePath);
  static std::string getFolderPath(std::string absolutePath);
  static std::string getBaseName(std::string absolutePath);
  static std::string getFileName(std::string absolutePath);
  static void scanDirectory(std::string path, bool directories, std::vector<arc<FileInfo> >& output);

  std::string getAbsolutePath();
  std::string getBaseName();
  time_t getModified();
  std::string getFileName();
  void updateModified();

protected:
  std::string absolutePath;
  time_t modified;

  void init(std::string absolutePath);

};

class SourceFileInfo : public FileInfo
{
public:
  static arc<SourceFileInfo> create(std::string absolutePath);

  static arc<SourceFileInfo> create(std::string absolutePath,
    std::vector<std::string> additionalIncludeDirectories);

private:
  void processInclude(std::string absolutePath);
  std::vector<arc<FileInfo> > dependencies;
  std::vector<std::string> additionalIncludeDirectories;

};

#endif
