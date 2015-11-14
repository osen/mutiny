#ifndef BLOOMSCREEN_H
#define BLOOMSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class BloomScreen : public Behaviour
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

