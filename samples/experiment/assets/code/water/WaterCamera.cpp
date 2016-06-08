#include "WaterCamera.h"

#include <vector>

using namespace mutiny::engine;

ref<WaterCamera> WaterCamera::create()
{
  ref<GameObject> cameraGo = GameObject::create("WaterCamera");
  ref<WaterCamera> camera = cameraGo->addComponent<WaterCamera>();

  return camera;
}

void WaterCamera::onAwake()
{
  Debug::log("WaterCamera awoken");

  ref<Camera> camera = getGameObject()->addComponent<Camera>();
  camera->setBackgroundColor(Color(0.5f, 0.5f, 1.0f, 1));

  getGameObject()->getTransform()->setPosition(Vector3(0, 3, 13));
  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}

void WaterCamera::onUpdate()
{
  //getGameObject()->getTransform()->rotateAround(Vector3(-10, 0, -10), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
}

