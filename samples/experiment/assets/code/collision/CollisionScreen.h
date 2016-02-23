#ifndef COLLISIONSCREEN_H
#define COLLISIONSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class CollisionScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameObject* cameraGo;
  GameObject* camera2Go;
  GameObject* playerGo;
  GameObject* cubeGo;
  GameObject* levelGo;
  GameObject* level2Go;
  RenderTexture* renderTexture;
  Texture* levelTexture;

};

#endif

