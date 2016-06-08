#ifndef MODELSCREEN_H
#define MODELSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class ModelScreen : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onStart();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<GameObject> cameraGo;
  ref<GameObject> modelGo;


};

#endif

