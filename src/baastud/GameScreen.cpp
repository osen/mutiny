#include "GameScreen.h"
#include "Sheep.h"
#include "Fence.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* GameScreen::create()
{
  GameObject* mainGo = new GameObject("GameScreen");
  mainGo->addComponent<GameScreen>();

  return mainGo;
}

void GameScreen::onAwake()
{
  cameraGo = new GameObject("MainCamera");
  Camera* camera = cameraGo->addComponent<Camera>();
}

void GameScreen::onGui()
{
  Gui::label(Rect(10, 10, 100, 100), "game running...");
}

void GameScreen::onStart()
{
  Sheep::create();
  Fence::create();
}
