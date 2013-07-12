#include "SceneManager.h"
#include "SplashScreen.h"
#include "CollisionTest.h"

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

  if(Application::getLoadedLevelName() == "Splash")
  {
    GameObject* splashGo = new GameObject("SplashScreen");
    splashGo->addComponent<SplashScreen>();
  }
  else if(Application::getLoadedLevelName() == "CollisionTest")
  {
    GameObject* go = new GameObject("CollisionTest");
    go->addComponent<CollisionTest>();
  }
}

