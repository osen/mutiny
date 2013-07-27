#include "GuiStyle.h"
#include "GuiStyleState.h"
#include "Color.h"
#include "Resources.h"
#include "Texture2d.h"

namespace mutiny
{

namespace engine
{

GuiStyle::GuiStyle()
{
  Texture2d* tex = Resources::load<Texture2d>("gui/button_normal");
  Object::dontDestroyOnLoad(tex);

  normal.reset(new GuiStyleState());
  normal->setBackground(tex);

  tex = Resources::load<Texture2d>("gui/button_hover");
  Object::dontDestroyOnLoad(tex);

  hover.reset(new GuiStyleState());
  hover->setBackground(tex);

  tex = Resources::load<Texture2d>("gui/button_active");
  Object::dontDestroyOnLoad(tex);

  active.reset(new GuiStyleState());
  active->setBackground(tex);
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

