#ifndef SKYBOX_H
#define SKYBOX_H

#include <mutiny/mutiny.h>

#include <string>

using namespace mutiny::engine;

class SkyBox : public Behaviour
{
public:
  static SkyBox* create(GameObject* playerGo, std::string texturePath);

  virtual void onStart();
  virtual void onUpdate();

private:
  GameObject* playerGo;
  std::string texturePath;

};

#endif

