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
  Material* texturedMaterial;
  Material* lightKeyMaterial;
  Material* mergeMaterial;
  Material* accumMaterial;
  Material* deaccumMaterial;
  RenderTexture* accumA;
  RenderTexture* accumB;

  void regenRenderTextures();

};

#endif

