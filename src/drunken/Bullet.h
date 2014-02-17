#ifndef BULLET_H
#define BULLET_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;

class Bullet : public Behaviour
{
public:
  static Bullet* create(GameObject* emitter);

  virtual void onStart();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameObject* emitterGo;
  Vector3 direction;

};

#endif

