#ifndef SKYBOX_H
#define SKYBOX_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class SkyBox : public Behaviour
{
public:
  static SkyBox* create(std::shared_ptr<GameObject> playerGo);

  virtual void onAwake();
  virtual void onUpdate();

private:
  std::shared_ptr<GameObject> playerGo;

};

#endif

