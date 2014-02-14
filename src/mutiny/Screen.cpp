#include "Screen.h"
#include "Application.h"

namespace mutiny
{

namespace engine
{

int Screen::getWidth()
{
  return Application::getInternal()->screenWidth;
}

int Screen::getHeight()
{
  return Application::getInternal()->screenHeight;
}

}

}

