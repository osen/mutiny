#ifndef BLOOMCAMERA_H
#define BLOOMCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class BloomCamera : public Behaviour
{
public:
  static ref<BloomCamera> create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onPostRender();

private:
  shared<RenderTexture> originalPass;
  shared<RenderTexture> blurPass1;
  shared<RenderTexture> blurPass2;
  shared<RenderTexture> lightKeyPass;
  shared<RenderTexture> mergePass;
  ref<Material> texturedMaterial;
  ref<Material> lightKeyMaterial;
  ref<Material> mergeMaterial;

  void regenRenderTextures();

};

#endif

