#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

class Util
{
public:
  static void scanDir(std::string directory, std::vector<std::string>* files);
  static std::string cleanPath(std::string input);

};

#endif

