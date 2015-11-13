#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <memory>

class Compiler
{
public:
  static std::shared_ptr<Compiler> create();
  void compile(std::string sourceUnit, std::string output);

};

#endif
