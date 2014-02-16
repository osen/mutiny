#ifndef PLAYER_H
#define PLAYER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;

class Player : public Behaviour
{
public:
  static GameObject* create(GameScreen* gameScreen);

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameScreen* gameScreen;
  AnimatedMeshRenderer* mr;
  AnimatedMeshRenderer* lmr;
  Animation* walkAnimation;
  Animation* idleAnimation;
  Animation* shootAnimation;
  Animation* duckAnimation;
  GameObject* peacemakerGo;
  GameObject* legsGo;

  void addPeacemaker();
  void setupLegs();

};

#endif

