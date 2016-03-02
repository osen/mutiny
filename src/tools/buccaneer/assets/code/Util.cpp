#include "Util.h"

#include <sys/types.h>

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif

void Util::scanDir(std::string directory, std::vector<std::string>* files)
{
  DIR* dp = NULL;
  struct dirent* ep = NULL;

  dp = opendir (directory.c_str());

  if(dp != NULL)
  {
    while(ep = readdir(dp))
    {
      std::string filename = ep->d_name;

      if(filename == "." || filename == "..")
      {
        continue;
      }

      scanDir(directory + "/" + filename, files);
      files->push_back(directory + "/" + filename);
    }

    closedir (dp);
  }
}

std::string Util::cleanPath(std::string input)
{
  std::string output;

  for(int i = input.length() - 1; i >= 0; i--)
  {
    if(input[i] == '/' || input[i] == '\\')
    {
      break;
    }

    output = input[i] + output;
  }

  return output;
}

std::string Util::pathOnly(std::string input)
{
  int lastSep = -1;

  for(int i = 0; i < input.length(); i++)
  {
    if(input[i] == '/' || input[i] == '\\')
    {
      lastSep = i;
    }
  }

  if(lastSep == -1)
  {
    return ".";
  }

  return input.substr(0, lastSep);
}

