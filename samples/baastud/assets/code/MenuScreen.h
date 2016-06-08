#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class MenuScreen : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onGui();

private:
  ref<Texture2d> wwwTexture;
  ref<Texture2d> titleTexture;
  ref<GameObject> cameraGo;

  ref<Button> closeButton;
  ref<Button> startButton;

};

#endif

