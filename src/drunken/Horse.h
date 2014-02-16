#ifndef HORSE_H
#define HORSE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;

class Horse : public Behaviour
{
public:
  static Horse* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

  void addCowboy();
  void wedge();

private:
  AnimatedMeshRenderer* mr;
  Animation* runAnimation;
  GameObject* cowboyGo;

};

#endif

