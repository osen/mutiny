#ifndef MUTINY_ENGINE_RENDERTEXTURE_H
#define MUTINY_ENGINE_RENDERTEXTURE_H

#include "Texture.h"
#include "internal/glmm.h"

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
  static void setActive(ref<RenderTexture> renderTexture);
  static ref<RenderTexture> getActive();

  static shared<RenderTexture> create(int width, int height);

  virtual ~RenderTexture();

private:
  shared<gl::Uint> nativeFrameBuffer;
  shared<gl::Uint> nativeRenderBuffer;

};

}

}

#endif

