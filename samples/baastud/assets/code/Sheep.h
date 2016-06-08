#ifndef SHEEP_H
#define SHEEP_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;

class Sheep : public Behaviour
{
public:
  static ref<GameObject> create(ref<GameScreen> gameScreen);

  virtual void onUpdate();
  virtual void onStart();

  void freeze();
  bool isWolf();

private:
  ref<GameScreen> gameScreen;
  ref<Animation> walkAnimation;
  ref<Animation> eatAnimation;
  int state;
  float stateTimeout;
  ref<AnimatedMeshRenderer> sheepMr;
  int random(int min, int max);
  bool wolf;

};

#endif

