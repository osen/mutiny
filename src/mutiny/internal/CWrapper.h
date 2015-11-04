#ifndef MUTINY_ENGINE_INTERNAL_CWRAPPER_H
#define MUTINY_ENGINE_INTERNAL_CWRAPPER_H

#include "lodepng.h"

#include <GL/glew.h>

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

}

}

}

#endif

