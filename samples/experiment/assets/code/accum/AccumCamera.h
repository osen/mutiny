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
  RenderTexture* originalPass;
  RenderTexture* blurPass1;
  RenderTexture* blurPass2;
  RenderTexture* lightKeyPass;
  RenderTexture* mergePass;
  RenderTexture* accumPass;
  RenderTexture* deaccumPass;
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

