#ifndef MUTINY_ENGINE_BUTTON_H
#define MUTINY_ENGINE_BUTTON_H

#include "Canvas.h"
#include "../Behaviour.h"

namespace mutiny
{

namespace engine
{

class Canvas;

class Button : public Behaviour
{
private:
  Canvas* canvas;

  void redraw();
  virtual void awake();
  virtual void update();

};

}

}

#endif
