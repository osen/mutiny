#include "GuiSkin.h"
#include "GuiStyle.h"

#include <memory>

namespace mutiny
{

namespace engine
{

std::shared_ptr<GuiSkin> GuiSkin::defaultGuiSkin;

GuiSkin::GuiSkin()
{
  button.reset(new GuiStyle());
}

GuiStyle* GuiSkin::getButton()
{
  return button.get();
}

}

}

