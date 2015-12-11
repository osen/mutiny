#ifndef MUTINY_ENGINE_INTERNAL_CWRAPPER_H
#define MUTINY_ENGINE_INTERNAL_CWRAPPER_H

#include "lodepng.h"
#include "../arc.h"

#include <GL/glew.h>

#ifdef _WIN32
  #include <windows.h>
#endif

#include <memory>

namespace mutiny
{

namespace engine
{

namespace internal
{


struct PngData
{
  static arc<PngData> create();
  ~PngData();

  unsigned char* image;
  unsigned width;
  unsigned height;
};

struct GlBuffer
{
  static arc<GlBuffer> create();
  ~GlBuffer();

  GLuint id;
};

#ifdef _WIN32
struct Win32FindData
{
  static arc<Win32FindData> create();

  WIN32_FIND_DATA ffd;
  
};

struct FindHandle
{
  static arc<FindHandle> FindFirstFile(std::string path, arc<Win32FindData> findData);
  ~FindHandle();
  bool FindNextFile();

  arc<Win32FindData> findData;
  HANDLE hFind;
  
};
#endif

}

}

}

#endif

