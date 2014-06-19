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

  EditorGuiUtil::dropDown(lblRect, "File",
    "New Scene|Reopen Scene|---|Save Scene|---|Exit",
    dropdownClicked);

  lblRect.x += lblRect.width;
  EditorGuiUtil::dropDown(lblRect, "Edit", "", dropdownClicked);
  lblRect.x += lblRect.width; lblRect.width = 55;
  EditorGuiUtil::dropDown(lblRect, "Assets", "", dropdownClicked);
  lblRect.x += lblRect.width; lblRect.width = 85;
  EditorGuiUtil::dropDown(lblRect, "GameObject", "", dropdownClicked);
  lblRect.x += lblRect.width; lblRect.width = 80;
  EditorGuiUtil::dropDown(lblRect, "Component", "", dropdownClicked);
  lblRect.x += lblRect.width; lblRect.width = 45;
  EditorGuiUtil::dropDown(lblRect, "Help", "", dropdownClicked);

  Gui::button(Rect(buttonsBegin, 5 + ITEM_HEIGHT, 30, 25), playTexture);
  Gui::button(Rect(buttonsBegin + 31, 5 + ITEM_HEIGHT, 30, 25), buildTexture);
}

void Header::dropdownClicked(std::string item)
{
  std::cout << item << std::endl;

  if(item == "Exit")
  {
    Application::quit();
  }
}
