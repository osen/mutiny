#include "Compiler.h"
#include "Util.h"
#include "Environment.h"
#include "FileInfo.h"

#include <iostream>

std::shared_ptr<Compiler> Compiler::create(std::shared_ptr<Environment> environment)
{
  static Compiler s;
  std::shared_ptr<Compiler> rtn(new Compiler(s));
  rtn->environment = environment;
  rtn->name = "g++";

  if(environment->getCompilerName() != "")
  {
    rtn->name = environment->getCompilerName();
  }

  return rtn;
}

void Compiler::addIncludeDirectory(std::string directory)
{
  includeDirectories.push_back(directory);
}

void Compiler::compile(std::string sourceUnit, std::string output)
{
  std::string includeFragment = "";

  for(int i = 0; i < includeDirectories.size(); i++)
  {
    includeFragment += " -I" + includeDirectories.at(i);
  }

  std::string program = name;

  std::string command = program + " -std=c++11 -c" +
    includeFragment +
    " " + sourceUnit +
    " -o" +
    " " + output;

  std::cout << command << std::endl;
  std::string result = Util::execute(command);
}

void Compiler::addObjectDirectory(std::string directory)
{
  objectDirectories.push_back(directory);
}

void Compiler::addLib(std::string path)
{
  libs.push_back(path);
}

void Compiler::link(std::string output)
{
  std::string objectsFragment = "";

  for(int i = 0; i < objectDirectories.size(); i++)
  {
    objectsFragment += " " + objectDirectories.at(i) + "/*.o";
  }

  std::string libsFragment = "";

  for(int i = 0; i < libs.size(); i++)
  {
    libsFragment += " " + libs.at(i);
  }

  std::string program = name;

  libsFragment += " -lGL -lGLEW -lSDL -lSDL_mixer";

  if(FileInfo::getFileName(name) == "em++")
  {
    libsFragment = "";
  }

  std::string command = program +
    objectsFragment +
    " -o" +
    " " + output +
    libsFragment;

  std::cout << command << std::endl;

  std::string result = Util::execute(command);
}
