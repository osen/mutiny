#ifndef MUTINY_ENGINE_BUTTON_H
#define MUTINY_ENGINE_BUTTON_H

#include "Canvas.h"
#include "../Behaviour.h"
#include "../Font.h"

namespace mutiny
{

namespace engine
{

class Canvas;

class Button : public Behaviour
{
public:
  ref<Canvas> getCanvas();

private:
  ref<Canvas> canvas;
  ref<Font> font;

  void redraw();
  virtual void onAwake();
  virtual void onUpdate();

};

}

}

#endif
