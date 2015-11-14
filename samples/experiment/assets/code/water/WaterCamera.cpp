#include "WaterCamera.h"

#include <vector>

using namespace mutiny::engine;

WaterCamera* WaterCamera::create()
{
  GameObject* cameraGo = new GameObject("WaterCamera");
  WaterCamera* camera = cameraGo->addComponent<WaterCamera>();

  return camera;
}

void WaterCamera::onAwake()
{
  Debug::log("WaterCamera awoken");

  Camera* camera = getGameObject()->addComponent<Camera>();
  camera->setBackgroundColor(Color(0.5f, 0.5f, 1.0f, 1));

  getGameObject()->getTransform()->setPosition(Vector3(0, 3, 13));
  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}

void WaterCamera::onUpdate()
{
  //getGameObject()->getTransform()->rotateAround(Vector3(-10, 0, -10), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
}

