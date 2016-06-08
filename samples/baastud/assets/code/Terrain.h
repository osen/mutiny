#ifndef TERRAIN_H
#define TERRAIN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Terrain : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();

private:
  shared<Material> material;

};

#endif

