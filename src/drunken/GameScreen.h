#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class GameCamera;

class GameScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();
  virtual void onStart();

  GameCamera* getCamera();

private:
  GameObject* cameraGo;

};

#endif

