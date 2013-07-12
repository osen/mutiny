#ifndef MUTINY_ENGINE_INTERNAL_UTIL_H
#define MUTINY_ENGINE_INTERNAL_UTIL_H

#include <string>
#include <vector>

namespace mutiny
{

namespace engine
{

namespace internal
{

class Util
{
public:
  static void splitString(std::string input, std::vector<std::string>* output);
  static void splitString(std::string input, char seperator, std::vector<std::string>* output);
  static void splitStringWhitespace(std::string line, std::vector<std::string>* output);
  static double deg2Rad(double input);
  static std::string pathOnly(std::string input);
  static std::string getFoldername(std::string input);
  static std::string getFilename(std::string input);

};

}

}

}

#endif

