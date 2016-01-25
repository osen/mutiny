#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "features.h"

#include <string>
#include <vector>
#include <memory>

class Environment
{
public:
  static shared<Environment> create(std::vector<std::string>& args);
  std::string getPrefix();

  bool isMutinyAvailable();
  bool isDebug();
  std::string getOutputDirectory();
  std::string getCompilerName();
  std::vector<std::string> getDefines();
  std::string getProjectName();

private:
  std::vector<std::string> args;
  std::string prefix;

  std::string projectName;
  bool mutinyAvailable;
  std::string outputDirectory;
  std::string compilerName;
  std::vector<std::string> defines;
  bool debug;

};

#endif
