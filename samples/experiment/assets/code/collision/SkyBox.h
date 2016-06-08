#ifndef SKYBOX_H
#define SKYBOX_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class SkyBox : public Behaviour
{
public:
  static ref<SkyBox> create(ref<GameObject> playerGo);

  virtual void onAwake();
  virtual void onUpdate();

private:
  ref<GameObject> playerGo;
  shared<Material> material;

};

#endif

