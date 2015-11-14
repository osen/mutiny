#include "Compiler.h"
#include "Util.h"

std::shared_ptr<Compiler> Compiler::create()
{
  static Compiler s;
  std::shared_ptr<Compiler> rtn(new Compiler(s));

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

  std::string result = Util::execute("g++ -std=c++11 -c" +
    includeFragment +
    " " + sourceUnit +
    " -o" +
    " " + output);
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

  std::string result = Util::execute("g++" +
    objectsFragment +
    " -o" +
    " " + output +
    libsFragment +
    " -lGL -lGLEW -lSDL -lSDL_mixer");
}
