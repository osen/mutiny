#include "SceneManager.h"
#include "introduction/IntroductionScreen.h"
#include "transform/TransformScreen.h"
#include "model/ModelScreen.h"

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
    IntroductionScreen::create();
  }
  else if (Application::getLoadedLevelName() == "transform")
  {
    TransformScreen::create();
  }
  else if (Application::getLoadedLevelName() == "model")
  {
    ModelScreen::create();
  }
}

