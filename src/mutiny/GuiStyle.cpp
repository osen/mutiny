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
  normal = Application::getGC()->gc_new<GuiStyleState>();
  hover = Application::getGC()->gc_new<GuiStyleState>();
  active = Application::getGC()->gc_new<GuiStyleState>();

  alignment = TextAnchor::MiddleCenter;
  border = RectOffset(10, 10, 10, 10);
  font = Resources::load<Font>("fonts/default");

  if(font == NULL)
  {
    throw Exception("Failed to load default font");
  }

  Object::dontDestroyOnLoad(font);
}

GuiStyleState* GuiStyle::getActive()
{
  return active;
}

GuiStyleState* GuiStyle::getNormal()
{
  return normal;
}

GuiStyleState* GuiStyle::getHover()
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

