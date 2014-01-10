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

  if(Gui::button(Rect(200, 300, 200, 50), "Model Example") == true)
  {
    Application::loadLevel("model");
  }

  if(Gui::button(Rect(200, 400, 200, 50), "Collision Example") == true)
  {
    Application::loadLevel("collision");
  }

  if(Gui::button(Rect(200, 500, 200, 50), "Postprocess Example") == true)
  {
    Application::loadLevel("post");
  }

  if(Gui::button(Rect(410, 200, 200, 50), "Bloom Example") == true)
  {
    Application::loadLevel("bloom");
  }

  if(Gui::button(Rect(410, 300, 200, 50), "Layer Example") == true)
  {
    Application::loadLevel("layer");
  }
}

