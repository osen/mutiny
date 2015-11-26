#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>
#include <memory>
#include <vector>

class FileInfo
{
public:
  static std::shared_ptr<FileInfo> create(std::string absolutePath);
  static std::string getSuffix(std::string absolutePath);
  static std::string getFolderPath(std::string absolutePath);
  static std::string getBaseName(std::string absolutePath);
  static std::string getFileName(std::string absolutePath);
  static void scanDirectory(std::string path, bool directories, std::vector<std::shared_ptr<FileInfo>>& output);

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
  static std::shared_ptr<SourceFileInfo> create(std::string absolutePath);

private:
  void processInclude(std::string absolutePath);
  std::vector<std::shared_ptr<FileInfo>> dependencies;

};

#endif
