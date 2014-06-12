#include "EditorGuiUtil.h"

Texture2d* EditorGuiUtil::tabTexture = NULL;
Texture2d* EditorGuiUtil::noTabTexture = NULL;

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

