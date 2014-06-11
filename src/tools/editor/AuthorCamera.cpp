#include "AuthorCamera.h"

AuthorCamera* AuthorCamera::create()
{
  AuthorCamera* rtn;
  GameObject* go;

  go = new GameObject("Camera");
  rtn = go->addComponent<AuthorCamera>();

  return rtn;
}

void AuthorCamera::onAwake()
{
  getGameObject()->getTransform()->setPosition(Vector3(0, 0, -10));
  getGameObject()->addComponent<Camera>();
}

void AuthorCamera::onUpdate()
{
  Transform* transform;

  if(Input::getMouseButtonDown(1) == true)
  {
    prevMouse = Input::getMousePosition();
  }

  if(Input::getMouseButton(1) == true)
  {
    Vector3 mouseDelta = Input::getMousePosition() - prevMouse;

    prevMouse = Input::getMousePosition();
    transform = getGameObject()->getTransform();

    if(Input::getKey(KeyCode::W) == true)
    {
      transform->translate(transform->getForward() * 10.0f * Time::getDeltaTime());
    }

    transform->rotate(Vector3(mouseDelta.y, mouseDelta.x, 0));
  }
}
