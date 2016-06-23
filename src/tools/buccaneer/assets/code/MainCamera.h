#ifndef MAINCAMERA_H
#define MAINCAMERA_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class MainCamera : public Behaviour
{
public:
  static ref<MainCamera> create();

  virtual void onAwake();
  virtual void onUpdate();

private:

};

#endif

