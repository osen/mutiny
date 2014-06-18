#include "Header.h"

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
  Gui::label(lblRect, "File");
  lblRect.x += lblRect.width;
  Gui::label(lblRect, "Edit");
  lblRect.x += lblRect.width; lblRect.width = 55;
  Gui::label(lblRect, "Assets");
  lblRect.x += lblRect.width; lblRect.width = 85;
  Gui::label(lblRect, "GameObject");
  lblRect.x += lblRect.width; lblRect.width = 80;
  Gui::label(lblRect, "Component");
  lblRect.x += lblRect.width; lblRect.width = 45;
  Gui::label(lblRect, "Help");

  Gui::button(Rect(buttonsBegin, 5 + ITEM_HEIGHT, 30, 25), playTexture);
  Gui::button(Rect(buttonsBegin + 31, 5 + ITEM_HEIGHT, 30, 25), buildTexture);
}

