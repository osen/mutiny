#ifndef MUTINY_ENGINE_DEBUG_H
#define MUTINY_ENGINE_DEBUG_H

#include <string>

namespace mutiny
{

namespace engine
{

class Debug
{
public:
  static void log(std::string message);
  static void logWarning(std::string message);
  static void logError(std::string message);

};

}

}

#endif

