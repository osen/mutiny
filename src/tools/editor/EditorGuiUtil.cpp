#include "EditorGuiUtil.h"
#include "DropdownLayer.h"

Texture2d* EditorGuiUtil::tabTexture = NULL;
Texture2d* EditorGuiUtil::noTabTexture = NULL;
DropdownLayer* EditorGuiUtil::dropdownLayer = NULL;

std::string EditorGuiUtil::tabs(Rect rect, std::vector<std::string>* names,
    std::string current)
{
  std::string rtn = current;

  if(tabTexture == NULL || noTabTexture == NULL)
  {
    tabTexture = Resources::load<Texture2d>("gui/tab_active");
    Object::dontDestroyOnLoad(tabTexture);
    noTabTexture = Resources::load<Texture2d>("gui/tab_normal");
    Object::dontDestroyOnLoad(noTabTexture);
  }

  for(int i = 0; i < names->size(); i++)
  {
    if(names->at(i) == current)
    {
      Graphics::drawTexture(Rect(rect.x + (rect.width * i), rect.y, rect.width,
        rect.height), tabTexture, Rect(0, 0, 1, 1), 5, 5, 5, 5);
    }
    else
    {
      Gui::drawTexture(Rect(rect.x + (rect.width * i), rect.y, rect.width,
        rect.height), noTabTexture);
    }

    Gui::label(Rect(rect.x + (rect.width * i), rect.y, rect.width, rect.height), names->at(i));

    if(Input::getMouseButtonDown(0) == true)
    {
      if(Rect(rect.x + (rect.width * i), rect.y, rect.width, rect.height).contains(Input::getMousePosition()) == true)
      {
        rtn = names->at(i);
      }
    }
  }

  return rtn;
}

void EditorGuiUtil::dropDown(Rect rect, std::string caption, std::string items)
{
  Gui::label(rect, caption);

  if(Input::getMouseButtonDown(0) == true)
  {
    if(rect.contains(Input::getMousePosition()) == true)
    {
      if(dropdownLayer->caption == caption && dropdownLayer->enabled == true)
      {
        dropdownLayer->enabled = false;
      }
      else
      {
        dropdownLayer->enabled = true;
        dropdownLayer->released = false;
        dropdownLayer->captionRect = rect;
        dropdownLayer->caption = caption;
        dropdownLayer->rect = Rect(rect.x, rect.y + rect.height - 1, 200, 200);
      }
    }
  }
}
