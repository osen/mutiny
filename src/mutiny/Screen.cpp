#include "Screen.h"
#include "Application.h"

namespace mutiny
{

namespace engine
{

int Screen::width;
int Screen::height;

int Screen::getWidth()
{
  return width;
}

int Screen::getHeight()
{
  return height;
}


void Screen::setResolution(int width, int height, bool fullscreen, int preferredRefreshRate)
{
  Application::reshape(width, height);
}

}

}

