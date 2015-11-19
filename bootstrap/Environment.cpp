#include "Environment.h"
#include "Util.h"
#include "cwrapper.h"

#include <iostream>

std::shared_ptr<Environment> Environment::create(std::vector<std::string>& args)
{
  static Environment s;
  std::shared_ptr<Environment> rtn(new Environment(s));
  rtn->args = args;

  std::string absolutePath = Util::stripEol(Util::execute("which \"" + args.at(0) + "\""));
  std::string absoluteBinPath = Util::stripEol(Util::execute("dirname \"" + absolutePath + "\""));
  rtn->prefix = Util::stripEol(Util::execute("dirname \"" + absoluteBinPath + "\""));

  std::cout << "Mutiny Prefix: " << rtn->prefix << std::endl;

  try
  {
    std::shared_ptr<Dir> dir = Dir::opendir(rtn->prefix + "/src/mutiny");
    std::shared_ptr<Dirent> dirent = dir->readdir();

    if(dirent.get() != NULL)
    {
      std::cout << "Mutiny is available" << std::endl;
      rtn->mutinyAvailable = true;
    }

  }
  catch(std::exception& e) { }

  for(int i = 0; i < args.size(); i++)
  {
    if(args.at(i) == "-o")
    {
      i++;
      rtn->outputDirectory = args.at(i);
    }
    else if(args.at(i) == "-c")
    {
      i++;
      rtn->compilerName = args.at(i);
    }
  }

  return rtn;
}

std::string Environment::getCompilerName()
{
  return compilerName;
}

std::string Environment::getOutputDirectory()
{
  return outputDirectory;
}

bool Environment::isMutinyAvailable()
{
  return mutinyAvailable;
}

std::string Environment::getPrefix()
{
  return prefix;
}
