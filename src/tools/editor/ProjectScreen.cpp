#include "ProjectScreen.h"
#include "Header.h"
#include "FilesPanel.h"
#include "HierarchyPanel.h"

#define PADDING 10

void ProjectScreen::onAwake()
{
  header.reset(new Header(this));
  filesPanel.reset(new FilesPanel(this));
  hierarchyPanel.reset(new HierarchyPanel(this));
}

void ProjectScreen::onGui()
{
  header->onGui();
  filesPanel->onGui();
  hierarchyPanel->onGui();

  inspectorRect.width = 300;
  inspectorRect.x = Screen::getWidth() - inspectorRect.width;
  inspectorRect.y = header->rect.height;
  inspectorRect.height = Screen::getHeight() - header->rect.height;

  logRect.x = filesPanel->rect.width;
  logRect.width = Screen::getWidth() - inspectorRect.width - logRect.x;
  logRect.height = 200;
  logRect.y = Screen::getHeight() - logRect.height;

  Gui::box(inspectorRect, "");
  Gui::box(logRect, "");
}

