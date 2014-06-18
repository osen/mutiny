#include "Header.h"
#include "EditorGuiUtil.h"

#define ITEM_HEIGHT 20

Header::Header(ProjectScreen* parent)
{
  playTexture = Resources::load<Texture2d>("images/play");
  buildTexture = Resources::load<Texture2d>("images/build");
  setTitle("Header");
}

void Header::onGui()
{
  int buttonsBegin = Screen::getWidth() / 2;
  buttonsBegin -= 15;

  position.width = Screen::getWidth();
  position.height = 35 + ITEM_HEIGHT;

  Gui::box(Rect(0, 0, position.width, 20), "");

  Rect lblRect(0, 0, 45, ITEM_HEIGHT);
  EditorGuiUtil::dropDown(lblRect, "File", "New Scene|Reopen Scene|---|Save Scene|---|Exit");
  lblRect.x += lblRect.width;
  EditorGuiUtil::dropDown(lblRect, "Edit", "");
  lblRect.x += lblRect.width; lblRect.width = 55;
  EditorGuiUtil::dropDown(lblRect, "Assets", "");
  lblRect.x += lblRect.width; lblRect.width = 85;
  EditorGuiUtil::dropDown(lblRect, "GameObject", "");
  lblRect.x += lblRect.width; lblRect.width = 80;
  EditorGuiUtil::dropDown(lblRect, "Component", "");
  lblRect.x += lblRect.width; lblRect.width = 45;
  EditorGuiUtil::dropDown(lblRect, "Help", "");

  Gui::button(Rect(buttonsBegin, 5 + ITEM_HEIGHT, 30, 25), playTexture);
  Gui::button(Rect(buttonsBegin + 31, 5 + ITEM_HEIGHT, 30, 25), buildTexture);
}

