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
  arc<RenderTexture> originalPass;
  arc<RenderTexture> blurPass1;
  arc<RenderTexture> blurPass2;
  arc<RenderTexture> blurPass3;
  arc<RenderTexture> lightKeyPass;
  arc<RenderTexture> mergePass;
  arc<Material> texturedMaterial;
  arc<Material> lightKeyMaterial;
  arc<Material> mergeMaterial;

};

#endif

