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
  static const int FENCE_X_WIDTH = 5;
  static const int FENCE_Z_WIDTH = 5;

  Mesh* mesh;

private:

};

#endif
