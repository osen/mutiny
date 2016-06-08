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
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onGui();
  virtual void onStart();

  ref<GameObject> getFence();
  ref<Audio> getAudio();
  ref<GameCamera> getCamera();

private:
  ref<GameObject> cameraGo;
  ref<GameObject> fenceGo;
  shared<Audio> audio;

};

#endif

