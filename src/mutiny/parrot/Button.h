#ifndef MUTINY_ENGINE_BUTTON_H
#define MUTINY_ENGINE_BUTTON_H

#include "Canvas.h"
#include "../Behaviour.h"
#include "../Font.h"
#include "../arc.h"

namespace mutiny
{

namespace engine
{

class Canvas;

class Button : public Behaviour
{
public:
  Canvas* getCanvas();

private:
  Canvas* canvas;
  arc<Font> font;

  void redraw();
  virtual void awake();
  virtual void update();

};

}

}

#endif
