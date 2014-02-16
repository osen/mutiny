#include "GameScreen.h"
#include "GameCamera.h"
#include "Terrain.h"
#include "SkyBox.h"
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

}

GameCamera* GameScreen::getCamera()
{
  return cameraGo->getComponent<GameCamera>();
}

void GameScreen::onGui()
{
  Gui::label(Rect(10, 10, 100, 100), "game running...");
}

void GameScreen::onStart()
{
  GameObject* playerGo = Player::create(this);
  SkyBox::create(playerGo);
  cameraGo = GameCamera::create(playerGo);
  Terrain::create();
}
