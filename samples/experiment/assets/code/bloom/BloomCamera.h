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
  arc<RenderTexture> originalPass;
  arc<RenderTexture> blurPass1;
  arc<RenderTexture> blurPass2;
  arc<RenderTexture> lightKeyPass;
  arc<RenderTexture> mergePass;
  Material* texturedMaterial;
  Material* lightKeyMaterial;
  Material* mergeMaterial;

  void regenRenderTextures();

};

#endif

