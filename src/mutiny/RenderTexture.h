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
  RenderTexture(int width, int height);
  virtual ~RenderTexture();

private:
  static void disable();

  GLuint nativeFrameBuffer;
  std::shared_ptr<void> _nativeFrameBuffer;

  GLuint nativeRenderBuffer;
  std::shared_ptr<void> _nativeRenderBuffer;

  void setEnabled(bool enabled);

};

}

}

#endif

