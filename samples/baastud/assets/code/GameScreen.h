#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class Audio;
class GameCamera;

class GameScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();
  virtual void onStart();

  GameObject* getFence();
  Audio* getAudio();
  GameCamera* getCamera();

private:
  GameObject* cameraGo;
  GameObject* fenceGo;
  arc<Audio> audio;

};

#endif

