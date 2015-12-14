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
  arc<RenderTexture> originalPass;
  arc<RenderTexture> blurPass1;
  arc<RenderTexture> blurPass2;
  arc<RenderTexture> lightKeyPass;
  arc<RenderTexture> mergePass;
  arc<RenderTexture> accumPass;
  arc<RenderTexture> deaccumPass;
  arc<Material> texturedMaterial;
  arc<Material> lightKeyMaterial;
  arc<Material> mergeMaterial;
  arc<Material> accumMaterial;
  arc<Material> deaccumMaterial;
  arc<RenderTexture> accumA;
  arc<RenderTexture> accumB;

  void regenRenderTextures();

};

#endif

