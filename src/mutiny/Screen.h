#ifndef MUTINY_ENGINE_SCREEN_H
#define MUTINY_ENGINE_SCREEN_H

namespace mutiny
{

namespace engine
{

class Application;

class Screen
{
  friend class Application;

public:
  static int getWidth();
  static int getHeight();
  static void setResolution(int width, int height, bool fullscreen, int preferredRefreshRate = 0);

private:
  static int width;
  static int height;

};

}

}

#endif

