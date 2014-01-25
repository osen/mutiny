#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class Audio;

class GameScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();
  virtual void onStart();

  GameObject* getFence();
  Audio* getAudio();

private:
  GameObject* cameraGo;
  GameObject* fenceGo;
  std::unique_ptr<Audio> audio;

};

#endif

