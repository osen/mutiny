#include "Bullet.h"
#include "GameScreen.h"
#include "GameCamera.h"

#include <iostream>

using namespace mutiny::engine;

Bullet* Bullet::create(GameObject* emitter)
{
  GameObject* mainGo = new GameObject("Bullet");
  Bullet* rtn = mainGo->addComponent<Bullet>();
  rtn->emitterGo = emitter;

  return rtn;
}

void Bullet::onStart()
{
  lifetime = 1;
  getGameObject()->setTag("bullet");

  getGameObject()->getTransform()->setParent(emitterGo->getTransform());
  getGameObject()->getTransform()->setLocalPosition(Vector3(0, -1, 0.3f));
  getGameObject()->getTransform()->setParent(NULL);
  getGameObject()->getTransform()->setLocalRotation(emitterGo->getTransform()->getParent()->getParent()->getParent()->getRotation());

  MeshRenderer* mr = getGameObject()->addComponent<MeshRenderer>();
  MeshFilter* mf = getGameObject()->addComponent<MeshFilter>();
  Mesh* mesh = Resources::load<Mesh>("models/bullet/bullet");
  Texture2d* tex = Resources::load<Texture2d>("models/bullet/bullet");
  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);
  mf->setMesh(mesh);
  mr->setMaterial(material);
}


void Bullet::onUpdate()
{
  getGameObject()->getTransform()->translate(getGameObject()->getTransform()->getForward() * 20.0f * Time::getDeltaTime());
  lifetime -= Time::getDeltaTime();

  if(lifetime <= 0)
  {
    Object::destroy(getGameObject());
  }
}

void Bullet::onGui()
{

}

