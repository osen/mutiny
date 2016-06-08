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
  defaultBackground = Texture2d::create(1, 1);
  defaultBackground->setPixel(0, 0, Color(0, 0, 1, 1));
  defaultBackground->apply();
}

void GuiStyleState::setBackground(ref<Texture2d> background)
{
  this->background = background;
}

ref<Texture2d> GuiStyleState::getBackground()
{
  if(background.expired())
  {
    return defaultBackground;
  }

  return background;
}

}

}

