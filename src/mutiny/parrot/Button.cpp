#include "Button.h"
#include "Canvas.h"
#include "../GameObject.h"
#include "../Rect.h"
#include "../Vector2.h"
#include "../Transform.h"
#include "../Debug.h"

namespace mutiny
{

namespace engine
{

void Button::awake()
{
  canvas = getGameObject()->addComponent<Canvas>();
  redraw();
}

void Button::redraw()
{
  int width = canvas->getGameObject()->getTransform()->getScale().x;
  int height = canvas->getGameObject()->getTransform()->getScale().y;

  Color activeColor(1.0f, 0.0f, 0.0f);

  if(canvas->isHovering() == false)
  {
    activeColor.a = 0;
  }

  canvas->fillRectangle(Rect(0, 0, width, height), activeColor);
  canvas->fillRectangle(Rect(1, 1, width - 2, height - 2), Color(0.5f, 0.5f, 0.5f));

  canvas->fillRectangle(Rect(1, 1, width - 2, 1), Color(0.8f, 0.8f, 0.8f));
  canvas->fillRectangle(Rect(1, 1, 1, height - 2), Color(0.8f, 0.8f, 0.8f));
  canvas->fillRectangle(Rect(width - 2, 1, 1, height - 2), Color(0.2f, 0.2f, 0.2f));
  canvas->fillRectangle(Rect(2, height - 2, width - 3, 1), Color(0.2f, 0.2f, 0.2f));
}

void Button::update()
{
  if(canvas->hasHoveringChanged() == true)
  {
    redraw();
  }
}

}

}
