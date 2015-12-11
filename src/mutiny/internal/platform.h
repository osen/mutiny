#ifndef MUTINY_PLATFORM_H
#define MUTINY_PLATFORM_H

#ifdef EMSCRIPTEN
  #define USE_SDL
#else
  #define USE_GLUT
#endif

#ifdef _WIN32
  #define USE_WINAPI 1
#endif

#define HAS_TR1_NAMESPACE

#endif
