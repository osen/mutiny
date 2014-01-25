#ifndef PLAYER_H
#define PLAYER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Player : public Behaviour
{
public:
  static GameObject* create();

  virtual void onUpdate();
  virtual void onAwake();

private:

};

#endif

