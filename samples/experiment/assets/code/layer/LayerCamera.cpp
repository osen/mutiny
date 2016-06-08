#include "LayerCamera.h"

#include <vector>

using namespace mutiny::engine;

ref<GameObject> LayerCamera::create()
{
  ref<GameObject> cameraGo = GameObject::create("LayerCamera");
  cameraGo->addComponent<LayerCamera>();

  return cameraGo;
}

void LayerCamera::onAwake()
{
  Debug::log("LayerCamera awoken");

  ref<Camera> camera = getGameObject()->addComponent<Camera>();
  camera->setBackgroundColor(Color(0, 0, 0, 1));

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, 8));
}

void LayerCamera::onUpdate()
{
  //getGameObject()->getTransform()->rotateAround(Vector3(0, 0, 0), Vector3(0, 1, 0), 100.0f * Time::getDeltaTime());
  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}

