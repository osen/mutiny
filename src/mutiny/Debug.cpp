#include "Debug.h"

#include <string>
#include <iostream>

namespace mutiny
{

namespace engine
{

void Debug::log(std::string message)
{
  std::cout << "Debug: " << message << std::endl;
}

void Debug::logWarning(std::string message)
{
  std::cout << "Warning: " << message << std::endl;
}

void Debug::logError(std::string message)
{
  std::cout << "Error: " << message << std::endl;
}

}

}

