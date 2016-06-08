#ifndef FENCE_H
#define FENCE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Fence : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();

  // Number of panels
  static const int FENCE_X_WIDTH = 12;
  static const int FENCE_Z_WIDTH = 8;

  ref<Mesh> mesh;
  Bounds getBounds();

};

#endif
