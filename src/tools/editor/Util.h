#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

class Util
{
public:
  static void splitString(std::string input, char separator, std::vector<std::string>* output);

};

#endif
