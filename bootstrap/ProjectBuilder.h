#ifndef PROJECTBUILDER_H
#define PROJECTBUILDER_H

#include "arc.h"

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
  static arc<ProjectBuilder> create(arc<Environment> environment);
  void removeOrphanedObjects();
  void buildOutOfDateObjects();
  void generateOutOfDateOutput();

private:
  arc<Environment> environment;
  std::vector<arc<SourceFileInfo> > sourceUnits;
  //std::vector<arc<HeaderFileInfo> > headers;
  std::vector<arc<FileInfo> > libs;
  std::vector<std::string> includeDirectories;

  void scanSource(std::string rootDir);
  void scanForIncludeDirectories(std::string rootDir);
  void prepareDirectories();
  void syncAssetDirectory();
  void removeOrphanedAssets();

  std::string srcDir;
  std::string outputDirectory;
  std::string outputFilename;

};

#endif
