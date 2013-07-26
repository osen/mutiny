#include "SceneManager.h"
#include "MainScreen.h"
#include "SelectModelScreen.h"

using namespace mutiny::engine;

void SceneManager::onStart()
{
  dontDestroyOnLoad(getGameObject());
  Application::loadLevel("SelectModel");
}

void SceneManager::onLevelWasLoaded()
{
  loadLevel();
}

void SceneManager::loadLevel()
{
  Debug::log("Level loaded: " + Application::getLoadedLevelName());

  GameObject* go = new GameObject(Application::getLoadedLevelName() + "Screen");

  if(Application::getLoadedLevelName() == "SelectModel")
  {
    go->addComponent<SelectModelScreen>();
  }
  else if(Application::getLoadedLevelName() == "Main")
  {
    go->addComponent<MainScreen>();
  }
}

