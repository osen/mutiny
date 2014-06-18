#include "Util.h"

void Util::splitString(std::string input, char separator, std::vector<std::string>* output)
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
      output->push_back(current);
      current = "";
    }
    else
    {
      current += input[i];
    }
  }

  if(current.length() > 0)
  {
    output->push_back(current);
  }
}

