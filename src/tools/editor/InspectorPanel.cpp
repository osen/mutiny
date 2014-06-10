#include "InspectorPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"
#include "Header.h"

InspectorPanel::InspectorPanel(ProjectScreen* parent)
{
  this->parent = parent;
}

void InspectorPanel::onGui()
{
  position.width = 300;
  position.x = Screen::getWidth() - position.width;
  position.y = parent->header->position.height;
  position.height = Screen::getHeight() - parent->header->position.height;

  Gui::box(position, "");
}

