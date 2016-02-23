#ifndef BLOOMCAMERA_H
#define BLOOMCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class BloomCamera : public Behaviour
{
public:
  static BloomCamera* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onPostRender();

private:
  RenderTexture* originalPass;
  RenderTexture* blurPass1;
  RenderTexture* blurPass2;
  RenderTexture* lightKeyPass;
  RenderTexture* mergePass;
  Material* texturedMaterial;
  Material* lightKeyMaterial;
  Material* mergeMaterial;

  void regenRenderTextures();

};

#endif

