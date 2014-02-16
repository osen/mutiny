#include "MenuScreen.h"
#include "GameCamera.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Horse.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* MenuScreen::create()
{
  GameObject* mainGo = new GameObject("MenuScreen");
  mainGo->addComponent<MenuScreen>();

  return mainGo;
}

void MenuScreen::onAwake()
{

}

void MenuScreen::onStart()
{
  horse = Horse::create();
  horse->addCowboy();
  cameraGo = GameCamera::create(horse->getGameObject());
  SkyBox::create(horse->getGameObject());
  Terrain::create();
}

void MenuScreen::onGui()
{
  if(Gui::button(Rect(100, 100, 100, 100), "play") == true)
  {
    Application::loadLevel("game");
    return;
  }
}

