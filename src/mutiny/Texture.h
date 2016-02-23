#ifndef MUTINY_ENGINE_TEXTURE_H
#define MUTINY_ENGINE_TEXTURE_H

#include "Object.h"
#include "internal/glmm.h"

#include <GL/glew.h>

#include <memory>

namespace mutiny
{

namespace engine
{

class Texture : public Object
{
public:
  Texture();
  virtual ~Texture();

  int getWidth();
  int getHeight();
  GLuint getNativeTexture();

protected:
  int width;
  int height;

  gl::Uint* nativeTexture;

};

}

}

#endif

