#include "ProjectScreen.h"
#include "Header.h"
#include "FilesPanel.h"
#include "HierarchyPanel.h"
#include "InspectorPanel.h"

#define PADDING 10

void ProjectScreen::onAwake()
{
  header.reset(new Header(this));
  filesPanel.reset(new FilesPanel(this));
  hierarchyPanel.reset(new HierarchyPanel(this));
  inspectorPanel.reset(new InspectorPanel(this));
}

void ProjectScreen::onGui()
{
  header->onGui();
  filesPanel->onGui();
  hierarchyPanel->onGui();
  inspectorPanel->onGui();

  logRect.x = filesPanel->position.width;
  logRect.width = Screen::getWidth() - inspectorPanel->position.width - logRect.x;
  logRect.height = 200;
  logRect.y = Screen::getHeight() - logRect.height;

  Gui::box(logRect, "");
}

