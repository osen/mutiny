#ifndef ENGINEBUILDER_H
#define ENGINEBUILDER_H

#include "arc.h"

#include <memory>
#include <vector>
#include <string>

class Environment;
class SourceFileInfo;
class HeaderFileInfo;

class EngineBuilder
{
public:
  static arc<EngineBuilder> create(arc<Environment> environment);
  void removeOrphanedObjects();
  void buildOutOfDateObjects();

private:
  arc<Environment> environment;
  std::vector<arc<SourceFileInfo> > sourceUnits;
  std::vector<arc<HeaderFileInfo> > headers;

  void scanSource(std::string rootDir);
  void prepareDirectories();

  std::string srcDir;

};

#endif
