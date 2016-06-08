#include "TransformScreen.h"

#include <iostream>

using namespace mutiny::engine;

ref<GameObject> TransformScreen::create()
{
  Debug::log("onAwake()");
  ref<GameObject> mainGo = GameObject::create("IntroductionScreen");
  mainGo->addComponent<TransformScreen>();

  return mainGo;
}

void TransformScreen::onAwake()
{
  cameraGo = GameObject::create("MainCamera");
  ref<Camera> camera = cameraGo->addComponent<Camera>();
  cameraGo->getTransform()->setPosition(Vector3(0, 1, -10));

  cube1Go = GameObject::createPrimitive(PrimitiveType::CUBE);
  cube1Go->getTransform()->setPosition(Vector3(5, 0, 10));
  cube1Go->setName("cube1Go");

  cube2Go = GameObject::createPrimitive(PrimitiveType::CUBE);
  cube2Go->getTransform()->setPosition(Vector3(-5, 0, 10));
  cube2Go->setName("cube2Go");
}

void TransformScreen::onUpdate()
{
  cube2Go->getTransform()->rotate(Vector3(0, 0, 20) * Time::getDeltaTime());
}

void TransformScreen::onGui()
{
  if(Gui::button(Rect(200, 200, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }

  if(cube1Go->getTransform()->getParent().expired())
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

