#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <mutiny/mutiny.h>

#include <memory>
#include <vector>

using namespace mutiny::engine;

class GameCamera : public Behaviour
{
public:
  static GameObject* create(GameObject* playerGo);

  virtual void onAwake();
  virtual void onStart();
  virtual void onUpdate();
  virtual void onPostRender();

  void toggleEventMode();

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
  Camera* camera;
  GameObject* playerGo;
  std::vector<Vector3> positionBuffer;
  std::vector<Vector3> rotationBuffer;
  bool eventMode;

};

#endif

