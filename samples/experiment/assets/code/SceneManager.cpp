#include "SceneManager.h"
#include "introduction/IntroductionScreen.h"
#include "transform/TransformScreen.h"
#include "model/ModelScreen.h"
#include "collision/CollisionScreen.h"
#include "post/PostScreen.h"
#include "bloom/BloomScreen.h"
#include "layer/LayerScreen.h"
#include "accum/AccumScreen.h"
#include "water/WaterScreen.h"

using namespace mutiny::engine;

void SceneManager::onAwake()
{
  watermark = Resources::load<Texture2d>("textures/watermark");
  dontDestroyOnLoad(watermark.cast<Object>());
  dontDestroyOnLoad(getGameObject());
  loadLevel();
}

void SceneManager::onLevelWasLoaded()
{
  loadLevel();
}

void SceneManager::onGui()
{
  if(Application::getLoadedLevelName() == "introduction")
  {
    Gui::drawTexture(Rect(Screen::getWidth() / 2 - watermark->getWidth() / 2, 40, watermark->getWidth(), watermark->getHeight()), watermark.cast<Texture>());
  }
  else
  {
    Gui::drawTexture(Rect(0, Screen::getHeight() - watermark->getHeight() / 2.0f - 25, watermark->getWidth() / 2.0f, watermark->getHeight() / 2.0f), watermark.cast<Texture>());
  }
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
  else if (Application::getLoadedLevelName() == "collision")
  {
    CollisionScreen::create();
  }
  else if (Application::getLoadedLevelName() == "post")
  {
    PostScreen::create();
  }
  else if (Application::getLoadedLevelName() == "bloom")
  {
    BloomScreen::create();
  }
  else if (Application::getLoadedLevelName() == "layer")
  {
    LayerScreen::create();
  }
  else if (Application::getLoadedLevelName() == "accum")
  {
    AccumScreen::create();
  }
  else if (Application::getLoadedLevelName() == "water")
  {
    WaterScreen::create();
  }
}

