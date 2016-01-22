#ifndef MUTINY_ENGINE_ANCHOR_H
#define MUTINY_ENGINE_BUTTON_H

#include "Canvas.h"
#include "../Behaviour.h"
#include "../arc.h"

namespace mutiny
{

namespace engine
{

class Anchor : public Behaviour
{
public:
  static const int RIGHT = 1;
  static const int BOTTOM = 2;

  void set(int options);

private:
  int options;
  virtual void onAwake();
  virtual void onUpdate();

};

}

}

#endif
