#include "GuiStyle.h"
#include "GuiStyleState.h"
#include "Color.h"
#include "Resources.h"
#include "Texture2d.h"
#include "Font.h"
#include "TextAnchor.h"
#include "Exception.h"

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

  if(font.expired())
  {
    throw Exception("Failed to load default font");
  }

  Object::dontDestroyOnLoad(font.get());
}

ref<GuiStyleState> GuiStyle::getActive()
{
  return active;
}

ref<GuiStyleState> GuiStyle::getNormal()
{
  return normal;
}

ref<GuiStyleState> GuiStyle::getHover()
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

