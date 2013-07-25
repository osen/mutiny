#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <mutiny/mutiny.h>

#include <memory>

using namespace mutiny::engine;

class MainScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameObject* transient;


};

#endif

