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
  virtual void onGui();

private:
  std::shared_ptr<RenderTexture> originalPass;
  std::shared_ptr<RenderTexture> blurPass1;
  std::shared_ptr<RenderTexture> blurPass2;
  std::shared_ptr<RenderTexture> blurPass3;
  std::shared_ptr<RenderTexture> lightKeyPass;
  std::shared_ptr<RenderTexture> mergePass;
  std::shared_ptr<Material> texturedMaterial;
  std::shared_ptr<Material> lightKeyMaterial;
  std::shared_ptr<Material> mergeMaterial;

};

#endif

