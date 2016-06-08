#include "Util.h"

namespace mutiny
{

namespace engine
{

namespace internal
{

double Util::deg2Rad(double input)
{
  return input * (3.14159265359f / 180);
}

void Util::splitString(std::string input, std::vector<std::string>& output)
{
  splitString(input, ' ', output);
}

void Util::splitString(std::string input, char separator, std::vector<std::string>& output)
{
  std::string current;

  for(int i = 0; i < input.length(); i++)
  {
    if(input[i] == '\t' || input[i] == '\r' || input[i] == '\n')
    {
      continue;
    }

    if(input[i] == separator)
    {
      output.push_back(current);
      current = "";
    }
    else
    {
      current += input[i];
    }
  }

  if(current.length() > 0)
  {
    output.push_back(current);
  }
}

void Util::splitStringWhitespace(std::string line, std::vector<std::string>& output)
{
  bool lastWasWhiteSpace = true;
  std::string current;

  for(int i = 0; i < line.length(); i++)
  {
    if(line[i] == '\n' || line[i] == '\r')
    {
      continue;
    }

    if(line[i] == ' ' || line[i] == '\t')
    {
      if(lastWasWhiteSpace == false)
      {
        output.push_back(current);
        current = "";
        lastWasWhiteSpace = true;
      }
    }
    else
    {
      current += line[i];
      lastWasWhiteSpace = false;
    }
  }

  if(current.length() > 0)
  {
    output.push_back(current);
  }
}

std::string Util::pathOnly(std::string input)
{
  int last = -1;

  for(int i = 0; i < input.length(); i++)
  {
    if(input[i] == '/' || input[i] == '\\')
    {
      last = i;
    }
  }

  if(last == -1)
  {
    return "";
  }

  return input.substr(0, last);
}

std::string Util::getFilename(std::string input)
{
  int lastSep = 0;

  for(int i = 0; i < input.length(); i++)
  {
    if(input[i] == '/' || input[i] == '\\')
    {
      lastSep = i;
    }
  }

  return input.substr(lastSep + 1);
}

std::string Util::getFoldername(std::string input)
{
  int lastSep = 0;

  for(int i = 0; i < input.length(); i++)
  {
    if(input[i] == '/' || input[i] == '\\')
    {
      lastSep = i;
    }
  }

  return input.substr(0, lastSep);
}

}

}

}

