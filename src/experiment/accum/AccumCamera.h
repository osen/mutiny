#ifndef ACCUMCAMERA_H
#define ACCUMCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class AccumCamera : public Behaviour
{
public:
  static AccumCamera* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onPostRender();

private:
  std::shared_ptr<RenderTexture> originalPass;
  std::shared_ptr<RenderTexture> blurPass1;
  std::shared_ptr<RenderTexture> blurPass2;
  std::shared_ptr<RenderTexture> lightKeyPass;
  std::shared_ptr<RenderTexture> mergePass;
  std::shared_ptr<RenderTexture> accumPass;
  Material* texturedMaterial;
  Material* lightKeyMaterial;
  Material* mergeMaterial;
  Material* accumMaterial;

  void regenRenderTextures();

};

#endif

