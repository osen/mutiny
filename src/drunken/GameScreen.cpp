#include "GameScreen.h"
#include "GameCamera.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Player.h"
#include "Pickup.h"
#include "Horse.h"
#include "Injun.h"

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
  return camera;
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

  if(Application::getLoadedLevelName() == "game")
  {
    SkyBox::create(player->getGameObject(), "textures/clouds");
  }
  else
  {
    SkyBox::create(player->getGameObject(), "textures/polluted_clouds");
  }

  camera = GameCamera::create(player->getGameObject());

  if(Application::getLoadedLevelName() == "game")
  {
    Terrain::create();
  }

  Pickup::create(this, PICKUP_GUN);

  Horse* horse = Horse::create();
  horse->wedge();

  //for(int i = 0; i < 10; i++)
  //{
  //  Injun* injun = Injun::create(this);
  //  injun->getGameObject()->getTransform()->setPosition(Vector3(Random::range(20, 400), 0, 0));
  //}
}
