#ifndef MUTINY_ENGINE_RENDERTEXTURE_H
#define MUTINY_ENGINE_RENDERTEXTURE_H

#include "Texture.h"

namespace mutiny
{

namespace engine
{

class Application;
class Graphics;

class RenderTexture : public Texture
{
  friend class mutiny::engine::Application;
  friend class mutiny::engine::Graphics;

public:
  static void setActive(RenderTexture* renderTexture);

  RenderTexture(int width, int height);
  virtual ~RenderTexture();

private:
  GLuint nativeFrameBuffer;
  std::shared_ptr<void> _nativeFrameBuffer;

  GLuint nativeRenderBuffer;
  std::shared_ptr<void> _nativeRenderBuffer;

};

}

}

#endif

