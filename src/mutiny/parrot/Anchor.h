#ifndef MUTINY_ENGINE_ANCHOR_H
#define MUTINY_ENGINE_BUTTON_H

#include "../Behaviour.h"
#include "../arc.h"
#include "../Vector2.h"

namespace mutiny
{

namespace engine
{

class Canvas;

class Anchor : public Behaviour
{
public:
  static const int RIGHT = 1;
  static const int BOTTOM = 2;

  void setAttachment(int options);
  Vector2 getOffset();

private:
  Canvas* canvas;
  int options;
  Vector2 referenceScreenSize;
  Vector2 resizeDelta;

  virtual void onAwake();
  virtual void onUpdate();

};

}

}

#endif
