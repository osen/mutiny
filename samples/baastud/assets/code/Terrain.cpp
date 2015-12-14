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
  arc<Mesh> mesh = Resources::load<Mesh>("models/terrain/terrain");
  arc<Texture2d> tex = Resources::load<Texture2d>("models/terrain/terrain");

  arc<Material> material(new Material(Resources::load<Material>("shaders/Internal-MeshRendererTexture")));
  material->setMainTexture(tex.cast<Texture>());

  mr->setMaterial(material);
  mf->setMesh(mesh);

  MeshCollider* meshCollider = getGameObject()->addComponent<MeshCollider>();

  getGameObject()->getTransform()->setPosition(Vector3(0, -1, 25));
}

