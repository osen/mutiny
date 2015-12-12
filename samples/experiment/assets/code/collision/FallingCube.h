#ifndef FALLINGCUBE_H
#define FALLINGCUBE_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class FallingCube : public Behaviour
{
public:
  static FallingCube* create();

private:
  virtual void onAwake();
  virtual void collisionEnter(Collision& collision);
  virtual void collisionStay(Collision& collision);
  virtual void collisionExit(Collision& collision);

};

#endif

