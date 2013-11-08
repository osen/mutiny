#include "TransformScreen.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* TransformScreen::create()
{
  GameObject* mainGo = new GameObject("IntroductionScreen");
  mainGo->addComponent<TransformScreen>();

  return mainGo;
}

void TransformScreen::onAwake()
{
  cameraGo = new GameObject("MainCamera");
  Camera* camera = cameraGo->addComponent<Camera>();
  cameraGo->getTransform()->setPosition(Vector3(0, 1, -10));

  cube1Go = GameObject::createPrimitive(PrimitiveType::CUBE);
  cube1Go->getTransform()->setPosition(Vector3(5, 0, 10));

  cube2Go = GameObject::createPrimitive(PrimitiveType::CUBE);
  cube2Go->getTransform()->setPosition(Vector3(-5, 0, 10));
}

void TransformScreen::onUpdate()
{
  cube2Go->getTransform()->rotate(Vector3(0, 0, 20) * Time::getDeltaTime());
}

void TransformScreen::onGui()
{
  Gui::label(Rect(10, 10, 100, 100), "Welcome");

  if(Gui::button(Rect(200, 200, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }

  if(cube1Go->getTransform()->getParent() == NULL)
  {
    if(Gui::button(Rect(10, 300, 200, 50), "Attach") == true)
    {
      cube1Go->getTransform()->setParent(cube2Go->getTransform());
    }
  }
  else
  {
    if(Gui::button(Rect(10, 300, 200, 50), "Detach") == true)
    {
      cube1Go->getTransform()->setParent(NULL);
    }
  }
}

