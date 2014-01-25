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
  MeshRenderer* mr = getGameObject()->addComponent<MeshRenderer>();
  MeshFilter* mf = getGameObject()->addComponent<MeshFilter>();
  Mesh* mesh = Resources::load<Mesh>("models/terrain/terrain");
  Texture2d* tex = Resources::load<Texture2d>("models/terrain/terrain");

  Material* material = new Material(Resources::load<Material>("shaders/textured"));
  material->setMainTexture(tex);

  mr->setMaterial(material);
  mf->setMesh(mesh);

  MeshCollider* meshCollider = getGameObject()->addComponent<MeshCollider>();

  getGameObject()->getTransform()->setPosition(Vector3(0, -5, 0));
}

void Terrain::onUpdate()
{

}
