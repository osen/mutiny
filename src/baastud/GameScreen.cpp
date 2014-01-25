#include "GameScreen.h"
#include "GameCamera.h"
#include "Sheep.h"
#include "Fence.h"
#include "Player.h"

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
  GameCamera::create();
}

void GameScreen::onGui()
{
  Gui::label(Rect(10, 10, 100, 100), "game running...");
}

void GameScreen::onStart()
{
  Sheep::create();
  Fence::create();
  Player::create();
}
