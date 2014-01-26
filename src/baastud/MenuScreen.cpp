#include "MenuScreen.h"
#include "Audio.h"

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
  Audio::playMusic();
  cameraGo = new GameObject("MainCamera");
  Camera* camera = cameraGo->addComponent<Camera>();
}

void MenuScreen::onGui()
{
  Gui::label(Rect(100, 10, 100, 100), "baaaaaaaaaaaaasttuuuuddd");

  if(Gui::button(Rect(300, 200, 200, 50), "begin game") == true)
  {
    Audio::stopMusic();
    Application::loadLevel("game");
  }
  else if(Gui::button(Rect(300, 300, 200, 50), "audio test") == true)
  {
    Audio::stopMusic();
    Application::loadLevel("audiotest");
  }
  else if(Gui::button(Rect(500, 500, 200, 50), "quit") == true)
  {
    Application::quit();
  }
}

