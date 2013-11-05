#include "GuiStyle.h"
#include "GuiStyleState.h"
#include "Color.h"
#include "Resources.h"
#include "Texture2d.h"
#include "Font.h"

namespace mutiny
{

namespace engine
{

GuiStyle::GuiStyle()
{
  normal.reset(new GuiStyleState());
  hover.reset(new GuiStyleState());
  active.reset(new GuiStyleState());

  border = RectOffset(10, 10, 10, 10);
  font = Resources::load<Font>("fonts/default");

  if(font == NULL)
  {
    Debug::logError("Failed to load default font");
    throw std::exception();
  }

  Object::dontDestroyOnLoad(font);
}

GuiStyleState* GuiStyle::getActive()
{
  return active.get();
}

GuiStyleState* GuiStyle::getNormal()
{
  return normal.get();
}

GuiStyleState* GuiStyle::getHover()
{
  return hover.get();
}

}

}

