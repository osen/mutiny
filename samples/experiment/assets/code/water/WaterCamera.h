#ifndef WATERCAMERA_H
#define WATERCAMERA_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class WaterCamera : public Behaviour
{
public:
  static ref<WaterCamera> create();

  virtual void onAwake();
  virtual void onUpdate();

private:

};

#endif

