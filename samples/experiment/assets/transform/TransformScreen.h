#ifndef TRANSFORMSCREEN_H
#define TRANSFORMSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class TransformScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameObject* cameraGo;
  GameObject* cube1Go;
  GameObject* cube2Go;
  GameObject* centerGo;


};

#endif

