#include "Horse.h"
#include "GameScreen.h"
#include "GameCamera.h"

#include <iostream>

using namespace mutiny::engine;

Horse* Horse::create(GameScreen* gameScreen)
{
  GameObject* mainGo = new GameObject("Horse");
  Horse* horse = mainGo->addComponent<Horse>();
  horse->gameScreen = gameScreen;

  return horse;
}

void Horse::onAwake()
{
  mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/horse/horse");
  mr->setAnimatedMesh(mesh);

  runAnimation = Resources::load<Animation>("models/horse/run.anm");

  mr->setAnimation(runAnimation);
  mr->setInterpolateEnd(false);
  mr->setFps(8.0f);
  mr->play();

  getGameObject()->getTransform()->setPosition(Vector3(0, -0.5f, 0));

  addCowboy();
}

void Horse::addCowboy()
{
  GameObject* cowboyGo = new GameObject();
  cowboyGo->getTransform()->setParent(getGameObject()->getTransform());
  AnimatedMeshRenderer* mr = cowboyGo->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/cowboy/cowboy");
  mr->setAnimatedMesh(mesh);
  cowboyGo->getTransform()->setLocalRotation(Vector3(0, 90, 0));
  cowboyGo->getTransform()->setLocalPosition(Vector3(0, 1.2f, 0));

  GameObject* cowboyLGo = new GameObject();
  cowboyLGo->getTransform()->setParent(getGameObject()->getTransform());
  AnimatedMeshRenderer* lmr = cowboyLGo->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* lmesh = Resources::load<AnimatedMesh>("models/cowboy/cowboy_lower");
  lmr->setAnimatedMesh(lmesh);
  cowboyLGo->getTransform()->setLocalRotation(Vector3(0, 90, 0));
  cowboyLGo->getTransform()->setLocalPosition(Vector3(0, 1.2f, 0));

  Animation* sitAnimation = Resources::load<Animation>("models/cowboy/sit.anm");
  lmr->setAnimation(sitAnimation);
  lmr->play();

}

void Horse::onUpdate()
{
  getGameObject()->getTransform()->translate(Vector3(5, 0, 0) * Time::getDeltaTime());
}

void Horse::onGui()
{

}

