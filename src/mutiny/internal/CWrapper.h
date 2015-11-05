#ifndef MUTINY_ENGINE_INTERNAL_CWRAPPER_H
#define MUTINY_ENGINE_INTERNAL_CWRAPPER_H

#include "lodepng.h"

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
  static std::shared_ptr<PngData> create();
  ~PngData();

  unsigned char* image;
  unsigned width;
  unsigned height;
};

struct GlBuffer
{
  static std::shared_ptr<GlBuffer> create();
  ~GlBuffer();

  GLuint id;
};

#ifdef _WIN32
struct Win32FindData
{
  static std::shared_ptr<Win32FindData> create();

  WIN32_FIND_DATA ffd;
  
};

struct FindHandle
{
  static std::shared_ptr<FindHandle> FindFirstFile(std::string path, std::shared_ptr<Win32FindData> findData);
  ~FindHandle();
  bool FindNextFile();

  std::shared_ptr<Win32FindData> findData;
  HANDLE hFind;
  
};
#endif

}

}

}

#endif

