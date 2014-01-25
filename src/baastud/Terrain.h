#ifndef TERRAIN_H
#define TERRAIN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class Terrain : public Behaviour
{
public:
  static GameObject* create();

  virtual void onUpdate();
  virtual void onAwake();

private:

};

#endif

