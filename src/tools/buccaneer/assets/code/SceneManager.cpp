#include "SceneManager.h"
#include "MainScreen.h"
#include "MenuScreen.h"

using namespace mutiny::engine;

void SceneManager::onStart()
{
  dontDestroyOnLoad(getGameObject());
  Application::loadLevel("Menu");
}

void SceneManager::onLevelWasLoaded()
{
  loadLevel();
}

void SceneManager::loadLevel()
{
  Debug::log("Level loaded: " + Application::getLoadedLevelName());

  ref<GameObject> go = GameObject::create(Application::getLoadedLevelName() + "Screen");

  if(Application::getLoadedLevelName() == "Menu")
  {
    go->addComponent<MenuScreen>();
  }
  else if(Application::getLoadedLevelName() == "Main")
  {
    go->addComponent<MainScreen>();
  }
}

