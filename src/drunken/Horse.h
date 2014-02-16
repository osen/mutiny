#ifndef HORSE_H
#define HORSE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;

class Horse : public Behaviour
{
public:
  static Horse* create(GameScreen* gameScreen);

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameScreen* gameScreen;
  AnimatedMeshRenderer* mr;
  Animation* runAnimation;

};

#endif

