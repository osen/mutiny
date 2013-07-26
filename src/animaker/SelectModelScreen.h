#ifndef SELECTMODELSCREEN_H
#define SELECTMODELSCREEN_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class SelectModelScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:

};

#endif

