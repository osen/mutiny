#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util
{
public:
  static std::string execute(std::string command);
  static std::string stripEol(std::string input);
  static std::string cropRight(std::string input, char splitter);
  static std::string trimRight(std::string input, char splitter);
  static std::string trimLeft(std::string input, char splitter);

};

#endif
