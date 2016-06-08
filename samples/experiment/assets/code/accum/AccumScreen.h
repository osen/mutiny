#ifndef ACCUMSCREEN_H
#define ACCUMSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class AccumScreen : public Behaviour
{
public:
  static ref<GameObject> create();

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

};

#endif

