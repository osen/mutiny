#include "GuiStyleState.h"
#include "Color.h"
#include "Texture2d.h"

#include <functional>

namespace mutiny
{

namespace engine
{

GuiStyleState::GuiStyleState()
{
  background = NULL;
  Texture2d* tex = Texture2d::create(1, 1);
  defaultBackground = tex;
  tex->setPixel(0, 0, Color(0, 0, 1, 1));
  tex->apply();
}

void GuiStyleState::setBackground(Texture2d* background)
{
  this->background = background;
}

Texture2d* GuiStyleState::getBackground()
{
  if(background == NULL)
  {
    return defaultBackground;
  }

  return background;
}

}

}

