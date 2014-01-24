#include "SceneManager.h"
#include "MenuScreen.h"
#include "GameScreen.h"

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

  if(Application::getLoadedLevelName() == "introduction")
  {
    MenuScreen::create();
  }
  else if(Application::getLoadedLevelName() == "game")
  {
    GameScreen::create();
  }
}

