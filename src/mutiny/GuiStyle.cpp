#include "GuiStyle.h"
#include "GuiStyleState.h"
#include "Color.h"
#include "Texture2d.h"

namespace mutiny
{

namespace engine
{

GuiStyle::GuiStyle()
{
  Texture2d tex(1, 1);
  tex.setPixel(0, 0, Color(0, 0, 1));
  tex.apply();

  normal.reset(new GuiStyleState());
  normal->setBackground(&tex);

  tex.setPixel(0, 0, Color(1, 0, 0));
  tex.apply();

  hover.reset(new GuiStyleState());
  hover->setBackground(&tex);

  tex.setPixel(0, 0, Color(0, 1, 0));
  tex.apply();

  active.reset(new GuiStyleState());
  active->setBackground(&tex);
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

