#ifndef FENCE_H
#define FENCE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Fence : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();

  // Number of panels
  const int FENCE_X_WIDTH = 20;
  const int FENCE_Z_WIDTH = 20;

  Mesh* mesh;

private:

};

#endif
