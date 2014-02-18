#include "Terrain.h"

#include <iostream>

using namespace mutiny::engine;

GameObject* Terrain::create()
{
  GameObject* mainGo = new GameObject("Terrain");
  mainGo->addComponent<Terrain>();

  return mainGo;
}

void Terrain::onAwake()
{
  Mesh* mesh = Resources::load<Mesh>("models/terrain/terrain");
  Texture2d* tex = Resources::load<Texture2d>("models/terrain/terrain");

  for(int i = 0; i < 3; i++)
  {
    GameObject* tGo = new GameObject();
    tGo->getTransform()->setParent(getGameObject()->getTransform());
    MeshRenderer* mr = tGo->addComponent<MeshRenderer>();
    MeshFilter* mf = tGo->addComponent<MeshFilter>();

    Material* material = new Material(Resources::load<Material>("shaders/textured"));
    material->setMainTexture(tex);

    mr->setMaterial(material);
    mf->setMesh(mesh);

    MeshCollider* meshCollider = tGo->addComponent<MeshCollider>();

    tGo->getTransform()->setPosition(Vector3(mesh->getBounds().size.x * i, 0, 20));
    tGo->getTransform()->setRotation(Vector3(0, 180, 0));
  }

  setupCactusii();
}

void Terrain::setupCactusii()
{
  Mesh* mesh = Resources::load<Mesh>("models/cactus/cactus");
  Texture2d* tex = Resources::load<Texture2d>("models/cactus/cactus");

  for(int i = 0; i < 20; i++)
  {
    GameObject* tGo = new GameObject();
    tGo->getTransform()->setParent(getGameObject()->getTransform());
    MeshRenderer* mr = tGo->addComponent<MeshRenderer>();
    MeshFilter* mf = tGo->addComponent<MeshFilter>();

    Material* material = new Material(Resources::load<Material>("shaders/textured"));
    material->setMainTexture(tex);

    mr->setMaterial(material);
    mf->setMesh(mesh);

    MeshCollider* meshCollider = tGo->addComponent<MeshCollider>();

    tGo->getTransform()->setPosition(Vector3(Random::range(0, 300), 0, Random::range(3, 10)));
    tGo->getTransform()->setRotation(Vector3(0, Random::range(0, 360), 0));
  }
}

void Terrain::onUpdate()
{

}
