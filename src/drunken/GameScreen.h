#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class GameCamera;
class Player;

class GameScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();
  virtual void onStart();

  GameCamera* getCamera();
  Player* getPlayer();

private:
  GameObject* cameraGo;
  Player* player;

};

#endif

