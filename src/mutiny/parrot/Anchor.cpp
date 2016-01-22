#include "Anchor.h"
#include "Canvas.h"
#include "../GameObject.h"
#include "../Screen.h"

namespace mutiny
{

namespace engine
{

void Anchor::onAwake()
{
  canvas = getGameObject()->getComponent<Canvas>();
  referenceScreenSize = Vector2(Screen::getWidth(), Screen::getHeight());
}

void Anchor::onUpdate()
{
  resizeDelta = Vector2(Screen::getWidth(), Screen::getHeight()) - referenceScreenSize;
}

void Anchor::setAttachment(int options)
{
  this->options = options;
}

Vector2 Anchor::getOffset()
{
  return resizeDelta;
}

}

}
