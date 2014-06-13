#include "HierarchyPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"
#include "FileTree.h"

HierarchyPanel::HierarchyPanel(ProjectScreen* parent)
{
  setTitle("Hierarchy");
  this->parent = parent;
}

void HierarchyPanel::onGui()
{
  position.width = parent->filesPanel->position.width;
  position.x = parent->filesPanel->position.x;

  position.height = parent->filesPanel->position.height;

  position.y = parent->filesPanel->position.y +
    parent->filesPanel->position.height;

  listHierarchy();
}

void HierarchyPanel::listHierarchy()
{

}
