#ifndef WATERSCREEN_H
#define WATERSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class WaterScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<GameObject> playerGo;
  ref<AnimatedMeshRenderer> playerMr;
  ref<Animation> runAnimation;
  ref<Animation> idleAnimation;
  ref<Animation> jumpAnimation;
  float accel;

  ref<GameObject> waterGo;
  ref<MeshRenderer> waterMr;
  ref<Material> waterMaterial;
  float effectOffset;
  float texOffset;
  bool effectUp;

};

#endif

