#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <mutiny/mutiny.h>

#include <memory>
#include <vector>

using namespace mutiny::engine;

class GameCamera : public Behaviour
{
public:
  static GameObject* create(std::shared_ptr<GameObject> playerGo);

  virtual void onAwake();
  virtual void onStart();
  virtual void onUpdate();
  virtual void onPostRender();

  void toggleEventMode();

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
  Camera* camera;
  std::shared_ptr<GameObject> playerGo;
  std::vector<Vector3> positionBuffer;
  std::vector<Vector3> rotationBuffer;
  bool eventMode;

};

#endif

