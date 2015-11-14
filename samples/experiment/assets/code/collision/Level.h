#ifndef LEVEL_H
#define LEVEL_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Level : public Behaviour
{
public:
  static Level* create(GameObject* playerGo);

  virtual void onAwake();
  virtual void onUpdate();

private:
  GameObject* playerGo;
  float resetCooldown;

};

#endif

