#include "AuthorCamera.h"

AuthorCamera* AuthorCamera::create()
{
  AuthorCamera* rtn;
  GameObject* go;

  go = new GameObject("_EDITOR_AuthorCamera");
  rtn = go->addComponent<AuthorCamera>();

  return rtn;
}

void AuthorCamera::onAwake()
{
  Camera* camera;

  getGameObject()->getTransform()->setPosition(Vector3(0, 0, -10));
  camera = getGameObject()->addComponent<Camera>();

  camera->setBackgroundColor(Color(0.171f, 0.171f, 0.171f, 1));
  //camera->setBackgroundColor(Color(0.5f, 0.5f, 0.5f, 1.0f));
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
    else if(Input::getKey(KeyCode::S) == true)
    {
      transform->translate(transform->getForward() * -10.0f * Time::getDeltaTime());
    }

    if(Input::getKey(KeyCode::A) == true)
    {
      transform->translate(transform->getRight() * -10.0f * Time::getDeltaTime());
    }
    else if(Input::getKey(KeyCode::D) == true)
    {
      transform->translate(transform->getRight() * 10.0f * Time::getDeltaTime());
    }

    transform->rotate(Vector3(mouseDelta.y, mouseDelta.x, 0));
  }
}
