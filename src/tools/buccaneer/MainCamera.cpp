#include "MainCamera.h"

#include <vector>

using namespace mutiny::engine;

MainCamera* MainCamera::create()
{
  GameObject* cameraGo = new GameObject("MainCamera");
  MainCamera* camera = cameraGo->addComponent<MainCamera>();

  return camera;
}

void MainCamera::onAwake()
{
  Debug::log("MainCamera awoken");

  Camera* camera = getGameObject()->addComponent<Camera>();

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, 10));
  getGameObject()->getTransform()->setRotation(Vector3(0, 180, 0));
}

void MainCamera::onUpdate()
{
  //static float amount = 0;
  //amount=100.0f * Time::getDeltaTime();
  //getGameObject()->getTransform()->rotateAround(Vector3(0, 0, 0), Vector3(0, 1, 0), amount);
  //getGameObject()->getTransform()->translate(Vector3(-1, -1, 0));
  //getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}
