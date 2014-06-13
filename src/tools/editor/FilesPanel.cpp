#include "FilesPanel.h"
#include "ProjectScreen.h"
#include "Header.h"
#include "FileTree.h"

FilesPanel::FilesPanel(ProjectScreen* parent)
{
  setTitle("Project");
  this->parent = parent;
  files.reset(new FileTree("../share/baastud"));
  expandTexture = Resources::load<Texture2d>("gui/expand");
}

void FilesPanel::onGui()
{
  position.x = 0;
  position.y = parent->header->position.height;
  position.width = 200;
  position.height = (Screen::getHeight() - parent->header->position.height)
    / 2.0;

  listFiles();
}

void FilesPanel::listFiles()
{
  int indent = 0;
  int y = 0;

  for(int i = 0; i < files->children.size(); i++)
  {
    listFiles(&indent, &y, &files->children.at(i));
  }
}

void FilesPanel::listFiles(int* indent, int* y, FileTree* item)
{
  Rect rect;

  if(*y > 10) return;

  rect.x = position.x + (10 * *indent);
  rect.height = 20;
  rect.y = position.y + rect.height + (*y * rect.height);
  rect.width = position.width;

  Gui::label(Rect(rect.x + expandTexture->getWidth(), rect.y, rect.width,
    rect.height), item->getName());

  *y = *y + 1;

  if(item->directory == false)
  {
    return;
  }

  if(item->children.size() > 0)
  {
    Gui::drawTexture(Rect(rect.x, rect.y, expandTexture->getWidth(),
      expandTexture->getHeight()), expandTexture);
  }

  if(Input::getMouseButtonDown(0) == true &&
     rect.contains(Input::getMousePosition()) == true)
  {
    item->expanded = !item->expanded;
  }

  if(item->expanded == false)
  {
    return;
  }

  *indent = *indent + 1;
  for(int i = 0; i < item->children.size(); i++)
  {
    listFiles(indent, y, &item->children.at(i));
  }
  *indent = *indent - 1;
}

