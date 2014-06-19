#include "ProjectScreen.h"
#include "Header.h"
#include "FilesPanel.h"
#include "HierarchyPanel.h"
#include "InspectorPanel.h"
#include "ScenePanel.h"
#include "AuthorCamera.h"
#include "LogPanel.h"
#include "DropdownLayer.h"
#include "SelectProjectScreen.h"

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

  sceneName = "Untitled.mutiny";
  Application::setTitle("Mutiny - " + sceneName + " - " + SelectProjectScreen::selectedProject);

  // Temp (So I can see something...)
  GameObject* go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("Player");
  go->getTransform()->setPosition(Vector3(0, 10, 0));

  go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("WeaponSpawner");
  go->getTransform()->setPosition(Vector3(10, 10, 0));

  GameObject* go2 = GameObject::createPrimitive(PrimitiveType::CUBE);
  go2->setName("Sword");
  go2->getTransform()->setPosition(Vector3(0, 0, 0));
  go2->getTransform()->setParent(go->getTransform());

  go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("Terrain");
  go->getTransform()->setPosition(Vector3(10, 0, 0));

  go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->setName("House");
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

