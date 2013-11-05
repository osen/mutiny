#include "IntroductionScreen.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* IntroductionScreen::create()
{
  GameObject* mainGo = new GameObject("IntroductionScreen");
  mainGo->addComponent<IntroductionScreen>();

  return mainGo;
}

void IntroductionScreen::onAwake()
{
  cameraGo = new GameObject("MainCamera");
  Camera* camera = cameraGo->addComponent<Camera>();
}

void IntroductionScreen::onGui()
{
  Gui::label(Rect(10, 10, 100, 100), "Welcome");

  if(Gui::button(Rect(200, 200, 200, 50), "Transform Example") == true)
  {
	Application::loadLevel("transform");
  }
}

