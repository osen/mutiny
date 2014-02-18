#ifndef INJUN_H
#define INJUN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;

class Injun : public Behaviour
{
public:
  static Injun* create(GameScreen* gameScreen);

  virtual void onAwake();
  virtual void onUpdate();

private:
  GameScreen* gameScreen;
  AnimatedMeshRenderer* mr;
  Animation* walkAnimation;
  Animation* throwAnimation;
  GameObject* axeGo;
  float shootTimeout;
  float axeReleaseTimeout;
  Vector3 axeVelocity;

  void addAxe();
  void grabAxe();
  void tryThrowAxe();

};

#endif

