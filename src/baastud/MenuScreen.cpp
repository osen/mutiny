#include "MenuScreen.h"

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
  cameraGo = new GameObject("MainCamera");
  Camera* camera = cameraGo->addComponent<Camera>();
}

void MenuScreen::onGui()
{
  Gui::label(Rect(10, 10, 100, 100), "Welcome");

  if(Gui::button(Rect(200, 200, 200, 50), "Transform Example") == true)
  {
		Application::loadLevel("game");
  }
}

