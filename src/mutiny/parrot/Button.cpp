#include "Button.h"
#include "Canvas.h"
#include "../GameObject.h"
#include "../Rect.h"
#include "../Vector2.h"
#include "../Transform.h"
#include "../Debug.h"
#include "../Material.h"

namespace mutiny
{

namespace engine
{

void Button::onAwake()
{
  canvas = getGameObject()->addComponent<Canvas>();
  redraw();
}

ref<Canvas> Button::getCanvas()
{
  return canvas;
}

void Button::redraw()
{
  int width = canvas->getGameObject()->getTransform()->getScale().x;
  int height = canvas->getGameObject()->getTransform()->getScale().y;

  Color activeColor(1.0f, 0.0f, 0.0f);
  Color backgroundColor(0.5f, 0.5f, 0.5f);
  Color tlBevelColor(0.8f, 0.8f, 0.8f);
  Color brBevelColor(0.3f, 0.3f, 0.3f);

  if(canvas->isHovering() == true)
  {
    backgroundColor = Color(0.7f, 0.7f, 0.7f);
  }

  if(canvas->isActive() == false)
  {
    activeColor.a = 0;
  }

  if(canvas->isPressed() == true)
  {
    backgroundColor = Color(0.4f, 0.4f, 0.4f);
    tlBevelColor = Color(0.2f, 0.2f, 0.2f);
    brBevelColor = Color(0.8f, 0.8f, 0.8f);
  }

  canvas->fillRectangle(Rect(0, 0, width, height), activeColor);
  canvas->fillRectangle(Rect(1, 1, width - 2, height - 2), backgroundColor);

  canvas->fillRectangle(Rect(1, 1, width - 2, 1), tlBevelColor);
  canvas->fillRectangle(Rect(1, 1, 1, height - 2), tlBevelColor);
  canvas->fillRectangle(Rect(width - 2, 1, 1, height - 2), brBevelColor);
  canvas->fillRectangle(Rect(2, height - 2, width - 3, 1), brBevelColor);

  canvas->drawText(Vector2(10, 10), font.get(), "Hello");
}

void Button::onUpdate()
{
  if(canvas->needsRepaint() == true)
  {
    redraw();
  }

  if(canvas->isReleased() == true)
  {
    Debug::log("Clicked!");
  }
}

}

}
