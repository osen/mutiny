#include "MeshCollider.h"
#include "MeshFilter.h"
#include "GameObject.h"
#include "Debug.h"
#include "Mesh.h"

namespace mutiny
{

namespace engine
{

MeshCollider::~MeshCollider()
{

}

void MeshCollider::awake()
{
  Debug::log("MeshCollider awaken");

  ref<MeshFilter> meshFilter = getGameObject()->getComponent<MeshFilter>();

  if(meshFilter.valid())
  {
    mesh = meshFilter->getMesh();
    Debug::log("Added mesh");
  }

  Collider::awake();
}

void MeshCollider::setMesh(ref<Mesh> mesh)
{
  this->mesh = mesh;
}

ref<Mesh> MeshCollider::getMesh()
{
  return mesh;
}

}

}

