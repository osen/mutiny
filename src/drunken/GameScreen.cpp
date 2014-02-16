#include "GameScreen.h"
#include "GameCamera.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Player.h"
#include "Pickup.h"
#include "Horse.h"

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

Player* GameScreen::getPlayer()
{
  return player;
}

void GameScreen::onStart()
{
  player = Player::create(this);
  SkyBox::create(player->getGameObject());
  cameraGo = GameCamera::create(player->getGameObject());
  Terrain::create();
  Pickup::create(this, PICKUP_GUN);

  Horse* horse = Horse::create();
  horse->wedge();
}
