#ifndef MUTINY_PLATFORM_H
#define MUTINY_PLATFORM_H

#ifdef EMSCRIPTEN
  #define USE_SDL
#elif _MSC_VER
  #define USE_SDL
#else
  #define USE_GLUT
#endif

#ifdef _WIN32
  #define USE_WINAPI 1
#endif

#ifndef _MSC_VER
  #define HAS_TR1_NAMESPACE
#endif

#endif
