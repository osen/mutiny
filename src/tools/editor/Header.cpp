#include "Header.h"

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
  position.height = 35;

  Gui::button(Rect(buttonsBegin, 5, 30, 25), playTexture);
  Gui::button(Rect(buttonsBegin + 31, 5, 30, 25), buildTexture);
}

