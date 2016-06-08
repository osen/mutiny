#ifndef COLLISIONSCREEN_H
#define COLLISIONSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class CollisionScreen : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<GameObject> cameraGo;
  ref<GameObject> camera2Go;
  ref<GameObject> playerGo;
  ref<GameObject> cubeGo;
  ref<GameObject> levelGo;
  ref<GameObject> level2Go;
  shared<RenderTexture> renderTexture;
  ref<Texture2d> levelTexture;

};

#endif

