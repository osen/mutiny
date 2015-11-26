#ifndef PROJECTBUILDER_H
#define PROJECTBUILDER_H

#include <memory>
#include <vector>
#include <string>

class Environment;
class SourceFileInfo;
class HeaderFileInfo;
class FileInfo;

class ProjectBuilder
{
public:
  static std::shared_ptr<ProjectBuilder> create(std::shared_ptr<Environment> environment);
  void removeOrphanedObjects();
  void buildOutOfDateObjects();
  void generateOutOfDateOutput();

private:
  std::shared_ptr<Environment> environment;
  std::vector<std::shared_ptr<SourceFileInfo>> sourceUnits;
  std::vector<std::shared_ptr<HeaderFileInfo>> headers;
  std::vector<std::shared_ptr<FileInfo>> libs;

  void scanSource(std::string rootDir);
  void prepareDirectories();
  void syncAssetDirectory();
  void removeOrphanedAssets();

  std::string srcDir;
  std::string outputDirectory;
  std::string outputFilename;

};

#endif
