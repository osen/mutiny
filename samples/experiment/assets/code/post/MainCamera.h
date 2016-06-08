#ifndef MAINCAMERA_H
#define MAINCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class MainCamera : public Behaviour
{
public:
  static ref<MainCamera> create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onPostRender();

private:
  shared<RenderTexture> originalPass;
  shared<RenderTexture> blurPass1;
  shared<RenderTexture> blurPass2;
  shared<RenderTexture> blurPass3;
  shared<RenderTexture> lightKeyPass;
  shared<RenderTexture> mergePass;
  ref<Material> texturedMaterial;
  ref<Material> lightKeyMaterial;
  ref<Material> mergeMaterial;

};

#endif

