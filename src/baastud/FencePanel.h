#ifndef FENCEPANEL_H
#define FENCEPANEL_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Fence;

class FencePanel : public Behaviour
{
public:
  static GameObject* create(Fence* fence);

  virtual void onAwake();

private:
  Fence* fence;
};

#endif
