#ifndef PLAYER_H
#define PLAYER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Player : public Behaviour
{
public:
  static ref<Player> create();

  virtual void onAwake();
  virtual void onUpdate();

private:
  shared<Material> material;
  shared<Material> particleMaterial;

};

#endif

