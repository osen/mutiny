#ifndef TRANSFORMSCREEN_H
#define TRANSFORMSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class TransformScreen : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<GameObject> cameraGo;
  ref<GameObject> cube1Go;
  ref<GameObject> cube2Go;
  ref<GameObject> centerGo;


};

#endif

