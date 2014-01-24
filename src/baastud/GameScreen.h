#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();
  virtual void onStart();

private:
  GameObject* cameraGo;

};

#endif

