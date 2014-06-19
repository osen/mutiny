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

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, -10));
  camera = getGameObject()->addComponent<Camera>();

  camera->setBackgroundColor(Color(1.0f, 0.5f, 0.5f, 1.0f));

  rt.reset(new RenderTexture(512, 512));
  camera->setTargetTexture(rt.get());
}

RenderTexture* InspectorCamera::getRenderTexture()
{
  return rt.get();
}
