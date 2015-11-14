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
  std::shared_ptr<RenderTexture> originalPass;
  std::shared_ptr<RenderTexture> blurPass1;
  std::shared_ptr<RenderTexture> blurPass2;
  std::shared_ptr<RenderTexture> lightKeyPass;
  std::shared_ptr<RenderTexture> mergePass;
  Material* texturedMaterial;
  Material* lightKeyMaterial;
  Material* mergeMaterial;

  void regenRenderTextures();

};

#endif

