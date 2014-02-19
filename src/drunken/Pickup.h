#ifndef PICKUP_H
#define PICKUP_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

#define PICKUP_GUN 0
#define PICKUP_BOTTLE 1

class GameScreen;

class Pickup : public Behaviour
{
public:
  static GameObject* create(GameScreen* gameScreen, int type);

  virtual void onUpdate();
  virtual void onStart();

private:
  int type;
  GameScreen* gameScreen;

};

#endif

