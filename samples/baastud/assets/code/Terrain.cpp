#include "Terrain.h"

#include <iostream>

using namespace mutiny::engine;

ref<GameObject> Terrain::create()
{
  ref<GameObject> mainGo = GameObject::create("Terrain");
  mainGo->addComponent<Terrain>();

  return mainGo;
}

void Terrain::onAwake()
{
  ref<MeshRenderer> mr = getGameObject()->addComponent<MeshRenderer>();
  ref<MeshFilter> mf = getGameObject()->addComponent<MeshFilter>();
  ref<Mesh> mesh = Resources::load<Mesh>("models/terrain/terrain");
  ref<Texture2d> tex = Resources::load<Texture2d>("models/terrain/terrain");

  material = Material::create(Resources::load<Shader>("shaders/Internal-MeshRendererTexture"));
  material->setMainTexture(tex);

  mr->setMaterial(material);
  mf->setMesh(mesh);

  ref<MeshCollider> meshCollider = getGameObject()->addComponent<MeshCollider>();

  getGameObject()->getTransform()->setPosition(Vector3(0, -1, 25));
}

