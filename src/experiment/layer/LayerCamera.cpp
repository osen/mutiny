#include "LayerCamera.h"

#include <vector>

using namespace mutiny::engine;

GameObject* LayerCamera::create()
{
  GameObject* cameraGo = new GameObject("LayerCamera");
  cameraGo->addComponent<LayerCamera>();

  return cameraGo;
}

void LayerCamera::onAwake()
{
  Debug::log("LayerCamera awoken");

  Camera* camera = getGameObject()->addComponent<Camera>();
  camera->setBackgroundColor(Color(0, 0, 0, 1));

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, -8));
}

void LayerCamera::onUpdate()
{
  //getGameObject()->getTransform()->rotateAround(Vector3(0, 0, 0), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}

