#ifndef POSTSCREEN_H
#define POSTSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class PostScreen : public Behaviour
{
public:
  static GameObject* create();

  virtual void onAwake();
  virtual void onGui();

private:


};

#endif

