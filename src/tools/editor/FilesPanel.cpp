#include "FilesPanel.h"
#include "ProjectScreen.h"
#include "Header.h"

FilesPanel::FilesPanel(ProjectScreen* parent)
{
  this->parent = parent;
}

void FilesPanel::onGui()
{
  position.x = 0;
  position.y = parent->header->position.height;
  position.width = 200;
  position.height = Screen::getHeight()
                - parent->header->position.height
                - parent->logRect.height;

  Gui::box(position, "");
}

