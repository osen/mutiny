#ifndef MAINCAMERA_H
#define MAINCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class MainCamera : public Behaviour
{
public:
  static MainCamera* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onPostRender();

private:
  RenderTexture* originalPass;
  RenderTexture* blurPass1;
  RenderTexture* blurPass2;
  RenderTexture* blurPass3;
  RenderTexture* lightKeyPass;
  RenderTexture* mergePass;
  Material* texturedMaterial;
  Material* lightKeyMaterial;
  Material* mergeMaterial;

};

#endif

