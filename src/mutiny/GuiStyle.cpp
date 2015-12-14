#include "GuiStyle.h"
#include "GuiStyleState.h"
#include "Color.h"
#include "Resources.h"
#include "Texture2d.h"
#include "Font.h"
#include "TextAnchor.h"

namespace mutiny
{

namespace engine
{

GuiStyle::GuiStyle()
{
  normal.reset(new GuiStyleState());
  hover.reset(new GuiStyleState());
  active.reset(new GuiStyleState());

  alignment = TextAnchor::MiddleCenter;

  border = RectOffset(10, 10, 10, 10);
  font = Resources::load<Font>("fonts/default");

  if(font.get() == NULL)
  {
    Debug::logError("Failed to load default font");
    throw std::exception();
  }

  Object::dontDestroyOnLoad(font.cast<Object>());
}

arc<GuiStyleState> GuiStyle::getActive()
{
  return active;
}

arc<GuiStyleState> GuiStyle::getNormal()
{
  return normal;
}

arc<GuiStyleState> GuiStyle::getHover()
{
  return hover;
}

void GuiStyle::setAlignment(int alignment)
{
  this->alignment = alignment;
}

int GuiStyle::getAlignment()
{
  return alignment;
}

}

}

