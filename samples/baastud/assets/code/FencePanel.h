#ifndef FENCEPANEL_H
#define FENCEPANEL_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Fence;

class FencePanel : public Behaviour
{
public:
  static ref<GameObject> create(ref<Fence> fence);

  virtual void onStart();

private:
  ref<Fence> fence;
  shared<Material> material;
};

#endif
