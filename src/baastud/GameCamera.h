#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameCamera : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();

private:
  Camera* camera;

};

#endif

