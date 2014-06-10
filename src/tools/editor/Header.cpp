#include "Header.h"

Header::Header(ProjectScreen* parent)
{

}

void Header::onGui()
{
  position.width = Screen::getWidth();
  position.height = 75;
  Gui::box(position, "");
}

