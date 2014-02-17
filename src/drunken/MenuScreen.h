#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameCamera;
class Horse;

class MenuScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();
  virtual void onStart();

private:
  GameCamera* camera;
  Horse* horse;

};

#endif

