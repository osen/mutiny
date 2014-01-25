#include "GameScreen.h"
#include "GameCamera.h"
#include "Sheep.h"
#include "Fence.h"
#include "Player.h"
#include "Terrain.h"
#include "SkyBox.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* GameScreen::create()
{
  GameObject* mainGo = new GameObject("GameScreen");
  mainGo->addComponent<GameScreen>();

  return mainGo;
}

GameObject* GameScreen::getFence()
{
  return fenceGo;
}

void GameScreen::onAwake()
{
}

void GameScreen::onGui()
{
  Gui::label(Rect(10, 10, 100, 100), "game running...");
}

void GameScreen::onStart()
{
  for(int i = 0; i < 10; i++)
  {
    Sheep::create(this);
  }

  fenceGo = Fence::create();
  GameObject* playerGo = Player::create(this);
  SkyBox::create(playerGo);
  GameCamera::create(playerGo);
  Terrain::create();
}
