#include "FilesPanel.h"
#include "ProjectScreen.h"
#include "Header.h"

FilesPanel::FilesPanel(ProjectScreen* parent)
{
  this->parent = parent;
}

void FilesPanel::onGui()
{
  rect.x = 0;
  rect.y = parent->header->rect.height;
  rect.width = 200;
  rect.height = Screen::getHeight()
                - parent->header->rect.height
                - parent->logRect.height;

  Gui::box(rect, "");
}

