#ifndef PROJECTBUILDER_H
#define PROJECTBUILDER_H

#include "features.h"

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
  static shared<ProjectBuilder> create(shared<Environment> environment);
  void removeOrphanedObjects();
  void buildOutOfDateObjects();
  void generateOutOfDateOutput();

private:
  shared<Environment> environment;
  std::vector<shared<SourceFileInfo> > sourceUnits;
  //std::vector<shared<HeaderFileInfo> > headers;
  std::vector<shared<FileInfo> > libs;
  std::vector<std::string> includeDirectories;

  void scanSource(std::string rootDir);
  void scanForIncludeDirectories(std::string rootDir);
  void prepareDirectories();
  bool syncAssetDirectory(std::string assetDirectory);
  void removeOrphanedAssets();
  void obtainOutputFilename();

  std::string srcDir;
  std::string outputDirectory;
  std::string outputFilename;

};

#endif
