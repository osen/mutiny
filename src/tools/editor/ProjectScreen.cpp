#include "ProjectScreen.h"
#include "Header.h"
#include "FilesPanel.h"
#include "HierarchyPanel.h"
#include "InspectorPanel.h"
#include "ScenePanel.h"
#include "AuthorCamera.h"
#include "LogPanel.h"
#include "DropdownLayer.h"

void ProjectScreen::onAwake()
{
  Screen::setResolution(800, 600, false);

  header.reset(new Header(this));
  filesPanel.reset(new FilesPanel(this));
  hierarchyPanel.reset(new HierarchyPanel(this));
  inspectorPanel.reset(new InspectorPanel(this));
  scenePanel.reset(new ScenePanel(this));
  logPanel.reset(new LogPanel(this));
  dropdownLayer.reset(new DropdownLayer(this));

  AuthorCamera::create();

  // Temp (So I can see something...)
  GameObject* go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("Da Cube?");
  go->getTransform()->setPosition(Vector3(0, 10, 0));

  go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("Da Other Cube");
  go->getTransform()->setPosition(Vector3(10, 10, 0));

  go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("Da Third Cube!");
  go->getTransform()->setPosition(Vector3(0, 0, 0));

  go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("Da Final Cube!");
  go->getTransform()->setPosition(Vector3(10, 0, 0));

  go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("Ok, just one more cube");
  go->getTransform()->setPosition(Vector3(10, 0, 10));
}

void ProjectScreen::onGui()
{
  header->gui();
  filesPanel->gui();
  hierarchyPanel->gui();
  inspectorPanel->gui();
  scenePanel->gui();
  logPanel->gui();
  dropdownLayer->onGui();
}

