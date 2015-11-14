#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <memory>
#include <vector>

class Compiler
{
public:
  static std::shared_ptr<Compiler> create();
  void compile(std::string sourceUnit, std::string output);
  void addIncludeDirectory(std::string directory);
  void addObjectDirectory(std::string directory);
  void addLib(std::string path);
  void link(std::string output);

private:
  std::vector<std::string> includeDirectories;
  std::vector<std::string> objectDirectories;
  std::vector<std::string> libs;

};

#endif
