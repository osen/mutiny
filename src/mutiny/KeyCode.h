#ifndef MUTINY_ENGINE_KEYCODE_H
#define MUTINY_ENGINE_KEYCODE_H

#include <SDL/SDL.h>

namespace mutiny
{

namespace engine
{

class KeyCode
{
public:
  static const int UP = SDLK_UP;
  static const int DOWN = SDLK_DOWN;
  static const int RIGHT = SDLK_RIGHT;
  static const int LEFT = SDLK_LEFT;
  static const int SPACE = SDLK_SPACE;
  static const int A = SDLK_a;
  static const int D = SDLK_d;
  static const int W = SDLK_w;
  static const int S = SDLK_s;
  static const int MOUSE0 = 99990;
  static const int MOUSE1 = 99991;
  static const int MOUSE2 = 99992;

};

}

}

#endif

