#ifndef COLLISIONTEST_H
#define COLLISIONTEST_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class CollisionTest : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameObject* cameraGo;
  GameObject* camera2Go;
  GameObject* playerGo;
  GameObject* levelGo = NULL;
  GameObject* level2Go = NULL;
  RenderTexture* renderTexture;
  Texture* levelTexture;

};

#endif

