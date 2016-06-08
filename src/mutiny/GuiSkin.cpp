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

GuiSkin::GuiSkin()
{
  ref<Texture2d> tex;

  button.reset(new GuiStyle());

  tex = Resources::load<Texture2d>("gui/button_normal");
  Object::dontDestroyOnLoad(tex.get());
  button->getNormal()->setBackground(tex);

  tex = Resources::load<Texture2d>("gui/button_hover");
  Object::dontDestroyOnLoad(tex.get());
  button->getHover()->setBackground(tex);

  tex = Resources::load<Texture2d>("gui/button_active");
  Object::dontDestroyOnLoad(tex.get());
  button->getActive()->setBackground(tex);

  box.reset(new GuiStyle());
  tex = Resources::load<Texture2d>("gui/box_normal");
  Object::dontDestroyOnLoad(tex.get());
  box->getNormal()->setBackground(tex);
}

ref<GuiStyle> GuiSkin::getButton()
{
  return button;
}

ref<GuiStyle> GuiSkin::getBox()
{
  return box;
}

}

}

