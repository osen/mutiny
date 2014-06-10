#include "HierarchyPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"

HierarchyPanel::HierarchyPanel(ProjectScreen* parent)
{
  this->parent = parent;
}

void HierarchyPanel::onGui()
{
  rect.width = parent->filesPanel->rect.width;
  rect.x = parent->filesPanel->rect.x;
  rect.y = parent->logRect.y;
  rect.height = parent->logRect.height;

  Gui::box(rect, "");
}

