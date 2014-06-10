#include "ProjectScreen.h"

#define PADDING 10

void ProjectScreen::onAwake()
{

}

void ProjectScreen::onGui()
{
  headerRect.width = Screen::getWidth();
  headerRect.height = 75;

  inspectorRect.width = 300;
  inspectorRect.x = Screen::getWidth() - inspectorRect.width;
  inspectorRect.y = headerRect.height;
  inspectorRect.height = Screen::getHeight() - headerRect.height;

  filesRect.x = 0;
  filesRect.y = headerRect.height;
  filesRect.width = 200;

  logRect.x = filesRect.width;
  logRect.width = Screen::getWidth() - inspectorRect.width - logRect.x;
  logRect.height = 200;
  logRect.y = Screen::getHeight() - logRect.height;

  filesRect.height = Screen::getHeight() - headerRect.height - logRect.height;

  hierarchyRect.width = filesRect.width;
  hierarchyRect.x = filesRect.x;
  hierarchyRect.y = logRect.y;
  hierarchyRect.height = logRect.height;

  Gui::box(headerRect, "");
  Gui::box(filesRect, "");
  Gui::box(inspectorRect, "");
  Gui::box(hierarchyRect, "");
  Gui::box(logRect, "");
}

