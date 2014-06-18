#include "DropdownLayer.h"
#include "ProjectScreen.h"
#include "EditorGuiUtil.h"
#include "Util.h"

#include <vector>

#define ITEM_HEIGHT 24

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
    return;
  }

  std::vector<std::string> splitItems;
  Util::splitString(items, '|', &splitItems);
  Rect itemRect(rect.x + ITEM_HEIGHT, rect.y, rect.width - ITEM_HEIGHT, ITEM_HEIGHT);
  rect.height = 0;
  bool contained = false;

  for(int i = 0; i < splitItems.size(); i++)
  {
    if(splitItems.at(i) != "---")
    {
      if(Rect(rect.x, itemRect.y, rect.width, itemRect.height).contains(
        Input::getMousePosition()) == true && contained == false)
      {
        contained = true;
        Gui::drawTexture(itemRect, color.get());
      }

      Gui::label(itemRect, splitItems.at(i));
      itemRect.y += itemRect.height;
      rect.height += itemRect.height;
    }
    else
    {
      Gui::drawTexture(Rect(itemRect.x, itemRect.y + 2, itemRect.width, 1),
        color.get());

      itemRect.y += 4;
      rect.height += 4;
    }
  }

  Gui::box(Rect(rect.x, rect.y, ITEM_HEIGHT, rect.height), "");
}
