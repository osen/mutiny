#include "Sheep.h"
#include "GameScreen.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Sheep::create(GameScreen* gameScreen)
{
  GameObject* mainGo = new GameObject("Sheep");
  Sheep* sheep = mainGo->addComponent<Sheep>();
  sheep->gameScreen = gameScreen;

  return mainGo;
}

void Sheep::onUpdate()
{
  //getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 10.0f * Time::getDeltaTime());
  //getGameObject()->getTransform()->rotate(Vector3(0, 1, 0));

  CharacterController* cc = getGameObject()->getComponent<CharacterController>();

  cc->simpleMove(Vector3(0, -5, 0) * Time::getDeltaTime());
}

void Sheep::onStart()
{
  AnimatedMeshRenderer* sheepMr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/sheep/sheep");
  sheepMr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/sheep/run.anm");

  sheepMr->setAnimation(walkAnimation);
  sheepMr->setFps(4);
  sheepMr->play();

  getGameObject()->addComponent<CharacterController>();

  getGameObject()->getTransform()->translate(Vector3(rand() % 20 + 1, 0, rand() % 20 + 1));

  getGameObject()->getTransform()->rotate(Vector3(0, rand() % 360, 0));
}


