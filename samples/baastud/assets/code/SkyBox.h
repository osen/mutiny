#ifndef SKYBOX_H
#define SKYBOX_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class SkyBox : public Behaviour
{
public:
  static SkyBox* create(GameObject* playerGo);

  virtual void onAwake();
  virtual void onUpdate();

private:
  GameObject* playerGo;

};

#endif

