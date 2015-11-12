#ifndef ENGINEBUILDER_H
#define ENGINEBUILDER_H

#include <memory>
#include <vector>
#include <string>

class Environment;
class SourceFileInfo;
class HeaderFileInfo;

class EngineBuilder
{
public:
  static std::shared_ptr<EngineBuilder> create(std::shared_ptr<Environment> environment);

  void buildIfNeeded();

private:
  std::shared_ptr<Environment> environment;
  std::vector<std::shared_ptr<SourceFileInfo>> sourceUnits;
  std::vector<std::shared_ptr<HeaderFileInfo>> headers;

  void scanSource(std::string rootDir);
  bool needsBuilding();
  void prepareDirectories();

  std::string srcDir;

};

#endif
