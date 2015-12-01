#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "arc.h"

#include <string>
#include <vector>
#include <memory>

class Environment
{
public:
  static arc<Environment> create(std::vector<std::string>& args);
  std::string getPrefix();

  bool isMutinyAvailable();
  std::string getOutputDirectory();
  std::string getCompilerName();

private:
  std::vector<std::string> args;
  std::string prefix;

  bool mutinyAvailable;
  std::string outputDirectory;
  std::string compilerName;

};

#endif
