#ifndef PLAYER_H
#define PLAYER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;

class Player : public Behaviour
{
public:
  static Player* create(GameScreen* gameScreen);

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

  void addPeacemaker();

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

  void setupLegs();

};

#endif

