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
  titleTexture = Resources::load<Texture2d>("textures/titleLogo");
  wwwTexture = Resources::load<Texture2d>("textures/www");

  GameObject* closeButtonGo = new GameObject("CloseButton");
  closeButton = closeButtonGo->addComponent<Button>();
  closeButton->getCanvas()->setSize(100, 200);

  GameObject* startButtonGo = new GameObject("StartButton");
  startButton = startButtonGo->addComponent<Button>();
  startButton->getCanvas()->setPosition(300, 200);
}

void MenuScreen::onGui()
{
  if(Gui::button(Rect(Screen::getWidth() - 280, 350, 200, 50), "begin game") == true)
  {
    Audio::stopMusic();
    Application::loadLevel("game");
  }
  else if(Gui::button(Rect(Screen::getWidth() - 280, 425, 200, 50), "audio test") == true)
  {
    Audio::stopMusic();
    Application::loadLevel("audiotest");
  }
  else if(Gui::button(Rect(Screen::getWidth() - 110, Screen::getHeight() - 40, 100, 30), "quit") == true)
  {
    Application::quit();
  }

  Gui::drawTexture(Rect(10, 10, titleTexture->getWidth(), titleTexture->getHeight()), titleTexture.cast<Texture>());
  Gui::drawTexture(Rect(10, Screen::getHeight() - wwwTexture->getHeight() + 80, 
    wwwTexture->getWidth(), wwwTexture->getHeight()), wwwTexture.cast<Texture>());
}

