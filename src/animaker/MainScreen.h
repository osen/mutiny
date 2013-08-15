#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class MainScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  AnimatedMesh* animatedMesh;
  GameObject* root;
  GameObject* animationGo;
  GameObject* transient;
  GameObject* transient2;
  Texture2d* simpleTex;
  Vector2 lastMousePosition;


};

#endif

