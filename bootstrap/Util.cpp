#include "Util.h"
#include "cwrapper.h"

#include <memory>
#include <iostream>

std::string Util::execute(std::string command)
{
  std::shared_ptr<File> proc = File::popen(command + " 2>&1");
  std::string line;
  std::string rtn;

  while(proc->fgets(line) != std::string::npos)
  {
    rtn += line;
  }

  if(proc->pclose() != 0)
  {
    std::cout << rtn << std::endl;
    throw std::exception();
  }

  return rtn;
}

std::string Util::stripEol(std::string input)
{
  std::string rtn;

  for(int i = 0; i < input.length(); i++)
  {
    if(input.at(i) != '\n' && input.at(i) != '\r')
    {
      rtn += input.at(i);
    }
  }

  return rtn;
}

std::string Util::trimLeft(std::string input, char splitter)
{
  for(int i = 0; i < input.length(); i++)
  {
    if(input.at(i) == splitter)
    {
      return input.substr(i + 1);
    }
  }

  return input;
}

std::string Util::trimRight(std::string input, char splitter)
{
  for(int i = input.length() - 1; i >= 0; i--)
  {
    if(input.at(i) == splitter)
    {
      return input.substr(0, i);
    }
  }

  return input;
}

std::string Util::cropRight(std::string input, char splitter)
{
  std::string rtn;

  for(int i = input.length() - 1; i >= 0; i--)
  {
    if(input.at(i) == splitter)
    {
      return rtn;
    }
    else
    {
      rtn = input.at(i) + rtn;
    }
  }

  return "";
}

