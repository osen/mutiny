#ifndef DIEDSCREEN_H
#define DIEDSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class DiedScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();
  virtual void onStart();

private:
  void setupPlayer();

};

#endif

