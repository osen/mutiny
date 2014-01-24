#ifndef FENCE_H
#define FENCE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Fence : public Behaviour
{
public:
  static GameObject* create();

  virtual void onUpdate();

private:

};

#endif
