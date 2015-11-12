#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <vector>
#include <memory>

class Environment
{
public:
  static std::shared_ptr<Environment> create(std::vector<std::string>& args);
  std::string getPrefix();

private:
  std::vector<std::string> args;
  std::string prefix;

};

#endif
