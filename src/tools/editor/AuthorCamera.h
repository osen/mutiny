#ifndef AUTHORCAMERA_H
#define AUTHORCAMERA_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class AuthorCamera : public Behaviour
{
public:
  static AuthorCamera* create();

  virtual void onAwake();
  virtual void onUpdate();

private:
  Vector3 prevMouse;

};

#endif

