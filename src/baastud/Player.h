#ifndef PLAYER_H
#define PLAYER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;

class Player : public Behaviour
{
public:
  static GameObject* create(GameScreen* gameScreen);

  virtual void onUpdate();
  virtual void onAwake();

private:
  GameScreen* gameScreen;
  AnimatedMeshRenderer* mr;
  Animation* walkAnimation;
  Animation* idleAnimation;
  Animation* sprintAnimation;
  Animation* humpAnimation;

  void keepInBounds();
  int state;

};

#endif

