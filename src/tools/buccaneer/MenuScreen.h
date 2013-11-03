#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <mutiny/mutiny.h>

#include <string>
#include <vector>

using namespace mutiny::engine;

class MenuScreen : public Behaviour
{
public:
  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:

};

#endif

