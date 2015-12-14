#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <mutiny/mutiny.h>

#include <memory>
#include <vector>

using namespace mutiny::engine;

class GameCamera : public Behaviour
{
public:
  static GameObject* create(arc<GameObject> playerGo);

  virtual void onAwake();
  virtual void onStart();
  virtual void onUpdate();
  virtual void onPostRender();

  void toggleEventMode();

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
  Camera* camera;
  arc<GameObject> playerGo;
  std::vector<Vector3> positionBuffer;
  std::vector<Vector3> rotationBuffer;
  bool eventMode;

};

#endif

