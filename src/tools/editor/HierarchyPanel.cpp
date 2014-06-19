#include "HierarchyPanel.h"
#include "ProjectScreen.h"
#include "FilesPanel.h"
#include "FileTree.h"

#include <vector>

#define ITEM_HEIGHT 20

HierarchyPanel::HierarchyPanel(ProjectScreen* parent)
{
  setTitle("Hierarchy");
  this->parent = parent;

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
  selectedGo = NULL;
}

void HierarchyPanel::onGui()
{
  position.width = parent->filesPanel->position.width;
  position.x = parent->filesPanel->position.x;

  position.height = parent->filesPanel->position.height;

  position.y = parent->filesPanel->position.y +
    parent->filesPanel->position.height;

  header();
  listGameObjects();
}

void HierarchyPanel::listGameObjects()
{
  int indent = 0;
  int y = 0;
  int total = 0;

  maxDisplay = (position.height - (ITEM_HEIGHT * 2)) / ITEM_HEIGHT;
  y = y - startDisplay;

  std::vector<Object*> gameObjects = 
    GameObject::findObjectsOfType<GameObject>();

  for(int i = 0; i < gameObjects.size(); i++)
  {
    GameObject* go = (GameObject*)gameObjects.at(i);

    if(go->getTransform()->getParent() != NULL)
    {
      continue;
    }

    if(go->getName().find("_EDITOR_") != std::string::npos)
    {
      continue;
    }

    listGameObjects(&indent, &y, &total, go);
    //Gui::label(Rect(position.x, position.y + 20 + 20 + (20 * i), position.width,
    //  20), gameObjects.at(i)->getName());
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

void HierarchyPanel::listGameObjects(int* indent, int* y, int* total, GameObject*
  gameObject)
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

    if(selectedGo != NULL && gameObject->getName() == selectedGo->getName())
    {
      Gui::drawTexture(Rect(position.x, rect.y, rect.width, rect.height), selectedTexture.get());
    }

    Gui::label(labelRect, gameObject->getName());

    if(Input::getMouseButtonDown(0) == true)
    {
      if(clickRect.contains(Input::getMousePosition()) == true &&
         expandRect.contains(Input::getMousePosition()) == false)
      {
        selectedGo = gameObject;
      }
    }
  }

  *y = *y + 1;

  if(display == true)
  {
    if(gameObject->getTransform()->getChildCount() > 0)
    {
      if(gameObject->getTag() != "expanded")
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
        if(gameObject->getTag() != "expanded") gameObject->setTag("expanded");
        else if(gameObject->getTag() == "expanded") gameObject->setTag("");
      }
    }
  }

  if(gameObject->getTag() != "expanded")
  {
    return;
  }

  *indent = *indent + 1;
  for(int i = 0; i < gameObject->getTransform()->getChildCount(); i++)
  {
    listGameObjects(indent, y, total,
      gameObject->getTransform()->getChild(i)->getGameObject());
  }
  *indent = *indent - 1;
}

void HierarchyPanel::header()
{
  Rect rect(position.x, position.y + ITEM_HEIGHT, position.width, ITEM_HEIGHT);

  Gui::box(rect, "");

  if(Gui::button(Rect(rect.x + 2, rect.y + 2, 65, ITEM_HEIGHT - 4),
    "Create") == true)
  {

  }
}

void HierarchyPanel::displayScrollbars()
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

