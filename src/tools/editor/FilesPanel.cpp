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

  refreshFiles();

  expandTexture = Resources::load<Texture2d>("gui/expand");
  scrollbarTexture = Resources::load<Texture2d>("gui/scrollbar");

  selectedTexture.reset(new Texture2d(1, 1));
  selectedTexture->setPixel(0, 0, Color(1.0f, 1.0f, 1.0f, 0.1f));
  selectedTexture->apply();

  startDisplay = 0;
  maxDisplay = 0;
  totalDisplay = 0;
  scrolling = false;
  scrollPos = 0;
}

void FilesPanel::onGui()
{
  position.x = 0;
  position.y = parent->header->position.height;
  position.width = 200;
  position.height = (Screen::getHeight() - parent->header->position.height)
    / 2.0;

  header();
  listFiles();
}

void FilesPanel::refreshFiles()
{
  Application::setTitle("Mutiny - " + SelectProjectScreen::selectedProject);

  files.reset(new FileTree(Application::getDataPath() + "/../" +
    SelectProjectScreen::selectedProject));

  startDisplay = 0;
}

void FilesPanel::header()
{
  Rect rect(position.x, position.y + ITEM_HEIGHT, position.width, ITEM_HEIGHT);

  Gui::box(rect, "");

  if(Gui::button(Rect(rect.x + 2, rect.y + 2, 65, ITEM_HEIGHT - 4),
    "Create") == true)
  {

  }

  if(Gui::button(Rect(rect.x + rect.width - ITEM_HEIGHT - 2, rect.y + 2,
    ITEM_HEIGHT, ITEM_HEIGHT - 4), "") == true)
  {
    refreshFiles();
  }
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

  if(totalDisplay >= maxDisplay)
  {
    displayScrollbars();
  }
  else
  {
    startDisplay = 0;
  }
}

void FilesPanel::displayScrollbars()
{
  Rect container(position.x + position.width - 20,
                 position.y + (ITEM_HEIGHT * 3),
                 20,
                 position.height - (ITEM_HEIGHT * 4));

  Rect scrollbarRect(container.x, container.y + scrollPos,
                     container.width, 20);

  Gui::box(container, "");

  Rect upRect(container.x, container.y - ITEM_HEIGHT, ITEM_HEIGHT, ITEM_HEIGHT);
  Gui::button(upRect, "");

  if(Input::getMouseButton(0) == true &&
    upRect.contains(Input::getMousePosition()) == true)
  {
    scrollPos -= 100 * Time::getDeltaTime();
  }

  Rect downRect(container.x, container.y + container.height,
    ITEM_HEIGHT, ITEM_HEIGHT);

  Gui::button(downRect, "");

  if(Input::getMouseButton(0) == true &&
    downRect.contains(Input::getMousePosition()) == true)
  {
    scrollPos += 100 * Time::getDeltaTime();
  }

  scrollbarRect.height = ((float)maxDisplay / (float)totalDisplay)
    * (float)container.height;

  //Gui::drawTexture(scrollbarRect, scrollbarTexture);
  //Gui::button(scrollbarRect, "");

  Graphics::drawTexture(scrollbarRect, scrollbarTexture, Rect(0, 0, 1, 1),
                        5, 5, 5, 5);

  if(scrolling == false)
  {
    if(Input::getMouseButtonDown(0) == true &&
       scrollbarRect.contains(Input::getMousePosition()) == true)
    {
      mousePos = Input::getMousePosition().y;
      scrolling = true;
    }
  }
  else
  {
    scrollPos += Input::getMousePosition().y - mousePos;
    mousePos = Input::getMousePosition().y;

    if(Input::getMouseButtonUp(0) == true)
    {
      scrolling = false;
    }
  }

  if(scrollPos + scrollbarRect.height > container.height)
  {
    scrollPos = container.height - scrollbarRect.height;
  }

  if(scrollPos < 0)
  {
    scrollPos = 0;
  }

  float percent = 0;

  if(scrollPos == 0)
  {
    percent = 0;
  }
  else
  {
    percent = scrollPos / (container.height - scrollbarRect.height);
  }

  //std::cout << percent << std::endl;
  startDisplay = (totalDisplay - maxDisplay) * percent;
}

void FilesPanel::listFiles(int* indent, int* y, int* total, FileTree* item)
{
  Rect rect;
  Rect expandRect;
  bool display = false;

  //*total = *y;
  *total = *total + 1;
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
    Rect labelRect(rect.x + expandTexture->getWidth(), rect.y, rect.width
      - ((position.x + rect.x) - position.x + expandTexture->getWidth()),
      rect.height);

    Rect clickRect(position.x, rect.y, rect.width, rect.height);

    if(item->path == selectedPath)
    {
      Gui::drawTexture(Rect(position.x, rect.y, rect.width, rect.height), selectedTexture.get());
    }

    Gui::label(labelRect, item->getName());

    if(Input::getMouseButtonDown(0) == true)
    {
      if(clickRect.contains(Input::getMousePosition()) == true &&
         expandRect.contains(Input::getMousePosition()) == false)
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
      if(item->expanded == false)
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

