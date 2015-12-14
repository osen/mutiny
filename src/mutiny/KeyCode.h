#ifndef MUTINY_ENGINE_KEYCODE_H
#define MUTINY_ENGINE_KEYCODE_H

#include "internal/platform.h"

#ifdef USE_SDL
  #include <SDL/SDL.h>
#endif

#ifdef USE_GLUT
  #include <GL/freeglut.h>
#endif

namespace mutiny
{

namespace engine
{

class KeyCode
{
public:
#ifdef USE_SDL
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
#endif

#ifdef USE_GLUT
  static const int UP = GLUT_KEY_UP;
  static const int DOWN = GLUT_KEY_DOWN;
  static const int RIGHT = GLUT_KEY_RIGHT;
  static const int LEFT = GLUT_KEY_LEFT;
  static const int SPACE = ' ';
  static const int A = 'a';
  static const int D = 'd';
  static const int W = 'w';
  static const int S = 's';
  static const int MOUSE0 = GLUT_LEFT_BUTTON;
  static const int MOUSE1 = GLUT_MIDDLE_BUTTON;
  static const int MOUSE2 = GLUT_RIGHT_BUTTON;
#endif

};

}

}

#endif

