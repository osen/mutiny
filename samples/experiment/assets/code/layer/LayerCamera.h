#ifndef LAYERCAMERA_H
#define LAYERCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class LayerCamera : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onUpdate();

private:

};

#endif

