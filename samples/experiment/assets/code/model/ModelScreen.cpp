#include "ModelScreen.h"

#include <iostream>

using namespace mutiny::engine;

ref<GameObject> ModelScreen::create()
{
  ref<GameObject> mainGo = GameObject::create("ModelScreen");
  mainGo->addComponent<ModelScreen>();

  return mainGo;
}

void ModelScreen::onStart()
{
  cameraGo = GameObject::create("MainCamera");
  ref<Camera> camera = cameraGo->addComponent<Camera>();
  cameraGo->getTransform()->setPosition(Vector3(0, 1, -10));

  modelGo = GameObject::create("Model");
  modelGo->getTransform()->setPosition(Vector3(0, 0, 10));

  ref<AnimatedMeshRenderer> playerMr = modelGo->addComponent<AnimatedMeshRenderer>();
  ref<AnimatedMesh> mesh = Resources::load<AnimatedMesh>("models/al/al");
  playerMr->setAnimatedMesh(mesh);
  //modelGo->getTransform()->setPosition(Vector3(0, 0, 10));
}

void ModelScreen::onUpdate()
{
  modelGo->getTransform()->rotate(Vector3(0, 10, 0) * Time::getDeltaTime());
}

void ModelScreen::onGui()
{
  if(Gui::button(Rect(200, 200, 200, 50), "Back") == true)
  {
    Application::loadLevel("introduction");
  }
}

