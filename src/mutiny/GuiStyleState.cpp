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
  Texture2d* tex = new Texture2d(1, 1);
  defaultBackground.reset(tex);
  tex->setPixel(0, 0, Color(0, 0, 1, 1));
  tex->apply();
}

void GuiStyleState::setBackground(arc<Texture2d> background)
{
  this->background = background;
}

arc<Texture2d> GuiStyleState::getBackground()
{
  if(background.get() == NULL)
  {
    return defaultBackground;
  }

  return background;
}

}

}

