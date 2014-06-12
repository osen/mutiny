#include "ScenePanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"
#include "InspectorPanel.h"

ScenePanel::ScenePanel(ProjectScreen* parent)
{
  setTitle("Scene");
  this->parent = parent;
}

void ScenePanel::onGui()
{
  position.x = parent->filesPanel->position.width;
  position.width = Screen::getWidth() - parent->filesPanel->position.width -
parent->inspectorPanel->position.width;
  position.y = parent->filesPanel->position.y;
  position.height = parent->filesPanel->position.height;
}

