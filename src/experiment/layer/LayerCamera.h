#ifndef LAYERCAMERA_H
#define LAYERCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class LayerCamera : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onPostRender();

private:
  std::shared_ptr<RenderTexture> originalPass;
  std::shared_ptr<RenderTexture> blurPass1;
  std::shared_ptr<RenderTexture> blurPass2;
  std::shared_ptr<RenderTexture> blurPass3;
  std::shared_ptr<RenderTexture> lightKeyPass;
  std::shared_ptr<RenderTexture> mergePass;
  Material* texturedMaterial;
  Material* lightKeyMaterial;
  Material* mergeMaterial;

};

#endif

