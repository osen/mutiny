#include "HierarchyPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"

HierarchyPanel::HierarchyPanel(ProjectScreen* parent)
{
  setTitle("Hierarchy");
  this->parent = parent;
}

void HierarchyPanel::onGui()
{
  position.width = parent->filesPanel->position.width;
  position.x = parent->filesPanel->position.x;
  position.y = parent->logRect.y;
  position.height = parent->logRect.height;
}

