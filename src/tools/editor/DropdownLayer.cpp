#include "DropdownLayer.h"
#include "ProjectScreen.h"
#include "EditorGuiUtil.h"

#include <vector>

DropdownLayer::DropdownLayer(ProjectScreen* parent)
{
  released = true;
  enabled = false;
  this->parent = parent;
  EditorGuiUtil::dropdownLayer = this;

  color.reset(new Texture2d(1, 1));
  //color->setPixel(0, 0, Color(0.5f, 0.5f, 0.5f, 1.0f));
  color->setPixel(0, 0, Color(0.171f, 0.171f, 0.171f, 1));
  color->apply();
}

void DropdownLayer::onGui()
{
  if(enabled == false)
  {
    return;
  }

  if(Input::getMouseButtonUp(0) == true)
  {
    released = true;
  }

  Gui::drawTexture(captionRect, color.get());
  Gui::label(captionRect, caption);

  Gui::box(rect, "");

  if(released == true && Input::getMouseButtonDown(0) == true &&
    rect.contains(Input::getMousePosition()) == false)
  {
    enabled = false;
  }
}
