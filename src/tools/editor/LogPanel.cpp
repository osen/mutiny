#include "LogPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"
#include "FileTree.h"
#include "InspectorPanel.h"

#include <vector>

LogPanel::LogPanel(ProjectScreen* parent)
{
  setTitle("Console");
  this->parent = parent;
}

void LogPanel::onGui()
{
  position.width = Screen::getWidth() - parent->inspectorPanel->position.width -
    position.x;

  position.x = parent->filesPanel->position.width;
  position.height = 200;
  position.y = Screen::getHeight() - position.height;
}

