#include "Button.h"
#include "Canvas.h"
#include "../GameObject.h"
#include "../Rect.h"
#include "../Vector2.h"

namespace mutiny
{

namespace engine
{

void Button::awake()
{
  canvas = getGameObject()->addComponent<Canvas>();

  int width = 256;
  int height = 64;
  canvas->setSize(width, height);
  canvas->fillRectangle(Rect(0, 0, width, height), Color(1.0f, 0.0f, 0.0f));
  canvas->fillRectangle(Rect(1, 1, width - 2, height - 2), Color(0.5f, 0.5f, 0.5f));

  canvas->fillRectangle(Rect(1, 1, width - 2, 1), Color(0.8f, 0.8f, 0.8f));
  canvas->fillRectangle(Rect(1, 1, 1, height - 2), Color(0.8f, 0.8f, 0.8f));
  canvas->fillRectangle(Rect(width - 2, 1, 1, height - 2), Color(0.2f, 0.2f, 0.2f));
  canvas->fillRectangle(Rect(2, height - 2, width - 3, 1), Color(0.2f, 0.2f, 0.2f));
}

}

}
