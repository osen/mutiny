#include "Environment.h"
#include "Util.h"

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

  return rtn;
}

std::string Environment::getPrefix()
{
  return prefix;
}
