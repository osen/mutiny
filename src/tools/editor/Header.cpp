#include "Header.h"

Header::Header(ProjectScreen* parent)
{

}

void Header::onGui()
{
  rect.width = Screen::getWidth();
  rect.height = 75;
  Gui::box(rect, "");
}

