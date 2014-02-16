#include "SceneManager.h"
#include "GameScreen.h"
#include "MenuScreen.h"

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

  if(Application::getLoadedLevelName() == "game")
  {
    GameScreen::create();
  }
  else if(Application::getLoadedLevelName() == "menu")
  {
    MenuScreen::create();
  }
}

