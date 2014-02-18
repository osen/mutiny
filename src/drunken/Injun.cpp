#include "Injun.h"
#include "GameScreen.h"
#include "GameCamera.h"
#include "Bullet.h"

#include <iostream>

using namespace mutiny::engine;

Injun* Injun::create(GameScreen* gameScreen)
{
  GameObject* mainGo = new GameObject("Injun");
  Injun* injun = mainGo->addComponent<Injun>();
  injun->gameScreen = gameScreen;

  return injun;
}

void Injun::onAwake()
{
  shootTimeout = 0;
  mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/injun/injun");
  mr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/injun/walk.anm");
  throwAnimation = Resources::load<Animation>("models/injun/throw.anm");

  getGameObject()->getTransform()->setRotation(Vector3(0, -90, 0));
  getGameObject()->getTransform()->setPosition(Vector3(20, 0, 0));

  mr->setAnimation(walkAnimation);
  mr->setFps(1.0f);
  mr->play();

  axeGo = NULL;
  addAxe();
}

void Injun::onUpdate()
{
  bool shouldIdle = true;

  shootTimeout -= Time::getDeltaTime();
}

void Injun::tryThrowAxe()
{
  if(shootTimeout > 0)
  {
    return;
  }

  shootTimeout = 0.33333f;
}

void Injun::addAxe()
{
  if(axeGo != NULL)
  {
    return;
  }

  Mesh* mesh = Resources::load<Mesh>("models/axe/axe");
  Texture2d* tex = Resources::load<Texture2d>("models/axe/axe");

  GameObject* tGo = new GameObject();

  for(int i = 0; i < mr->getRoot()->getTransform()->getChildCount(); i++)
  {
    if(mr->getRoot()->getTransform()->getChild(i)->getGameObject()->getName() == "LeftLowerArm")
    {
      tGo->getTransform()->setParent(mr->getRoot()->getTransform()->getChild(i));
      tGo->getTransform()->setLocalRotation(Vector3(0, 0, 0));
      tGo->getTransform()->setLocalPosition(Vector3(0.1f, -1.0f, 0.4f));
    }
  }

  axeGo = tGo;

  MeshRenderer* mr = tGo->addComponent<MeshRenderer>();
  MeshFilter* mf = tGo->addComponent<MeshFilter>();

  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);

  mr->setMaterial(material);
  mf->setMesh(mesh);
}

