#ifndef ACCUMCAMERA_H
#define ACCUMCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class AccumCamera : public Behaviour
{
public:
  static ref<AccumCamera> create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onPostRender();

private:
  shared<RenderTexture> originalPass;
  shared<RenderTexture> blurPass1;
  shared<RenderTexture> blurPass2;
  shared<RenderTexture> lightKeyPass;
  shared<RenderTexture> mergePass;
  shared<RenderTexture> accumPass;
  shared<RenderTexture> deaccumPass;
  ref<Material> texturedMaterial;
  ref<Material> lightKeyMaterial;
  ref<Material> mergeMaterial;
  ref<Material> accumMaterial;
  ref<Material> deaccumMaterial;
  shared<RenderTexture> accumA;
  shared<RenderTexture> accumB;

  void regenRenderTextures();

};

#endif

