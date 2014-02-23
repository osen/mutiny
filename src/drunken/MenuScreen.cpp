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
  camera = GameCamera::create(horse->getGameObject());
  camera->toggleEventMode();
  SkyBox::create(horse->getGameObject(), "textures/clouds");
  Terrain::create();
}

void MenuScreen::onGui()
{
  if(Gui::button(Rect(100, 100, 100, 50), "play") == true)
  {
    Application::loadLevel("game");
    return;
  }

  if(Gui::button(Rect(100, 200, 100, 50), "play city") == true)
  {
    Application::loadLevel("level1");
    return;
  }
}

