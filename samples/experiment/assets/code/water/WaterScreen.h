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
  GameObject* playerGo;
  AnimatedMeshRenderer* playerMr;
  arc<Animation> runAnimation;
  arc<Animation> idleAnimation;
  arc<Animation> jumpAnimation;
  float accel;

  GameObject* waterGo;
  MeshRenderer* waterMr;
  arc<Material> waterMaterial;
  float effectOffset;
  float texOffset;
  bool effectUp;

};

#endif

