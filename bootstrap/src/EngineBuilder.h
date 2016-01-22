#ifndef ENGINEBUILDER_H
#define ENGINEBUILDER_H

#include "features.h"

#include <memory>
#include <vector>
#include <string>

class Environment;
class SourceFileInfo;
class HeaderFileInfo;

class EngineBuilder
{
public:
  static shared<EngineBuilder> create(shared<Environment> environment);
  void removeOrphanedObjects();
  void buildOutOfDateObjects();

private:
  shared<Environment> environment;
  std::vector<shared<SourceFileInfo> > sourceUnits;
  std::vector<shared<HeaderFileInfo> > headers;

  void scanSource(std::string rootDir);
  void prepareDirectories();

  std::string srcDir;

};

#endif
