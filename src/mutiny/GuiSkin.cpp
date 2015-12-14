#include "GuiSkin.h"
#include "GuiStyle.h"
#include "GuiStyleState.h"
#include "Resources.h"
#include "Texture2d.h"

#include <memory>

namespace mutiny
{

namespace engine
{

GuiSkin* GuiSkin::_default;

GuiSkin::GuiSkin()
{
  arc<Texture2d> tex = NULL;

  button.reset(new GuiStyle());

  tex = Resources::load<Texture2d>("gui/button_normal");
  Object::dontDestroyOnLoad(tex.cast<Object>());
  button->getNormal()->setBackground(tex);

  tex = Resources::load<Texture2d>("gui/button_hover");
  Object::dontDestroyOnLoad(tex.cast<Object>());
  button->getHover()->setBackground(tex);

  tex = Resources::load<Texture2d>("gui/button_active");
  Object::dontDestroyOnLoad(tex.cast<Object>());
  button->getActive()->setBackground(tex);

  box.reset(new GuiStyle());
  tex = Resources::load<Texture2d>("gui/box_normal");
  Object::dontDestroyOnLoad(tex.cast<Object>());
  box->getNormal()->setBackground(tex);
}

arc<GuiStyle> GuiSkin::getButton()
{
  return button;
}

arc<GuiStyle> GuiSkin::getBox()
{
  return box;
}

}

}

