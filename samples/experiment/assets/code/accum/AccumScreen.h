#ifndef ACCUMSCREEN_H
#define ACCUMSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class AccumScreen : public Behaviour
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

};

#endif

