#ifndef ACCUMSCREEN_H
#define ACCUMSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class AccumScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameObject* playerGo;

};

#endif

