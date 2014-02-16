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

  Animation* drinkAnimation = Resources::load<Animation>("models/cowboy/drink.anm");
  mr->setAnimation(drinkAnimation);
  mr->play();

  Animation* sitAnimation = Resources::load<Animation>("models/cowboy/sit.anm");
  lmr->setAnimation(sitAnimation);
  lmr->play();

  Mesh* bmesh = Resources::load<Mesh>("models/bottle/bottle");
  Texture2d* tex = Resources::load<Texture2d>("models/bottle/bottle");

  GameObject* bGo = new GameObject();

  for(int i = 0; i < mr->getRoot()->getTransform()->getChildCount(); i++)
  {
    if(mr->getRoot()->getTransform()->getChild(i)->getGameObject()->getName() == "RightLowerArm")
    {
      bGo->getTransform()->setParent(mr->getRoot()->getTransform()->getChild(i));
      bGo->getTransform()->setLocalRotation(Vector3(0, 0, 0));
      bGo->getTransform()->setLocalPosition(Vector3(-0.2f, -0.8f, -0.2f));
    }
  }

  MeshRenderer* bmr = bGo->addComponent<MeshRenderer>();
  MeshFilter* bmf = bGo->addComponent<MeshFilter>();

  Material* bmaterial = new Material(Resources::load<Material>("shaders/textured"));
  bmaterial->setMainTexture(tex);

  bmr->setMaterial(bmaterial);
  bmf->setMesh(bmesh);

}

void Horse::onUpdate()
{
  getGameObject()->getTransform()->translate(Vector3(5, 0, 0) * Time::getDeltaTime());
}

void Horse::onGui()
{

}

