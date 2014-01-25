#include "Sheep.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Sheep::create()
{
  GameObject* mainGo = new GameObject("Sheep");
  mainGo->addComponent<Sheep>();

  return mainGo;
}

void Sheep::onUpdate()
{
  getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 0.1f);
  getGameObject()->getTransform()->rotate(Vector3(0, 1, 0));
}

void Sheep::onAwake()
{
  AnimatedMeshRenderer* sheepMr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  sheepMr->setAnimatedMesh(mesh);

  getGameObject()->getTransform()->rotate(Vector3(0, 90, 0));
}


