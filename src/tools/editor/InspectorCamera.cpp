#include "InspectorCamera.h"

InspectorCamera* InspectorCamera::create()
{
  InspectorCamera* rtn;
  GameObject* go;

  go = new GameObject("_EDITOR_InspectorCamera");
  rtn = go->addComponent<InspectorCamera>();

  return rtn;
}

void InspectorCamera::onAwake()
{
  Camera* camera;

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, 7.5f));
  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
  camera = getGameObject()->addComponent<Camera>();

  camera->setCullMask(1 << 1);

  camera->setBackgroundColor(Color(0.171f, 0.171f, 0.171f, 1));

  rt.reset(new RenderTexture(512, 512));
  camera->setTargetTexture(rt.get());
}

void InspectorCamera::onUpdate()
{
  getGameObject()->getTransform()->rotateAround(
    Vector3(0, 0, 0), Vector3(0, 1, 0), 50 * Time::getDeltaTime());

  getGameObject()->getTransform()->lookAt(Vector3(0, 0, 0));
}

RenderTexture* InspectorCamera::getRenderTexture()
{
  return rt.get();
}
