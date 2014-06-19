#include "SceneManager.h"
#include "SelectProjectScreen.h"
#include "ProjectScreen.h"

using namespace mutiny::engine;

void SceneManager::onStart()
{
  getGameObject()->setName("_EDITOR_SceneManager");
  dontDestroyOnLoad(getGameObject());
  Application::loadLevel("SelectProject");
}

void SceneManager::onLevelWasLoaded()
{
  loadLevel();
}

void SceneManager::loadLevel()
{
  Debug::log("Level loaded: " + Application::getLoadedLevelName());

  GameObject* go = new GameObject("_EDITOR_" + Application::getLoadedLevelName() + "Screen");

  if(Application::getLoadedLevelName() == "SelectProject")
  {
    go->addComponent<SelectProjectScreen>();
  }
  else if(Application::getLoadedLevelName() == "Project")
  {
    go->addComponent<ProjectScreen>();
  }
}

