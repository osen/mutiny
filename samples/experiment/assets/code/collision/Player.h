#ifndef PLAYER_H
#define PLAYER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Player : public Behaviour
{
public:
  static Player* create();

  virtual void onAwake();
  virtual void onUpdate();

private:
  arc<Material> material;

};

#endif

