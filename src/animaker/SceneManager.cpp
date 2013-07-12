#include "SceneManager.h"
#include "MainScreen.h"

using namespace mutiny::engine;

void SceneManager::onAwake()
{
  dontDestroyOnLoad(getGameObject());
  loadLevel();
}

void SceneManager::onLevelWasLoaded()
{
  loadLevel();
}

void SceneManager::loadLevel()
{
  Debug::log("Level loaded: " + Application::getLoadedLevelName());

  if(Application::getLoadedLevelName() == "Main")
  {
    GameObject* mainGo = new GameObject("MainScreen");
    mainGo->addComponent<MainScreen>();
  }
}

