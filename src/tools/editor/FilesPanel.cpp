#include "FilesPanel.h"
#include "ProjectScreen.h"
#include "Header.h"
#include "FileTree.h"
#include "SelectProjectScreen.h"

#define ITEM_HEIGHT 20

FilesPanel::FilesPanel(ProjectScreen* parent)
{
  setTitle("Project");
  this->parent = parent;

  files.reset(new FileTree(Application::getDataPath() + "/../" +
    SelectProjectScreen::selectedProject));

  expandTexture = Resources::load<Texture2d>("gui/expand");

  selectedTexture.reset(new Texture2d(1, 1));
  selectedTexture->setPixel(0, 0, Color(1.0f, 1.0f, 1.0f, 0.1f));
  selectedTexture->apply();

  startDisplay = 0;
  maxDisplay = 0;
  totalDisplay = 0;
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
  int total = 0;

  //maxDisplay = (position.height - ITEM_HEIGHT) / ITEM_HEIGHT;
  maxDisplay = (position.height - (ITEM_HEIGHT * 2)) / ITEM_HEIGHT;

  y = y - startDisplay;

  for(int i = 0; i < files->children.size(); i++)
  {
    listFiles(&indent, &y, &total, &files->children.at(i));
  }

  totalDisplay = total;
}

void FilesPanel::listFiles(int* indent, int* y, int* total, FileTree* item)
{
  Rect rect;
  Rect expandRect;
  bool display = false;

  *total = *y;
  rect.x = position.x + (10 * *indent);
  rect.height = ITEM_HEIGHT;
  rect.y = position.y + rect.height + (*y * rect.height) + ITEM_HEIGHT;
  rect.width = position.width;

  if(totalDisplay >= maxDisplay)
  {
    rect.width -= 20;
  }

  expandRect = Rect(rect.x, rect.y, expandTexture->getWidth(),
    expandTexture->getHeight());

  if(*y <= maxDisplay && *y >= 0)
  {
    display = true;
  }

  if(display == true)
  {
    if(item->path == selectedPath)
    {
      Gui::drawTexture(Rect(position.x, rect.y, rect.width, rect.height), selectedTexture.get());
    }

    Gui::label(Rect(rect.x + expandTexture->getWidth(), rect.y, rect.width
      - ((position.x + rect.x) - position.x + expandTexture->getWidth()),
      rect.height), item->getName());

    if(Input::getMouseButtonDown(0) == true)
    {
      if(rect.contains(Input::getMousePosition()) == true)
      {
        selectedPath = item->path;
      }
    }
  }

  *y = *y + 1;

  if(item->directory == false)
  {
    return;
  }

  if(display == true)
  {
    if(item->children.size() > 0)
    {
      if(item->expanded == true)
      {
        Gui::drawTexture(expandRect, expandTexture);
      }
      else
      {
        GuiUtility::rotateAroundPivot(90, Vector2(rect.x +
          (expandTexture->getWidth() / 2), rect.y + (expandTexture->getHeight() / 2)));

        Gui::drawTexture(expandRect, expandTexture);

        GuiUtility::rotateAroundPivot(-90, Vector2(rect.x +
          (expandTexture->getWidth() / 2), rect.y + (expandTexture->getHeight() / 2)));
      }
    }

    if(Input::getMouseButtonDown(0) == true)
    {
      if(expandRect.contains(Input::getMousePosition()) == true)
      {
        item->expanded = !item->expanded;
      }
    }
  }

  if(item->expanded == false)
  {
    return;
  }

  *indent = *indent + 1;
  for(int i = 0; i < item->children.size(); i++)
  {
    listFiles(indent, y, total, &item->children.at(i));
  }
  *indent = *indent - 1;
}

