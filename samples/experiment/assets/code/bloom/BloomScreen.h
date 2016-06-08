#ifndef BLOOMSCREEN_H
#define BLOOMSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class BloomScreen : public Behaviour
{
public:
  static ref<GameObject> create();

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<GameObject> playerGo;

};

#endif

