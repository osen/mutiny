#include "FallingCube.h"

using namespace mutiny::engine;

FallingCube* FallingCube::create()
{
  GameObject* go = GameObject::createPrimitive(PrimitiveType::CUBE);
  FallingCube* fallingCube = go->addComponent<FallingCube>();

  return fallingCube;
}

void FallingCube::onAwake()
{
  getGameObject()->getTransform()->setPosition(Vector3(0, 10, 0));
  getGameObject()->addComponent<RidgedBody>();
  getGameObject()->addComponent<Collider>();
}

void FallingCube::collisionEnter(Collision& collision)
{
  Debug::log("Collision Enter");
}

void FallingCube::collisionStay(Collision& collision)
{
  Debug::log("Collision Stay");
}

void FallingCube::collisionExit(Collision& collision)
{
  Debug::log("Collision Exit");
}
