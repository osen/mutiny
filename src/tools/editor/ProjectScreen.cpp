#include "ProjectScreen.h"
#include "Header.h"
#include "FilesPanel.h"
#include "HierarchyPanel.h"
#include "InspectorPanel.h"
#include "ScenePanel.h"
#include "AuthorCamera.h"
#include "LogPanel.h"

void ProjectScreen::onAwake()
{
  Screen::setResolution(800, 600, false);

  header.reset(new Header(this));
  filesPanel.reset(new FilesPanel(this));
  hierarchyPanel.reset(new HierarchyPanel(this));
  inspectorPanel.reset(new InspectorPanel(this));
  scenePanel.reset(new ScenePanel(this));
  logPanel.reset(new LogPanel(this));

  AuthorCamera::create();

  // Temp (So I can see something...)
  GameObject::createPrimitive(PrimitiveType::CUBE)->setName("Da Cube?");
}

void ProjectScreen::onGui()
{
  header->gui();
  filesPanel->gui();
  hierarchyPanel->gui();
  inspectorPanel->gui();
  scenePanel->gui();
  logPanel->gui();
}

