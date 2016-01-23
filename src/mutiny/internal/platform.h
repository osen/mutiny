#ifndef MUTINY_PLATFORM_H
#define MUTINY_PLATFORM_H

#ifdef EMSCRIPTEN
  #define USE_SDL
#elif _MSC_VER
  //#define USE_SDL
  #define USE_GLUT
#else
  #define USE_GLUT
  #define HAS_TR1_NAMESPACE
#endif

#ifdef _WIN32
  #define USE_WINAPI 1
#endif

#endif
