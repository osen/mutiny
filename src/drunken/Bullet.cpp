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
  getGameObject()->getTransform()->setParent(emitterGo->getTransform());
  getGameObject()->getTransform()->setLocalPosition(Vector3(0, 0, 0));
  getGameObject()->getTransform()->setLocalRotation(Vector3(0, 0, 0));
  getGameObject()->getTransform()->setParent(NULL);

  MeshRenderer* mr = getGameObject()->addComponent<MeshRenderer>();
  MeshFilter* mf = getGameObject()->addComponent<MeshFilter>();
  Mesh* mesh = Resources::load<Mesh>("models/horse/horse");
  Texture2d* tex = Resources::load<Texture2d>("models/horse/horse");
  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);
  mf->setMesh(mesh);
  mr->setMaterial(material);

  direction = emitterGo->getTransform()->getParent()->getParent()->getParent()->getForward() * 20.0f;
}


void Bullet::onUpdate()
{
  getGameObject()->getTransform()->translate(direction * Time::getDeltaTime());
}

void Bullet::onGui()
{

}

