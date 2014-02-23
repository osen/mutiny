#include "DiedScreen.h"
#include "GameCamera.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Horse.h"
#include "Player.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* DiedScreen::create()
{
  GameObject* mainGo = new GameObject("DiedScreen");
  mainGo->addComponent<DiedScreen>();

  return mainGo;
}

void DiedScreen::onAwake()
{

}

void DiedScreen::onGui()
{
  Gui::label(Rect(10, 10, 100, 100), "game running...");
}

void DiedScreen::onStart()
{
  Terrain::create();

  Horse* horse = Horse::create();
  horse->wedge();

  setupPlayer();

  SkyBox::create(horse->getGameObject(), "textures/clouds");
  GameCamera::create(horse->getGameObject());
}

void DiedScreen::setupPlayer()
{
  GameObject* topGo = new GameObject();
  AnimatedMeshRenderer* mr = topGo->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/cowboy/cowboy");
  mr->setAnimatedMesh(mesh);

  Animation* walkAnimation = Resources::load<Animation>("models/cowboy/walk.anm");

  GameObject* legsGo = new GameObject();
  legsGo->getTransform()->setParent(topGo->getTransform());

  AnimatedMeshRenderer* lmr = legsGo->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* lmesh = Resources::load<AnimatedMesh>("models/cowboy/cowboy_lower");
  lmr->setAnimatedMesh(lmesh);

  legsGo->getTransform()->setLocalPosition(Vector3(0, 0, 0));
  legsGo->getTransform()->setLocalRotation(Vector3(0, 0, 0));

  lmr->setAnimation(walkAnimation);
  lmr->setFps(10);
  lmr->play();

  topGo->getTransform()->setRotation(Vector3(180, -25, 0));
  topGo->getTransform()->setPosition(Vector3(0, 2.3, 0));
}
