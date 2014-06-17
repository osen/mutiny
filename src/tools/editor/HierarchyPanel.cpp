#include "HierarchyPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"
#include "FileTree.h"

#include <vector>

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
  std::vector<Object*> gameObjects = 
    GameObject::findObjectsOfType<GameObject>();

  for(int i = 0; i < gameObjects.size(); i++)
  {
    Gui::label(Rect(position.x, position.y + 20 + 20 + (20 * i), position.width,
      20), gameObjects.at(i)->getName());
  }
}
