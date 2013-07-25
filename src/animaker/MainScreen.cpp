#include "MainScreen.h"
#include "MainCamera.h"

using namespace mutiny::engine;

void MainScreen::onAwake()
{
  MainCamera::create();
  GameObject* go = GameObject::createPrimitive(PrimitiveType::CUBE);
  go->getTransform()->setPosition(Vector3(1, 1, 0));

  transient = GameObject::createPrimitive(PrimitiveType::CUBE);

  go->getTransform()->setParent(transient->getTransform());
}

void MainScreen::onUpdate()
{
  transient->getTransform()->rotate(Vector3(0, 100, 0) * Time::getDeltaTime());
}

void MainScreen::onGui()
{

}

