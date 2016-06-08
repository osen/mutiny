#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <mutiny/mutiny.h>

#include <memory>
#include <vector>

using namespace mutiny::engine;

class GameCamera : public Behaviour
{
public:
  static ref<GameObject> create(ref<GameObject> playerGo);

  virtual void onAwake();
  virtual void onStart();
  virtual void onUpdate();
  virtual void onPostRender();

  void toggleEventMode();

private:
  shared<RenderTexture> originalPass;
  shared<RenderTexture> blurPass1;
  shared<RenderTexture> blurPass2;
  shared<RenderTexture> blurPass3;
  shared<RenderTexture> lightKeyPass;
  shared<RenderTexture> mergePass;
  ref<Material> texturedMaterial;
  ref<Material> mergeMaterial;
  ref<Camera> camera;
  ref<GameObject> playerGo;
  std::vector<Vector3> positionBuffer;
  std::vector<Vector3> rotationBuffer;
  bool eventMode;

};

#endif

