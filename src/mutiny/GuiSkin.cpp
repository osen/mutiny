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

std::shared_ptr<GuiSkin> GuiSkin::defaultGuiSkin;

GuiSkin::GuiSkin()
{
  Texture2d* tex = NULL;

  button.reset(new GuiStyle());

  tex = Resources::load<Texture2d>("gui/button_normal");
  Object::dontDestroyOnLoad(tex);
  button->getNormal()->setBackground(tex);

  tex = Resources::load<Texture2d>("gui/button_hover");
  Object::dontDestroyOnLoad(tex);
  button->getHover()->setBackground(tex);

  tex = Resources::load<Texture2d>("gui/button_active");
  Object::dontDestroyOnLoad(tex);
  button->getActive()->setBackground(tex);

  box.reset(new GuiStyle());
  tex = Resources::load<Texture2d>("gui/box_normal");
  Object::dontDestroyOnLoad(tex);
  box->getNormal()->setBackground(tex);
}

GuiStyle* GuiSkin::getButton()
{
  return button.get();
}

GuiStyle* GuiSkin::getBox()
{
  return box.get();
}

}

}

