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
  axeReleaseTimeout = 0;
  shootTimeout = 0;
  mr = getGameObject()->addComponent<AnimatedMeshRenderer>();
  AnimatedMesh* mesh = Resources::load<AnimatedMesh>("models/injun/injun");
  mr->setAnimatedMesh(mesh);

  walkAnimation = Resources::load<Animation>("models/injun/walk.anm");
  throwAnimation = Resources::load<Animation>("models/injun/throw.anm");
  catchAnimation = Resources::load<Animation>("models/injun/catch.anm");

  getGameObject()->getTransform()->setRotation(Vector3(0, -90, 0));
  getGameObject()->getTransform()->setPosition(Vector3(20, 0, 0));

  axeGo = NULL;
  addAxe();
}

void Injun::onUpdate()
{
  bool shouldIdle = true;

  if(axeGo->getTransform()->getParent() != NULL)
  {
    shootTimeout -= Time::getDeltaTime();

    if(shootTimeout <= 0)
    {
      axeReleaseTimeout += Time::getDeltaTime();
    }

    if(axeReleaseTimeout >= 0.55f)
    {
      mr->setAnimation(catchAnimation);
      mr->play();
      axeGo->getTransform()->setParent(NULL);
      Vector3 currPos = axeGo->getTransform()->getPosition();
      currPos.y = 3.0f;
      axeGo->getTransform()->setPosition(currPos);
      axeReleaseTimeout = 0;
    }
  }
  else
  {
    axeGo->getTransform()->translate(axeVelocity * Time::getDeltaTime());
    axeGo->getTransform()->rotate(Vector3(1, 0, 0) * 720 * Time::getDeltaTime());
    axeVelocity.x += 30 * Time::getDeltaTime();

    if(axeGo->getTransform()->getPosition().x > getGameObject()->getTransform()->getPosition().x)
    {
      shootTimeout = 1.5f;
      grabAxe();
      mr->setAnimation(NULL);
    }
  }

  tryThrowAxe();
}

void Injun::tryThrowAxe()
{
  if(shootTimeout > 0)
  {
    return;
  }

  if(axeGo->getTransform()->getParent() == NULL)
  {
    return;
  }

  if(mr->getAnimation() == throwAnimation)
  {
    return;
  }

  mr->setAnimation(throwAnimation);
  mr->setFps(11.0f);
  axeReleaseTimeout = 0;
  axeVelocity = Vector3(-30, 0, 0);
  mr->playOnce();
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
  axeGo = tGo;

  MeshRenderer* mr = tGo->addComponent<MeshRenderer>();
  MeshFilter* mf = tGo->addComponent<MeshFilter>();

  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);

  mr->setMaterial(material);
  mf->setMesh(mesh);

  grabAxe();
}

void Injun::grabAxe()
{
  GameObject* tGo = axeGo;

  for(int i = 0; i < mr->getRoot()->getTransform()->getChildCount(); i++)
  {
    if(mr->getRoot()->getTransform()->getChild(i)->getGameObject()->getName() == "LeftLowerArm")
    {
      tGo->getTransform()->setParent(mr->getRoot()->getTransform()->getChild(i));
      tGo->getTransform()->setLocalRotation(Vector3(0, 0, 0));
      tGo->getTransform()->setLocalPosition(Vector3(0.1f, -1.0f, 0.4f));
    }
  }
}

